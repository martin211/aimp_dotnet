using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Core;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Core;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceVersionInfo"/>.
    /// </summary>
    internal sealed class AimpServiceVersionInfo : AimpObjectWrapper, IAimpServiceVersionInfo
    {
        private readonly IAIMPServiceVersionInfoNative _native;

        public AimpServiceVersionInfo(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceVersionInfoNative>(borrowedPointer);
        }

        public string FormatInfo
        {
            get
            {
                if (_native == null)
                {
                    return string.Empty;
                }

                var hr = _native.FormatInfo(out var text);

                return hr < 0 || text == IntPtr.Zero
                    ? string.Empty
                    : AimpString.ReadAndRelease(text);
            }
        }

        public DateTime BuildDate
        {
            get
            {
                if (_native == null)
                {
                    return DateTime.MinValue;
                }

                var value = _native.GetBuildDate();
                var year = (value >> 16) & 0xFFFF;
                var month = (value >> 8) & 0xFF;
                var day = value & 0xFF;

                try
                {
                    return new DateTime(year, month, day).AddMilliseconds(1);
                }
                catch
                {
                    return DateTime.MinValue;
                }
            }
        }

        public BuildStateType BuildState =>
            _native == null ? BuildStateType.Alpha : (BuildStateType)_native.GetBuildState();

        public int BuildNumber => _native?.GetBuildNumber() ?? 0;

        public int VersionId => _native?.GetVersionID() ?? 0;

        protected override void OnDispose()
        {
            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}