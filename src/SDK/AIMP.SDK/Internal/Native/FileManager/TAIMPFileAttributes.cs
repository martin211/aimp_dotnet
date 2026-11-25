using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>TAIMPFileAttributes</c> (apiFileManager.h, pack(1)).
    /// </summary>
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct TAIMPFileAttributes
    {
        public uint Attributes;
        public double TimeCreation;
        public double TimeLastAccess;
        public double TimeLastWrite;
        public long Reserved0;
        public long Reserved1;
        public long Reserved2;
    }
}