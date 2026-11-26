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
/// v1 <see cref="IAimpServicePlayerEqualizer"/>.
/// </summary>
internal sealed class AimpServicePlayerEqualizer : AimpObjectWrapper, IAimpServicePlayerEqualizer
{
    private readonly IAIMPServicePlayerEqualizerNative _native;

    public AimpServicePlayerEqualizer(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServicePlayerEqualizerNative>(borrowedPointer);
    }

    public int GetBandCount() => _native?.GetBandCount() ?? 0;

    public DoubleActionResult GetBandFrequency(int bandIndex)
    {
        return _native != null && _native.GetBandFrequency(bandIndex, out var value) >= 0
            ? new DoubleActionResult(ActionResultType.OK, value)
            : new DoubleActionResult(ActionResultType.Fail);
    }

    public DoubleActionResult GetBandGain(int bandIndex)
    {
        return _native != null && _native.GetBandGain(bandIndex, out var value) >= 0
            ? new DoubleActionResult(ActionResultType.OK, value)
            : new DoubleActionResult(ActionResultType.Fail);
    }

    public AimpActionResult SetBandGain(int integer, double value)
    {
        return _native == null ? AimpResult.Fail() : AimpResult.From(_native.SetBandGain(integer, value));
    }

    public bool GetActive() => _native != null && _native.GetActive() != 0;

    public AimpActionResult SetActive(bool value)
    {
        return _native == null ? AimpResult.Fail() : AimpResult.From(_native.SetActive(value ? 1 : 0));
    }

    public AimpActionResult<double> GetPreamp()
    {
        return _native != null && _native.GetPreamp(out var value) >= 0
            ? AimpResult.Ok(value)
            : AimpResult.Fail<double>();
    }

    public AimpActionResult SetPreamp(double value)
    {
        return _native == null ? AimpResult.Fail() : AimpResult.From(_native.SetPreamp(value));
    }

    public AimpActionResult<IAimpEqualizerPreset> GetPreset()
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpEqualizerPreset>();
        }

        var iid = AimpIids.IAIMPEqualizerPreset;
        var hr = _native.GetPreset(in iid, out var pointer);

        return hr < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpEqualizerPreset>()
            : AimpResult.Ok<IAimpEqualizerPreset>(new AimpEqualizerPresetWrapper(pointer));
    }

    public AimpActionResult SetPreset(IAimpEqualizerPreset value)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPEqualizerPresetNative));

        try
        {
            return AimpResult.From(_native.SetPreset(pointer));
        }
        finally
        {
            AimpComHelper.Release(pointer);
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