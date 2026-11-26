using System;

namespace AIMP.SDK.Objects;

public interface IAimpImage2
{
    AimpActionResult LoadFromResource();

    AimpActionResult LoadFromBitmap(IntPtr bitmap);

    AimpActionResult LoadFromBits(RGBQuad bits, int width, int height);

    AimpActionResult CopyToClipboard();

    AimpActionResult CanPasteFromClipboard();

    AimpActionResult PasteFromClipboard();
}