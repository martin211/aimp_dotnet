using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylist</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-506C-7300-0000-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPPlaylistNative
    {
        [PreserveSig]
        int Add(IntPtr obj, uint flags, int insertIn);

        [PreserveSig]
        int AddList(IntPtr objList, uint flags, int insertIn);

        [PreserveSig]
        int Delete(IntPtr item);

        [PreserveSig]
        int Delete2(int itemIndex);

        [PreserveSig]
        int Delete3(uint flags, IntPtr proc, IntPtr userData);

        [PreserveSig]
        int DeleteAll();

        [PreserveSig]
        int Sort(int mode);

        [PreserveSig]
        int Sort2(IntPtr template);

        [PreserveSig]
        int Sort3(IntPtr proc, IntPtr userData);

        [PreserveSig]
        int BeginUpdate();

        [PreserveSig]
        int EndUpdate();

        [PreserveSig]
        int Close(uint flags);

        [PreserveSig]
        int GetFiles(uint flags, out IntPtr list);

        [PreserveSig]
        int MergeGroup(IntPtr group);

        [PreserveSig]
        int ReloadFromPreimage();

        [PreserveSig]
        int ReloadInfo(uint flags);

        [PreserveSig]
        int GetItem(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetItemCount();

        [PreserveSig]
        int GetGroup(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetGroupCount();

        [PreserveSig]
        int ListenerAdd(IntPtr listener);

        [PreserveSig]
        int ListenerRemove(IntPtr listener);
    }
}