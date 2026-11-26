using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistQueue</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-506C-7351-7565-756500000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPPlaylistQueueNative
    {
        [PreserveSig]
        int Add(IntPtr item, int insertAtBeginning);

        [PreserveSig]
        int AddList(IntPtr itemList, int insertAtBeginning);

        [PreserveSig]
        int Delete(IntPtr item);

        [PreserveSig]
        int Delete2(IntPtr playlist);

        [PreserveSig]
        int Move(IntPtr item, int targetIndex);

        [PreserveSig]
        int Move2(int itemIndex, int targetIndex);

        [PreserveSig]
        int GetItem(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetItemCount();
    }
}