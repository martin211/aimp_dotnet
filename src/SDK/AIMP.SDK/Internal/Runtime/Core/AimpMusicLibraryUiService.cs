using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.MusicLibrary;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceMusicLibraryUI"/>.
    /// </summary>
    internal sealed class AimpMusicLibraryUiService : AimpObjectWrapper, IAimpServiceMusicLibraryUI
    {
        private readonly IAIMPServiceMusicLibraryUINative _native;

        public AimpMusicLibraryUiService(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceMusicLibraryUINative>(borrowedPointer);
        }

        public bool IsExists => _native != null;

        public AimpActionResult<IAimpFileList> GetFiles(FilesType flags)
        {
            return _native == null || _native.GetFiles((uint)flags, out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpFileList>()
                : AimpResult.Ok<IAimpFileList>(new AimpFileListWrapper(pointer));
        }

        public AimpActionResult<IAimpDataFilter> GetGroupingFilter()
        {
            return _native == null || _native.GetGroupingFilter(out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpDataFilter>()
                : AimpResult.Ok<IAimpDataFilter>(new AimpDataFilterWrapper(pointer));
        }

        public AimpActionResult<string> GetGroupingFilterPath()
        {
            return _native == null || _native.GetGroupingFilterPath(out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        public AimpActionResult SetGroupingFilterPath(string path)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = AimpString.CreateNative(path);

            try
            {
                return AimpResult.From(_native.SetGroupingFilterPath(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        protected override void OnDispose()
        {
            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}