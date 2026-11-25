using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.PlayList;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpPlaylistPreimageFolders"/> over a native preimage.
    /// </summary>
    internal sealed class AimpPlaylistPreimageFoldersWrapper :
        AimpPlaylistPreimageWrapper,
        IAimpPlaylistPreimageFolders
    {
        private readonly IAIMPPlaylistPreimageFoldersNative _folders;

        public AimpPlaylistPreimageFoldersWrapper(IntPtr ownedPointer)
            : base(ownedPointer)
        {
            _folders = AimpComHelper.Wrap<IAIMPPlaylistPreimageFoldersNative>(
                AimpComHelper.AddRef(ownedPointer));
        }

        public AimpActionResult ItemsAdd(string path, bool recursive)
        {
            var pointer = AimpString.CreateNative(path ?? string.Empty);

            try
            {
                return AimpResult.From(_folders.ItemsAdd(pointer, recursive ? 1 : 0));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult ItemsDelete(int index)
        {
            return AimpResult.From(_folders.ItemsDelete(index));
        }

        public AimpActionResult ItemsDeleteAll()
        {
            return AimpResult.From(_folders.ItemsDeleteAll());
        }

        public AimpActionResult<string, bool> ItemsGet(int index)
        {
            var hr = _folders.ItemsGet(index, out var path, out var recursive);

            return hr < 0
                ? new AimpActionResult<string, bool>(AimpResult.ToResult(hr), null, false)
                : AimpResult.Ok(AimpString.ReadAndRelease(path), recursive != 0);
        }

        public int ItemsGetCount()
        {
            return _folders.ItemsGetCount();
        }

        protected override void OnDispose()
        {
            if (_folders != null)
            {
                Marshal.FinalReleaseComObject(_folders);
            }

            base.OnDispose();
        }
    }
}