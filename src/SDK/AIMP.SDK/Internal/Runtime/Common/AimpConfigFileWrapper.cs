using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// <see cref="IAimpConfigFile"/> over <c>IAIMPConfigFile</c>.
/// </summary>
internal sealed class AimpConfigFileWrapper : AimpConfigWrapper, IAimpConfigFile
{
    private readonly IAIMPConfigFileNative _nativeFile;

    public AimpConfigFileWrapper(IntPtr ownedPointer)
        : this(AimpComHelper.Wrap<IAIMPConfigFileNative>(ownedPointer))
    {
    }

    public AimpConfigFileWrapper(IAIMPConfigFileNative native)
        : base((IAIMPConfigNative)native, true)
    {
        _nativeFile = native;
    }

    public static AimpConfigFileWrapper FromBorrowed(IntPtr pointer)
    {
        return pointer == IntPtr.Zero
            ? null
            : new AimpConfigFileWrapper(
                AimpComHelper.WrapBorrowed<IAIMPConfigFileNative>(pointer));
    }

    public AimpActionResult LoadFromFile(string fileName)
    {
        var text = AimpString.CreateNative(fileName ?? string.Empty);

        try
        {
            return AimpResult.From(_nativeFile.LoadFromFile(text));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult LoadFromStream(IAimpStream stream)
    {
        return ExecuteStream(stream, pointer => _nativeFile.LoadFromStream(pointer));
    }

    public AimpActionResult SaveToFile(string fileName)
    {
        var text = AimpString.CreateNative(fileName ?? string.Empty);

        try
        {
            return AimpResult.From(_nativeFile.SaveToFile(text));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult SaveToStream(IAimpStream stream)
    {
        return ExecuteStream(stream, pointer => _nativeFile.SaveToStream(pointer));
    }

    private static AimpActionResult ExecuteStream(IAimpStream stream, Func<IntPtr, int> action)
    {
        var pointer = stream is IAimpNativeObject native ? native.NativePointer : IntPtr.Zero;

        try
        {
            return AimpResult.From(action(pointer));
        }
        finally
        {
            if (pointer != IntPtr.Zero)
            {
                Marshal.Release(pointer);
            }
        }
    }
}