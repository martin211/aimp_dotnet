using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.TagEditor;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;
using AIMP.SDK.TagEditor;

namespace AIMP.Internal.Runtime.TagEditor
{
    /// <summary>
    /// v1 <see cref="IAimpServiceFileTagEditor"/>.
    /// </summary>
    internal sealed class AimpServiceFileTagEditor : AimpObjectWrapper, IAimpServiceFileTagEditor
    {
        private readonly IAIMPServiceFileTagEditorNative _native;

        public AimpServiceFileTagEditor(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileTagEditorNative>(borrowedPointer);
        }

        public bool IsExists => _native != null;

        public AimpActionResult<IAimpFileTagEditor> EditFile(string filePath)
        {
            if (_native == null)
            {
                return AimpResult.Fail<IAimpFileTagEditor>();
            }

            var text = AimpString.CreateNative(filePath ?? string.Empty);
            var iid = AimpIids.IAIMPFileTagEditor;

            try
            {
                var hr = _native.EditFile(text, in iid, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.Fail<IAimpFileTagEditor>()
                    : AimpResult.Ok<IAimpFileTagEditor>(new AimpFileTagEditorWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult<IAimpFileTagEditor> EditFile(IAimpStream fileStream)
        {
            if (_native == null)
            {
                return AimpResult.Fail<IAimpFileTagEditor>();
            }

            var stream = AimpBridgeHelper.GetStreamPointer(fileStream);
            var iid = AimpIids.IAIMPFileTagEditor;

            try
            {
                var hr = _native.EditFile(stream, in iid, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.Fail<IAimpFileTagEditor>()
                    : AimpResult.Ok<IAimpFileTagEditor>(new AimpFileTagEditorWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(stream);
            }
        }

        public AimpActionResult<IAimpFileInfo> EditTag(string filePath, TagType tag)
        {
            if (_native == null)
            {
                return AimpResult.Fail<IAimpFileInfo>();
            }

            var text = AimpString.CreateNative(filePath ?? string.Empty);
            var iid = AimpIids.IAIMPFileInfo;

            try
            {
                var hr = _native.EditTag(text, (int)tag, in iid, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.Fail<IAimpFileInfo>()
                    : AimpResult.Ok<IAimpFileInfo>(new AimpFileInfoWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult<IAimpFileInfo> EditTag(IAimpStream fileStream, TagType tag)
        {
            if (_native == null)
            {
                return AimpResult.Fail<IAimpFileInfo>();
            }

            var stream = AimpBridgeHelper.GetStreamPointer(fileStream);
            var iid = AimpIids.IAIMPFileInfo;

            try
            {
                var hr = _native.EditTag(stream, (int)tag, in iid, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.Fail<IAimpFileInfo>()
                    : AimpResult.Ok<IAimpFileInfo>(new AimpFileInfoWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(stream);
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