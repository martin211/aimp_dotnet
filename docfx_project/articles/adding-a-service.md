# Adding a new AIMP service

This guide describes how to add an AIMP service to `AIMP.SDK`: the public contract, the native projection, the internal implementation and how to expose it through `IAimpPlayer`.

## Project layers

```
src/SDK/AIMP.SDK/
  SDK/        public plugin contract (interfaces/API only)
  Native/     [ComImport] projections of api*.h (technically public, not plugin API)
  Runtime/    internal service and object implementations
  Bridges/    CCW bridges: managed plugin object -> native AIMP interface
  Internal/   AimpComHelper, AimpString, AimpPropertyBag, AimpIids, AimpResult...
  Loader/     Bootstrap, PluginHost, NativePluginBridge
```

Rule: **`SDK/` contains no implementation**. A plugin-facing interface goes to `SDK/`, the implementation goes to `Runtime/`, and the native vtable goes to `Native/`.

## Step 1. Public interface in `SDK/`

Example — `SDK/FileManager/IAimpServiceFileFormats.cs`:

```csharp
namespace AIMP.SDK.FileManager
{
    [Flags]
    public enum FileFormats
    {
        Audio = 1,
        Playlists = 2
    }

    public interface IAimpServiceFileFormats : IAimpService
    {
        AimpActionResult<string> GetFormats(FileFormats flags);
        AimpActionResult IsSupported(string fileName, FileFormats flags);
    }
}
```

Requirements:

- the interface is `public`;
- a service inherits `IAimpService` (`bool IsExists { get; }`);
- methods return `AimpActionResult` / `AimpActionResult<T>`, not `HRESULT`;
- strings are `string`, pointers are `IntPtr`, structs are ordinary C# structs;
- no `AimpComHelper`, `IAIMP...Native` or native pointers in the public contract.

If the service must be reachable through `IAimpPlayer`, add a property to `SDK/IAimpPlayer.cs`:

```csharp
IAimpServiceFileFormats ServiceFileFormats { get; }
```

## Step 2. IID in `Internal/AimpIids.cs`

```csharp
public static readonly Guid IAIMPServiceFileFormats =
    new Guid("41494D50-5372-7646-696C-65466D747300");
```

The GUID comes from `api*.h`:

```cpp
static const GUID IID_IAIMPServiceFileFormats =
    {0x41494D50, 0x5372, 0x7646, 0x69, 0x6C, 0x65, 0x46, 0x6D, 0x74, 0x73, 0x00};
```

Important: the GUID string must use the `8-4-4-4-12` format. A common mistake when copying is producing `8-4-4-4-4-8`.

## Step 3. Native projection in `Native/`

Put it in `Native/AimpClientServicesNative.cs` or a new `AimpXxxNative.cs`:

```csharp
[ComImport]
[ComVisible(true)]
[Guid("41494D50-5372-7646-696C-65466D747300")]
[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
public interface IAIMPServiceFileFormatsNative
{
    [PreserveSig] int GetFormats(uint flags, out IntPtr formats);
    [PreserveSig] int IsSupported(IntPtr fileName, uint flags);
}
```

Marshalling rules:

| C++ | C# |
|---|---|
| `HRESULT WINAPI F(...)` | `[PreserveSig] int F(...)` |
| `void WINAPI F(...)` | `[PreserveSig] void F(...)` |
| `BOOL`, `int`, `DWORD` | `int`, `uint` |
| `DWORD_PTR` | `UIntPtr` |
| `INT64`, `long long` | `long` |
| `WCHAR*`, `IAIMPString*` | `IntPtr` |
| `IUnknown*`, `void*` | `IntPtr` |
| `REFIID` | `in Guid` |
| `IAIMPString**`, `T**` | `out IntPtr` |
| `T**` (in/out) | `ref IntPtr` |
| `RECT`, `SIZE` | a separate `struct` with `LayoutKind.Sequential` |

Method order **must** match `api*.h` exactly, including inherited interfaces. `IUnknown` is implicit and is not listed in C#.

If the interface derives from another COM interface, either list all methods flat or inherit the C# interface:

```csharp
public interface IAIMPLyricsNative : IAIMPPropertyListNative
{
    [PreserveSig] int Assign(IntPtr source);
    // ...
}
```

For property-list services (`IAIMPPropertyList`) no separate native interface is needed — use `IAIMPPropertyListNative` + `AimpPropertyBag`.

## Step 4. Internal implementation in `Runtime/`

Example — `Runtime/Core/AimpClientServiceWrappers.cs`:

```csharp
internal sealed class AimpServiceFileFormats :
    AimpObjectWrapper,
    IAimpServiceFileFormats
{
    private readonly IAIMPServiceFileFormatsNative _native;

    public AimpServiceFileFormats(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileFormatsNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<string> GetFormats(FileFormats flags)
    {
        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var hr = _native.GetFormats((uint)flags, out var text);

        return hr < 0 || text == IntPtr.Zero
            ? AimpResult.Fail<string>()
            : AimpResult.Ok(AimpString.ReadAndRelease(text));
    }

    public AimpActionResult IsSupported(string fileName, FileFormats flags)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var text = AimpString.CreateNative(fileName ?? string.Empty);

        try
        {
            return AimpResult.From(_native.IsSupported(text, (uint)flags));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}
```

Key points:

- the class is `internal`;
- it derives from `AimpObjectWrapper` (which provides `Dispose`);
- `WrapBorrowed<T>` — the service pointer is borrowed; `Wrap<T>` — ownership is transferred;
- `AimpResult.From(hr)` converts `HRESULT` to `AimpActionResult`;
- `AimpString.CreateNative` / `ReadAndRelease` handle strings;
- every pointer is released in `finally`;
- `OnDispose` releases the RCW.

For a property-list service:

```csharp
public AimpServiceConnectionSettings(IntPtr borrowedPointer)
{
    _properties = AimpPropertyBag.FromOwned(
        AimpComHelper.QueryInterface(borrowedPointer, AimpIids.IAIMPPropertyList));
}

public int TimeOut
{
    get => _properties?.GetInt32(AimpPropId.ConnectionTimeout) ?? 0;
    set => _properties?.SetInt32(AimpPropId.ConnectionTimeout, value);
}
```

Property IDs live in `Native/AimpConstants.cs` in the `AimpPropId` class.

## Step 5. Expose the service in `AimpPlayer`

File — `Runtime/Core/AimpCoreWrappers.cs`, class `AimpPlayer`.

Add a field:

```csharp
private IAimpServiceFileFormats _fileFormats;
```

Add a property:

```csharp
public IAimpServiceFileFormats ServiceFileFormats =>
    _fileFormats ?? (_fileFormats =
        Service<IAIMPServiceFileFormatsNative, IAimpServiceFileFormats>(
            AimpIids.IAIMPServiceFileFormats,
            pointer => new AimpServiceFileFormats(pointer)));
```

`Service<TNative, TService>` performs `QueryInterface` with the IID, wraps the pointer and adds the object to `_owned`, so it is disposed together with the player.

If you added a property to `SDK/IAimpPlayer.cs`, `AimpPlayer` must implement it, otherwise the project will not compile.

## Step 6. Services that return objects

Example: `IAimpServicePlaybackQueue.GetNextTrack()` returns `IAimpPlaybackQueueItem`.

1. Public object interface — `SDK/<Area>/Objects/`.
2. Native object projection — `Native/`.
3. Wrapper — `Runtime/<Area>/...Wrappers.cs`:

```csharp
internal sealed class AimpPlaybackQueueItemWrapper :
    AimpObjectWrapper,
    IAimpPlaybackQueueItem,
    IAimpNativeObject
{
    private readonly IntPtr _pointer;
    private readonly IAIMPPropertyListNative _native;

    public AimpPlaybackQueueItemWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        _native = AimpComHelper.Wrap<IAIMPPropertyListNative>(ownedPointer);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);
    // ...
}
```

- `ownedPointer` — AIMP returned `**Obj` (ownership is yours); use `Wrap<T>`.
- `IAimpNativeObject` — the object can be passed back into a native call.
- `NativePointer` returns a **new** reference (`AddRef`); the caller must release it.

## Step 7. Services that use callbacks

Example — `IAIMPServiceLyrics.Get(...)` or `IAIMPServiceThreads`.

The native callback parameter is an `IntPtr`:

```csharp
[PreserveSig]
int Get(IntPtr fileInfo, uint flags, IntPtr callback,
        IntPtr userData, out IntPtr taskId);
```

Implementation:

```csharp
[UnmanagedFunctionPointer(CallingConvention.StdCall)]
private delegate void LyricsReceiveCallback(IntPtr lyrics, IntPtr userData);

private LyricsReceiveCallback _callback;

_callback = OnReceive;
var callbackPointer = Marshal.GetFunctionPointerForDelegate(_callback);
var hr = _native.Get(info, (uint)flags, callbackPointer, data, out var taskId);
```

Keep the delegate in a field; otherwise the GC may collect it and the native code will crash.

`userData` can be passed through a `GCHandle`:

```csharp
var handle = GCHandle.Alloc(userData);
var ptr = GCHandle.ToIntPtr(handle);
```

In the callback use `GCHandle.FromIntPtr(ptr).Target` and `handle.Free()`.

## Step 8. When AIMP calls the plugin (extension/CCW)

This is the opposite direction. Example — `IAimpExtensionFileInfoProvider`.

1. Public contract — `SDK/.../Extensions/`.
2. Native interface — `Native/`.
3. Bridge — `Bridges/XxxBridge.cs`:

```csharp
[ComVisible(true)]
[ClassInterface(ClassInterfaceType.None)]
internal sealed class FileInfoProviderBridge :
    IAIMPExtensionFileInfoProviderNative,
    ICustomQueryInterface
{
    private readonly IAimpExtensionFileInfoProvider _provider;
    // ...
}
```

4. Registration — `Internal/AimpExtensionRegistrar.cs`: add an `as IAimpExtensionXxx` branch and `Register(core, extension, new XxxBridge(...), <owner service IID>, typeof(INative))`.

When one object implements several optional contracts, use `ICustomQueryInterface.GetInterface` so AIMP only sees the interfaces the plugin actually implements.

## Step 9. Objects created through `Core.CreateObject<T>`

Add the IID to `AimpIids`, then add a branch to `AimpCoreWrapper.CreateObject<TAimpObject>()`:

```csharp
if (target == typeof(IAimpImageContainer))
{
    var pointer = _core.CreateObject(AimpIids.IAIMPImageContainer);
    return AimpResult.Ok<IAimpObject>(new AimpImageContainerWrapper(pointer));
}
```

If the object is created by an enum, add a value to `AimpObjectType` and a branch to `CreateObject(AimpObjectType)`.

## Step 10. Build and verify

```powershell
# SDK only
& $msbuild src\SDK\AIMP.SDK\AIMP.SDK.csproj /t:Build /p:Configuration=Release

# everything + smoke test
pwsh src\build.ps1 -Configuration Release
```

Check:

- `AIMP.SDK` builds;
- `build.ps1` reports `PASS` for x86 and x64;
- the smoke test does not fail;
- if the service is covered by integration tests — run `deploy.ps1` and start AIMP.

## New service checklist

- [ ] Public interface added under `SDK/<Area>/` and inherits `IAimpService` when it is a service.
- [ ] Property added to `SDK/IAimpPlayer.cs` (if the service is exposed to plugins).
- [ ] IID added to `Internal/AimpIids.cs`.
- [ ] Native projection added under `Native/` with the exact vtable order and `[PreserveSig]`.
- [ ] Internal implementation added under `Runtime/<Area>/` as an `internal sealed class`.
- [ ] Strings use `AimpString.CreateNative` / `ReadAndRelease`.
- [ ] `HRESULT` values use `AimpResult.From`.
- [ ] All incoming/outgoing pointers are released.
- [ ] Service exposed in `AimpPlayer` through `Service<TNative, TService>`.
- [ ] If objects are returned — their native projections and wrappers are added.
- [ ] If a callback is used — the delegate is stored in a field.
- [ ] If AIMP calls the plugin — a bridge in `Bridges/` and registration in `AimpExtensionRegistrar` are added.
- [ ] `msbuild` + `build.ps1` pass without errors.
