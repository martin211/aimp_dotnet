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
using System.Runtime.InteropServices;

namespace AIMP.SDK.Objects
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct RGBQuad
    {
        public byte rgbBlue;
        public byte rgbGreen;
        public byte rgbRed;
        public byte rgbReserved;
    }

    public interface IAimpImage2
    {
        AimpActionResult LoadFromResource();

        AimpActionResult LoadFromBitmap(IntPtr bitmap);

        AimpActionResult LoadFromBits(RGBQuad bits, int width, int height);

        AimpActionResult CopyToClipboard();

        AimpActionResult CanPasteFromClipboard();

        AimpActionResult PasteFromClipboard();
    }
}
