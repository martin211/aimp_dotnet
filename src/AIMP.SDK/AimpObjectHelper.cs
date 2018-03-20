using System;
using System.Runtime.InteropServices;
using AIMP.SDK.Objects;

namespace AIMP.SDK
{
    public static class AimpObjectHelper
    {
        public class AimpObject
        {
            public const string AimpString = "41494D50-5374-7269-6E67-000000000000";
        }

        public static TObject GetObject<TObject>(IAimpCore core)
        {
            Type type = typeof(TObject);
            IntPtr header = IntPtr.Zero;
            if (type == typeof(IAIMPString))
            {
                var id = new Guid(AimpObject.AimpString);
                header = core.CreateObject(ref id);
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
    }
}