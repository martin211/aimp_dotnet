using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.TagEditor;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.TagEditor;

namespace AIMP.Internal.Runtime.TagEditor;

/// <summary>
/// v1 <see cref="IAimpFileTagEditor"/>.
/// </summary>
internal sealed class AimpFileTagEditorWrapper : AimpObjectWrapper, IAimpFileTagEditor
{
    private readonly IAIMPFileTagEditorNative _native;

    public AimpFileTagEditorWrapper(IntPtr ownedPointer)
    {
        _native = AimpComHelper.Wrap<IAIMPFileTagEditorNative>(ownedPointer);
    }

    public AimpActionResult<IAimpFileInfo> GetMixedInfo()
    {
        return _native.GetMixedInfo(out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpFileInfo>()
            : AimpResult.Ok<IAimpFileInfo>(new AimpFileInfoWrapper(pointer));
    }

    public AimpActionResult<IAimpFileTag> GetTag(int index)
    {
        var iid = AimpIids.IAIMPFileTag;

        return _native.GetTag(index, in iid, out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpFileTag>()
            : AimpResult.Ok<IAimpFileTag>(new AimpFileTagWrapper(pointer));
    }

    public int GetTagCount() => _native.GetTagCount();

    public AimpActionResult SetToAll(IAimpFileInfo fileInfo)
    {
        var pointer = AimpBridgeHelper.GetPointer(fileInfo, typeof(IAIMPFileInfoNative));

        try
        {
            return AimpResult.From(_native.SetToAll(pointer));
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult Save() => AimpResult.From(_native.Save());

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}