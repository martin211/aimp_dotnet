using System;
using System.Drawing;

namespace AIMP.SDK.Objects;

public interface IAimpImage : IAimpObject, IAimpImage2
{
    AimpImageFormat FormatId { get; }

    PointF Size { get; }

    AimpActionResult LoadFromFile(string fileName);

    AimpActionResult LoadFromStream(IAimpStream stream);

    AimpActionResult SaveToFile(string fileName, AimpImageFormat format);

    AimpActionResult SaveToStream(IAimpStream stream, AimpImageFormat format);

    AimpActionResult<IAimpImage> Clone();

    AimpActionResult Draw(IntPtr dc, RectangleF rect);

    AimpActionResult Resize(int width, int height);
}