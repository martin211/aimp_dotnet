using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Lyrics
{
    /// <summary>
    /// <c>IAIMPLyrics</c> (apiLyrics.h): property list + lyrics commands.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4C79-7269-6373-46696C650000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPLyricsNative
    {
        [PreserveSig]
        void BeginUpdate();

        [PreserveSig]
        void EndUpdate();

        [PreserveSig]
        int Reset();

        [PreserveSig]
        int GetValueAsFloat(int propertyId, out double value);

        [PreserveSig]
        int GetValueAsInt32(int propertyId, out int value);

        [PreserveSig]
        int GetValueAsInt64(int propertyId, out long value);

        [PreserveSig]
        int GetValueAsObject(int propertyId, ref Guid iid, out IntPtr value);

        [PreserveSig]
        int SetValueAsFloat(int propertyId, double value);

        [PreserveSig]
        int SetValueAsInt32(int propertyId, int value);

        [PreserveSig]
        int SetValueAsInt64(int propertyId, long value);

        [PreserveSig]
        int SetValueAsObject(int propertyId, IntPtr value);

        [PreserveSig]
        int Assign(IntPtr source);

        [PreserveSig]
        int Clone(out IntPtr target);

        [PreserveSig]
        int Add(int timeStart, int timeFinish, IntPtr text);

        [PreserveSig]
        int Delete(int index);

        [PreserveSig]
        int Find(int time, ref int index, out IntPtr text);

        [PreserveSig]
        int Get(int index, ref int timeStart, ref int timeFinish, out IntPtr text);

        [PreserveSig]
        int GetCount(out int value);

        [PreserveSig]
        int LoadFromFile(IntPtr fileUri);

        [PreserveSig]
        int LoadFromStream(IntPtr stream, int format);

        [PreserveSig]
        int LoadFromString(IntPtr text, int format);

        [PreserveSig]
        int SaveToFile(IntPtr fileUri);

        [PreserveSig]
        int SaveToStream(IntPtr stream, int format);

        [PreserveSig]
        int SaveToString(out IntPtr text, int format);
    }
}