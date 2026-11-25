using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Objects;
using AIMP.SDK.Player.Objects;

namespace AIMP.Internal.Runtime.Player;

/// <summary>
/// v1 <see cref="IAimpEqualizerPreset"/>.
/// </summary>
internal sealed class AimpEqualizerPresetWrapper : AimpObjectWrapper, IAimpEqualizerPreset, IAimpNativeObject
{
    private readonly IntPtr _pointer;
    private readonly IAIMPEqualizerPresetNative _native;

    public AimpEqualizerPresetWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        _native = AimpComHelper.Wrap<IAIMPEqualizerPresetNative>(ownedPointer);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    public int GetBandCount() => _native.GetBandCount();

    public DoubleActionResult GetBandFrequency(int bandIndex)
    {
        return _native.GetBandFrequency(bandIndex, out var value) >= 0
            ? new DoubleActionResult(ActionResultType.OK, value)
            : new DoubleActionResult(ActionResultType.Fail);
    }

    public DoubleActionResult GetBandGain(int bandIndex)
    {
        return _native.GetBandGain(bandIndex, out var value) >= 0
            ? new DoubleActionResult(ActionResultType.OK, value)
            : new DoubleActionResult(ActionResultType.Fail);
    }

    public AimpActionResult SetBandGain(int integer, double value)
    {
        return AimpResult.From(_native.SetBandGain(integer, value));
    }

    public StringActionResult GetName()
    {
        return _native.GetName(out var pointer) < 0 || pointer == IntPtr.Zero
            ? new StringActionResult(ActionResultType.Fail)
            : new StringActionResult(ActionResultType.OK, new AimpStringWrapper(pointer));
    }

    public AimpActionResult SetName(IAimpString value)
    {
        var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPStringNative));

        try
        {
            return AimpResult.From(_native.SetName(pointer));
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