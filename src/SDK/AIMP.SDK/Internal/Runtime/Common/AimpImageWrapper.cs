using System;
using System.Drawing;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Types;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// v1 <see cref="IAimpImage"/> over <c>IAIMPImage</c>.
/// </summary>
internal sealed class AimpImageWrapper : AimpObjectWrapper, IAimpImage
{
    private readonly IAIMPImageNative _native;

    public AimpImageWrapper(IntPtr ownedPointer)
    {
        _native = AimpComHelper.Wrap<IAIMPImageNative>(ownedPointer);
    }

    public AimpImageFormat FormatId => (AimpImageFormat)_native.GetFormatID();

    public PointF Size
    {
        get
        {
            var hr = _native.GetSize(out var size);
            return hr < 0 ? PointF.Empty : new PointF(size.Width, size.Height);
        }
    }

    public AimpActionResult LoadFromFile(string fileName)
    {
        if (string.IsNullOrEmpty(fileName))
        {
            throw new ArgumentNullException(nameof(fileName), "fileName cannot be empty.");
        }

        var text = AimpString.CreateNative(fileName);

        try
        {
            return AimpResult.From(_native.LoadFromFile(text));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult LoadFromStream(IAimpStream stream)
    {
        return ExecuteStream(stream, pointer => _native.LoadFromStream(pointer));
    }

    public AimpActionResult SaveToFile(string fileName, AimpImageFormat format)
    {
        if (string.IsNullOrEmpty(fileName))
        {
            throw new ArgumentNullException(nameof(fileName), "fileName cannot be empty.");
        }

        var text = AimpString.CreateNative(fileName);

        try
        {
            return AimpResult.From(_native.SaveToFile(text, (int)format));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult SaveToStream(IAimpStream stream, AimpImageFormat format)
    {
        return ExecuteStream(stream, pointer => _native.SaveToStream(pointer, (int)format));
    }

    public AimpActionResult<IAimpImage> Clone()
    {
        var hr = _native.Clone(out var pointer);

        return hr < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpImage>()
            : AimpResult.Ok<IAimpImage>(new AimpImageWrapper(pointer));
    }

    public AimpActionResult Draw(IntPtr dc, RectangleF rect)
    {
        var nativeRect = new AimpNativeRect
        {
            Left = (int)rect.Left,
            Top = (int)rect.Top,
            Right = (int)rect.Right,
            Bottom = (int)rect.Bottom
        };

        return AimpResult.From(_native.Draw(dc, nativeRect, 0, IntPtr.Zero));
    }

    public AimpActionResult Resize(int width, int height)
    {
        return AimpResult.From(_native.Resize(width, height));
    }

    // IAimpImage2 is not projected yet; the legacy helpers return a clean failure.
    public AimpActionResult LoadFromResource() => AimpResult.Fail();

    public AimpActionResult LoadFromBitmap(IntPtr bitmap) => AimpResult.Fail();

    public AimpActionResult LoadFromBits(RGBQuad bits, int width, int height) => AimpResult.Fail();

    public AimpActionResult CopyToClipboard() => AimpResult.Fail();

    public AimpActionResult CanPasteFromClipboard() => AimpResult.Fail();

    public AimpActionResult PasteFromClipboard() => AimpResult.Fail();

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

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}