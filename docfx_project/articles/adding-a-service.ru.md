# Добавление нового сервиса AIMP

В этом руководстве описано, как добавить сервис AIMP в `AIMP.SDK`: публичный контракт, нативную проекцию, внутреннюю реализацию и подключение к `IAimpPlayer`.

## Слои проекта

```
src/SDK/AIMP.SDK/
  SDK/        публичный контракт для плагинов (только интерфейсы/API)
  Native/     [ComImport]-проекции api*.h (публичные технически, не API плагина)
  Runtime/    internal-реализации сервисов и объектов
  Bridges/    CCW-мосты: managed-объект плагина -> нативный интерфейс AIMP
  Internal/   AimpComHelper, AimpString, AimpPropertyBag, AimpIids, AimpResult...
  Loader/     Bootstrap, PluginHost, NativePluginBridge
```

Правило: **в `SDK/` нет реализации**. Если сервис нужен плагину — интерфейс в `SDK/`, реализация — в `Runtime/`, нативный vtable — в `Native/`.

## Шаг 1. Публичный интерфейс в `SDK/`

Пример — `SDK/FileManager/IAimpServiceFileFormats.cs`:

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

Требования:

- интерфейс `public`;
- если это сервис — наследовать `IAimpService` (там `bool IsExists { get; }`);
- методы возвращают `AimpActionResult` / `AimpActionResult<T>`, а не `HRESULT`;
- строки — `string`, указатели — `IntPtr`, структуры — обычные C#-структуры;
- никаких `AimpComHelper`, `IAIMP...Native` и нативных указателей в публичном контракте.

Если сервис должен быть доступен через `IAimpPlayer`, добавьте свойство в `SDK/IAimpPlayer.cs`:

```csharp
IAimpServiceFileFormats ServiceFileFormats { get; }
```

## Шаг 2. IID в `Internal/AimpIids.cs`

```csharp
public static readonly Guid IAIMPServiceFileFormats =
    new Guid("41494D50-5372-7646-696C-65466D747300");
```

GUID берётся из `api*.h`:

```cpp
static const GUID IID_IAIMPServiceFileFormats =
    {0x41494D50, 0x5372, 0x7646, 0x69, 0x6C, 0x65, 0x46, 0x6D, 0x74, 0x73, 0x00};
```

Важно: строка GUID строго в формате `8-4-4-4-12`. Частая ошибка при переносе — получить `8-4-4-4-4-8`.

## Шаг 3. Нативная проекция в `Native/`

Файл — `Native/AimpClientServicesNative.cs` или новый `AimpXxxNative.cs`:

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

Правила разметки:

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
| `RECT`, `SIZE` | отдельная `struct` с `LayoutKind.Sequential` |

Порядок методов **строго** как в `api*.h`, включая унаследованные интерфейсы. `IUnknown` в C# не указывается — он неявный.

Если интерфейс наследует другой COM-интерфейс, можно либо объявить все методы подряд (плоско), либо унаследовать C#-интерфейс:

```csharp
public interface IAIMPLyricsNative : IAIMPPropertyListNative
{
    [PreserveSig] int Assign(IntPtr source);
    // ...
}
```

Для property-list сервисов (`IAIMPPropertyList`) отдельный нативный интерфейс не нужен — используется `IAIMPPropertyListNative` + `AimpPropertyBag`.

## Шаг 4. Внутренняя реализация в `Runtime/`

Пример — `Runtime/Core/AimpClientServiceWrappers.cs`:

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

Ключевые моменты:

- класс `internal`;
- наследует `AimpObjectWrapper` (даёт `Dispose`);
- `WrapBorrowed<T>` — если сервис получен как заимствованный указатель; `Wrap<T>` — если владение передаётся;
- `AimpResult.From(hr)` превращает `HRESULT` в `AimpActionResult`;
- `AimpString.CreateNative` / `ReadAndRelease` для строк;
- все указатели освобождаются в `finally`;
- `OnDispose` освобождает RCW.

Если сервис — property list:

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

Property ID складываются в `Native/AimpConstants.cs` в класс `AimpPropId`.

## Шаг 5. Подключение в `AimpPlayer`

Файл — `Runtime/Core/AimpCoreWrappers.cs`, класс `AimpPlayer`.

Добавить поле:

```csharp
private IAimpServiceFileFormats _fileFormats;
```

Добавить свойство:

```csharp
public IAimpServiceFileFormats ServiceFileFormats =>
    _fileFormats ?? (_fileFormats =
        Service<IAIMPServiceFileFormatsNative, IAimpServiceFileFormats>(
            AimpIids.IAIMPServiceFileFormats,
            pointer => new AimpServiceFileFormats(pointer)));
```

`Service<TNative, TService>` делает `QueryInterface` по IID, оборачивает указатель и кладёт объект в `_owned`, чтобы он освободился вместе с плеером.

Если добавляли свойство в `SDK/IAimpPlayer.cs`, реализация обязана быть в `AimpPlayer`, иначе проект не соберётся.

## Шаг 6. Если сервис возвращает объекты

Пример: `IAimpServicePlaybackQueue.GetNextTrack()` возвращает `IAimpPlaybackQueueItem`.

1. Публичный интерфейс объекта — в `SDK/<Area>/Objects/`.
2. Нативная проекция объекта — в `Native/`.
3. Обёртка — `Runtime/<Area>/...Wrappers.cs`:

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

- `ownedPointer` — если AIMP отдал `**Obj` (владение ваше); используется `Wrap<T>`.
- `IAimpNativeObject` — если объект потом можно передать обратно в нативный вызов.
- `NativePointer` возвращает **новую** ссылку (`AddRef`), её нужно освобождать у вызывающего.

## Шаг 7. Если сервис использует callback

Пример — `IAIMPServiceLyrics.Get(...)` или `IAIMPServiceThreads`.

В нативной проекции callback — `IntPtr`:

```csharp
[PreserveSig]
int Get(IntPtr fileInfo, uint flags, IntPtr callback,
        IntPtr userData, out IntPtr taskId);
```

В реализации:

```csharp
[UnmanagedFunctionPointer(CallingConvention.StdCall)]
private delegate void LyricsReceiveCallback(IntPtr lyrics, IntPtr userData);

private LyricsReceiveCallback _callback;

_callback = OnReceive;
var callbackPointer = Marshal.GetFunctionPointerForDelegate(_callback);
var hr = _native.Get(info, (uint)flags, callbackPointer, data, out var taskId);
```

Делегат хранится в поле, иначе GC его соберёт и нативный код упадёт.

`userData` можно передать как `GCHandle`:

```csharp
var handle = GCHandle.Alloc(userData);
var ptr = GCHandle.ToIntPtr(handle);
```

В callback — `GCHandle.FromIntPtr(ptr).Target` и `handle.Free()`.

## Шаг 8. Если AIMP вызывает плагин (extension/CCW)

Это не сервис, а обратное направление. Пример — `IAimpExtensionFileInfoProvider`.

1. Публичный контракт — `SDK/.../Extensions/`.
2. Нативный интерфейс — `Native/`.
3. Мост — `Bridges/XxxBridge.cs`:

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

4. Регистрация — `Internal/AimpExtensionRegistrar.cs`: добавить ветку `as IAimpExtensionXxx` и `Register(core, extension, new XxxBridge(...), <IID сервиса-владельца>, typeof(INative))`.

Для нескольких опциональных контрактов у одного объекта используется `ICustomQueryInterface.GetInterface`, чтобы AIMP получал только реально реализованные интерфейсы.

## Шаг 9. Если сервис создаёт объекты через `Core.CreateObject<T>`

Добавить IID в `AimpIids`, затем ветку в `AimpCoreWrapper.CreateObject<TAimpObject>()`:

```csharp
if (target == typeof(IAimpImageContainer))
{
    var pointer = _core.CreateObject(AimpIids.IAIMPImageContainer);
    return AimpResult.Ok<IAimpObject>(new AimpImageContainerWrapper(pointer));
}
```

Если объект создаётся по enum — добавить значение в `AimpObjectType` и ветку в `CreateObject(AimpObjectType)`.

## Шаг 10. Сборка и проверка

```powershell
# только SDK
& $msbuild src\SDK\AIMP.SDK\AIMP.SDK.csproj /t:Build /p:Configuration=Release

# всё + smoke test
pwsh src\build.ps1 -Configuration Release
```

Проверить:

- `AIMP.SDK` собирается;
- `build.ps1` — `PASS` x86 и x64;
- smoke test не падает;
- если сервис используется интеграционными тестами — `deploy.ps1` и запуск в AIMP.

## Чек-лист нового сервиса

- [ ] Публичный интерфейс добавлен в `SDK/<Area>/` и наследует `IAimpService`, если это сервис.
- [ ] Свойство добавлено в `SDK/IAimpPlayer.cs` (если сервис доступен плагину).
- [ ] IID добавлен в `Internal/AimpIids.cs`.
- [ ] Нативная проекция добавлена в `Native/` с точным порядком vtable и `[PreserveSig]`.
- [ ] Внутренняя реализация добавлена в `Runtime/<Area>/` как `internal sealed class`.
- [ ] Для строк используются `AimpString.CreateNative` / `ReadAndRelease`.
- [ ] Для `HRESULT` используется `AimpResult.From`.
- [ ] Все входящие/исходящие указатели освобождаются.
- [ ] Сервис подключён в `AimpPlayer` через `Service<TNative, TService>`.
- [ ] Если есть объекты — добавлены их нативные проекции и обёртки.
- [ ] Если есть callback — делегат хранится в поле.
- [ ] Если AIMP вызывает плагин — добавлен мост в `Bridges/` и регистрация в `AimpExtensionRegistrar`.
- [ ] `msbuild` + `build.ps1` проходят без ошибок.
