// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System;
using System.IO;

namespace AIMP.SDK.FileManager
{
    public struct AimpFileAttributes : IEquatable<AimpFileAttributes>
    {
        public FileAttributes Attributes { get; set; }

        public DateTime TimeLastAccess { get; set; }

        public DateTime TimeLastWrite { get; set; }

        public DateTime TimeCreation { get; set; }

        public bool Equals(AimpFileAttributes other)
        {
            return Attributes.Equals(other.Attributes) &&
                   TimeLastAccess == other.TimeLastAccess &&
                   TimeLastWrite == other.TimeLastWrite &&
                   TimeCreation == other.TimeCreation;
        }
    }
}