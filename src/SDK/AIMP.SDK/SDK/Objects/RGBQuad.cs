using System.Runtime.InteropServices;

namespace AIMP.SDK.Objects;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public struct RGBQuad
{
    public byte rgbBlue;
    public byte rgbGreen;
    public byte rgbRed;
    public byte rgbReserved;
}