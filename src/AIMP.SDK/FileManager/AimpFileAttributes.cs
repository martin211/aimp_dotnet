using System;
using System.IO;

namespace AIMP.SDK.FileManager
{
    public struct AimpFileAttributes
    {
        public FileAttributes Attributes { get; set; }

        public DateTime TimeLastAccess { get; set; }

        public DateTime TimeLastWrite { get; set; }

        public DateTime TimeCreation { get; set; }
    }
}