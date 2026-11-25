using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceFileStreaming"/>.
/// </summary>
internal sealed class AimpServiceFileStreaming : AimpObjectWrapper, IAimpServiceFileStreaming
{
    private readonly IAIMPServiceFileStreamingNative _native;

    public AimpServiceFileStreaming(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileStreamingNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<IAimpStream> CreateStreamForFile(
        string fileName,
        FileStreamingType flags,
        long offset,
        long size)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpStream>();
        }

        var text = AimpString.CreateNative(fileName ?? string.Empty);

        try
        {
            var hr = _native.CreateStreamForFile(text, (uint)flags, offset, size, out var pointer);

            if (hr < 0 || pointer == IntPtr.Zero)
            {
                return AimpResult.Fail<IAimpStream>();
            }

            var stream = new AimpStreamWrapper(pointer);
            AimpComHelper.Release(pointer);

            return AimpResult.Ok<IAimpStream>(stream);
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult<CreateStreamResult> CreateStreamForFileUri(string fileUrl)
    {
        if (_native == null)
        {
            return AimpResult.Fail<CreateStreamResult>();
        }

        var text = AimpString.CreateNative(fileUrl ?? string.Empty);

        try
        {
            var hr = _native.CreateStreamForFileURI(text, out var virtualFile, out var streamPointer);

            if (hr < 0)
            {
                return AimpResult.Fail<CreateStreamResult>();
            }

            IAimpStream stream = null;

            if (streamPointer != IntPtr.Zero)
            {
                stream = new AimpStreamWrapper(streamPointer);
                AimpComHelper.Release(streamPointer);
            }

            if (virtualFile != IntPtr.Zero)
            {
                AimpComHelper.Release(virtualFile);
            }

            return AimpResult.Ok(new CreateStreamResult(null, stream));
        }
        finally
        {
            AimpComHelper.Release(text);
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