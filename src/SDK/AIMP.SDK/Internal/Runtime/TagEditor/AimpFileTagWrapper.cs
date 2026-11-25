using System;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Collections;
using AIMP.SDK.TagEditor;

namespace AIMP.Internal.Runtime.TagEditor;

/// <summary>
/// v1 <see cref="IAimpFileTag"/> (file info + tag properties).
/// </summary>
internal sealed class AimpFileTagWrapper : AimpFileInfoWrapper, IAimpFileTag
{
    private readonly AimpPropertyBag _tagProperties;

    public AimpFileTagWrapper(IntPtr ownedPointer)
        : base(ownedPointer)
    {
        _tagProperties = new AimpPropertyBag((IAIMPPropertyListNative)(object)NativeRaw);
    }

    public TagType TagId
    {
        get => (TagType)_tagProperties.GetInt32(AimpPropId.FileTagId);
        set => _tagProperties.SetInt32(AimpPropId.FileTagId, (int)value);
    }

    public bool DeleteOnSaving
    {
        get => _tagProperties.GetBool(AimpPropId.FileTagDeleteOnSaving);
        set => _tagProperties.SetBool(AimpPropId.FileTagDeleteOnSaving, value);
    }

    protected override void OnDispose()
    {
        _tagProperties.Dispose();
        base.OnDispose();
    }
}