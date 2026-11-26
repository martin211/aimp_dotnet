using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Player.Objects;

namespace AIMP.Internal.Runtime.Player;

/// <summary>
/// v1 <see cref="IAimpServicePlayerEqualizerPresets"/>.
/// </summary>
internal sealed class AimpServicePlayerEqualizerPresets : AimpObjectWrapper, IAimpServicePlayerEqualizerPresets
{
    private readonly IAIMPServicePlayerEqualizerPresetsNative _native;

    public AimpServicePlayerEqualizerPresets(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServicePlayerEqualizerPresetsNative>(borrowedPointer);
    }

    public AimpActionResult<IAimpEqualizerPreset> Add(string name)
    {
        return WithName(name, (text) => _native.Add(text, InIid(), out var pointer) < 0
            ? null
            : new AimpEqualizerPresetWrapper(pointer));
    }

    public AimpActionResult<IAimpEqualizerPreset> FindByName(string name)
    {
        return WithName(name, (text) => _native.FindByName(text, InIid(), out var pointer) < 0
            ? null
            : new AimpEqualizerPresetWrapper(pointer));
    }

    public AimpActionResult Delete(IAimpEqualizerPreset preset)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var pointer = AimpBridgeHelper.GetPointer(preset, typeof(IAIMPEqualizerPresetNative));

        try
        {
            return AimpResult.From(_native.Delete(pointer));
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult Delete(int index)
    {
        return _native == null ? AimpResult.Fail() : AimpResult.From(_native.Delete2(index));
    }

    public AimpActionResult<IAimpEqualizerPreset> GetPreset(int index)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpEqualizerPreset>();
        }

        var iid = AimpIids.IAIMPEqualizerPreset;

        return _native.GetPreset(index, in iid, out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpEqualizerPreset>()
            : AimpResult.Ok<IAimpEqualizerPreset>(new AimpEqualizerPresetWrapper(pointer));
    }

    public int GetPresetCount() => _native?.GetPresetCount() ?? 0;

    private Guid InIid() => AimpIids.IAIMPEqualizerPreset;

    private AimpActionResult<IAimpEqualizerPreset> WithName(
        string name,
        Func<IntPtr, IAimpEqualizerPreset> action)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpEqualizerPreset>();
        }

        var text = AimpString.CreateNative(name ?? string.Empty);

        try
        {
            var result = action(text);

            return result == null
                ? AimpResult.Fail<IAimpEqualizerPreset>()
                : AimpResult.Ok(result);
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