// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Drawing;
using AIMP.SDK.Objects;

namespace AIMP.SDK
{
    public enum AimpImageFormat
    {
        Unknown = 0,
        BPM = 1,
        GIF = 2,
        JPG = 3,
        PNG = 4
    }

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
}
