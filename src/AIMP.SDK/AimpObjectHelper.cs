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
using AIMP.SDK.Objects;

namespace AIMP.SDK
{
    public static class AimpObjectHelper
    {
        public static TObject GetObject<TObject>(IAimpCore core)
        {
            Type type = typeof(TObject);
            IntPtr header = IntPtr.Zero;
            if (type == typeof(IAimpString))
            {
                var id = new Guid(AimpObject.AimpString);
                //header = core.CreateObject(ref id);
            }

            if (header == IntPtr.Zero)
            {
                return default(TObject);
            }

            return GetObject<TObject>(header);
        }

        public static TObject GetObject<TObject>(IntPtr header)
        {
            return (TObject)Marshal.GetObjectForIUnknown(header);
        }

        public class AimpObject
        {
            public const string AimpString = "41494D50-5374-7269-6E67-000000000000";
        }
    }
}