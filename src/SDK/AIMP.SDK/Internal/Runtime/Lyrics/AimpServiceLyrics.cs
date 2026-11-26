using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Lyrics;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Lyrics;
using AIMP.SDK.Lyrics.Objects;

namespace AIMP.Internal.Runtime.Lyrics;

/// <summary>
/// v1 <see cref="IAimpServiceLyrics"/>.
/// </summary>
internal sealed class AimpServiceLyrics : AimpObjectWrapper, IAimpServiceLyrics
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    private delegate void LyricsReceiveCallback(IntPtr lyrics, IntPtr userData);

    private readonly IAIMPServiceLyricsNative _native;
    private readonly List<IntPtr> _userDataStrings = new List<IntPtr>();
    private LyricsReceiveCallback _callback;

    public AimpServiceLyrics(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceLyricsNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public event AimpServiceLyricsReceive LyricsReceive;

    public AimpActionResult<IntPtr> Get(IAimpFileInfo fileInfo, LyricsFlags flags, string userData)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IntPtr>();
        }

        var info = AimpBridgeHelper.GetPointer(fileInfo, typeof(IAIMPFileInfoNative));
        var data = IntPtr.Zero;

        if (!string.IsNullOrEmpty(userData))
        {
            data = AimpString.CreateNative(userData);
            _userDataStrings.Add(data);
        }

        _callback = OnReceive;

        try
        {
            var callbackPointer = Marshal.GetFunctionPointerForDelegate(_callback);
            var hr = _native.Get(info, (uint)flags, callbackPointer, data, out var taskId);

            return hr < 0
                ? AimpResult.Fail<IntPtr>()
                : AimpResult.Ok(taskId);
        }
        finally
        {
            AimpComHelper.Release(info);
        }
    }

    public AimpActionResult Cancel(IntPtr taskId, LyricsFlags flags)
    {
        return _native == null
            ? AimpResult.Fail()
            : AimpResult.From(_native.Cancel(taskId, (uint)flags));
    }

    private void OnReceive(IntPtr lyrics, IntPtr userData)
    {
        try
        {
            IAimpLyrics wrapper = lyrics == IntPtr.Zero
                ? null
                : new AimpLyricsWrapper(AimpComHelper.AddRef(lyrics));

            var data = userData == IntPtr.Zero ? null : AimpString.Read(userData);
            LyricsReceive?.Invoke(wrapper, data);
        }
        catch (Exception exception)
        {
            AimpLog.Write(exception);
        }
    }

    protected override void OnDispose()
    {
        foreach (var pointer in _userDataStrings)
        {
            AimpComHelper.Release(pointer);
        }

        _userDataStrings.Clear();
        _callback = null;

        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}