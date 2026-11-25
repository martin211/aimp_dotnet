using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Actions;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Runtime.MusicLibrary
{
    /// <summary>
    /// v1 <see cref="IAimpDataStorageManager"/> over the native manager.
    /// </summary>
    internal sealed class AimpDataStorageManagerWrapper : AimpObjectWrapper, IAimpDataStorageManager
    {
        private readonly IAIMPMLDataStorageManagerNative _native;

        public AimpDataStorageManagerWrapper(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPMLDataStorageManagerNative>(borrowedPointer);
        }

        public AimpActionResult BackgroundTaskStarted(int id, string caption, IAimpActionEvent cancelEvent)
        {
            var text = AimpString.CreateNative(caption);
            var cancel = AimpActionEventBridge.CreatePointer(cancelEvent);

            try
            {
                // Since AIMP 6.0 the native method returns void.
                _native.BackgroundTaskStarted(id, text, cancel);
                return AimpResult.Ok();
            }
            finally
            {
                AimpComHelper.Release(text);
                AimpComHelper.Release(cancel);
            }
        }

        public AimpActionResult BackgroundTaskFinished(int id)
        {
            // Since AIMP 6.0 the native method returns void.
            _native.BackgroundTaskFinished(id);
            return AimpResult.Ok();
        }

        public void Changed()
        {
            _native.Changed();
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