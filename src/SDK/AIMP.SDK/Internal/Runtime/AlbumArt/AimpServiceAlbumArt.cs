using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.AlbumArt;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.AlbumArt;
using AIMP.SDK.AlbumArt.Services;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.AlbumArt;

/// <summary>
/// v1 <see cref="IAimpServiceAlbumArt"/>.
/// </summary>
internal sealed class AimpServiceAlbumArt : AimpObjectWrapper, IAimpServiceAlbumArt
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    private delegate void AlbumArtReceiveCallback(IntPtr image, IntPtr imageContainer, IntPtr userData);

    private readonly IAIMPServiceAlbumArtNative _native;
    private readonly AimpPropertyBag _properties;
    private AlbumArtReceiveCallback _callback;

    public AimpServiceAlbumArt(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceAlbumArtNative>(borrowedPointer);
        _properties = AimpPropertyBag.FromOwned(
            AimpComHelper.QueryInterface(borrowedPointer, AimpIids.IAIMPPropertyList));
    }

    public bool IsExists => _native != null;

    public event EventHandler<AimpGetAlbumArtEventArgs> Completed;

    public bool FindInFiles
    {
        get => _properties != null && _properties.GetBool(AimpPropId.AlbumArtFindInFiles);
        set => _properties?.SetBool(AimpPropId.AlbumArtFindInFiles, value);
    }

    public bool FindInInternet
    {
        get => _properties != null && _properties.GetBool(AimpPropId.AlbumArtFindInInternet);
        set => _properties?.SetBool(AimpPropId.AlbumArtFindInInternet, value);
    }

    public string[] FileMasks
    {
        get => ReadStringArray(AimpPropId.AlbumArtFindInFilesMasks);
        set => WriteStringArray(AimpPropId.AlbumArtFindInFilesMasks, value);
    }

    public string[] FileExtensions
    {
        get => ReadStringArray(AimpPropId.AlbumArtFindInFilesExtensions);
        set => WriteStringArray(AimpPropId.AlbumArtFindInFilesExtensions, value);
    }

    public int MaxFileSize
    {
        get => _properties?.GetInt32(AimpPropId.AlbumArtFindInInternetMaxFileSize) ?? 0;
        set => _properties?.SetInt32(AimpPropId.AlbumArtFindInInternetMaxFileSize, value);
    }

    public AimpActionResult<int> Get(
        string fileUrl,
        string artist,
        string album,
        AimpFindCovertArtType flags,
        object userData)
    {
        if (string.IsNullOrEmpty(fileUrl))
        {
            throw new ArgumentNullException(nameof(fileUrl), "Parameter fileUrl cannot be empty");
        }

        if (_native == null)
        {
            return AimpResult.Fail<int>();
        }

        var uri = AimpString.CreateNative(fileUrl);
        var artistText = AimpString.CreateNative(artist ?? string.Empty);
        var albumText = AimpString.CreateNative(album ?? string.Empty);
        var handle = GCHandle.Alloc(userData);

        _callback = OnReceive;

        try
        {
            var callback = Marshal.GetFunctionPointerForDelegate(_callback);
            var hr = _native.Get(
                uri,
                artistText,
                albumText,
                (uint)flags,
                callback,
                GCHandle.ToIntPtr(handle),
                out var taskId);

            if (hr < 0)
            {
                handle.Free();
                return AimpResult.Fail<int>();
            }

            return AimpResult.Ok((int)taskId.ToInt64());
        }
        finally
        {
            AimpComHelper.Release(uri);
            AimpComHelper.Release(artistText);
            AimpComHelper.Release(albumText);
        }
    }

    public AimpActionResult<int> Get2(
        IAimpFileInfo fileInfo,
        AimpFindCovertArtType flags,
        object userData)
    {
        if (_native == null)
        {
            return AimpResult.Fail<int>();
        }

        var info = AimpBridgeHelper.GetPointer(fileInfo, typeof(IAIMPFileInfoNative));
        var handle = GCHandle.Alloc(userData);

        _callback = OnReceive;

        try
        {
            var callback = Marshal.GetFunctionPointerForDelegate(_callback);
            var hr = _native.Get2(
                info,
                (uint)flags,
                callback,
                GCHandle.ToIntPtr(handle),
                out var taskId);

            if (hr < 0)
            {
                handle.Free();
                return AimpResult.Fail<int>();
            }

            return AimpResult.Ok((int)taskId.ToInt64());
        }
        finally
        {
            AimpComHelper.Release(info);
        }
    }

    public AimpActionResult Cancel(int taskId, AimpFindCovertArtType flags)
    {
        return _native == null
            ? AimpResult.Fail()
            : AimpResult.From(_native.Cancel(new IntPtr(taskId), (uint)flags));
    }

    private void OnReceive(IntPtr image, IntPtr imageContainer, IntPtr userData)
    {
        object data = null;

        if (userData != IntPtr.Zero)
        {
            var handle = GCHandle.FromIntPtr(userData);
            data = handle.Target;
            handle.Free();
        }

        try
        {
            IAimpImageContainer container = imageContainer == IntPtr.Zero
                ? null
                : new AimpImageContainerWrapper(AimpComHelper.AddRef(imageContainer));

            Completed?.Invoke(this, new AimpGetAlbumArtEventArgs(null, container, data));
        }
        catch (Exception exception)
        {
            AimpLog.Write(exception);
        }
    }

    private string[] ReadStringArray(int propertyId)
    {
        if (_properties == null)
        {
            return Array.Empty<string>();
        }

        var value = _properties.GetString(propertyId);

        return string.IsNullOrEmpty(value)
            ? Array.Empty<string>()
            : value.Split([';'], StringSplitOptions.RemoveEmptyEntries);
    }

    private void WriteStringArray(int propertyId, string[] value)
    {
        if (_properties == null)
        {
            return;
        }

        _properties.SetString(propertyId, value == null ? string.Empty : string.Join(";", value));
    }

    protected override void OnDispose()
    {
        _properties?.Dispose();
        _callback = null;

        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}