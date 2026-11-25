using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Options;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Options;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceOptionsDialog"/>.
/// </summary>
internal sealed class AimpServiceOptionsDialog : AimpObjectWrapper, IAimpServiceOptionsDialog
{
    private readonly IAIMPServiceOptionsDialogNative _native;

    public AimpServiceOptionsDialog(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceOptionsDialogNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult FrameModified(IAimpOptionsDialogFrame frame)
    {
        return Execute(frame, (pointer) => _native.FrameModified(pointer));
    }

    public AimpActionResult FrameShow(IAimpOptionsDialogFrame frame, bool forceShow)
    {
        return Execute(frame, (pointer) => _native.FrameShow(pointer, forceShow ? 1 : 0));
    }

    public AimpActionResult FrameShow(IAimpConfig config, bool forceShow)
    {
        AimpApiGuard.Require(6, 0, "IAimpServiceOptionsDialog.FrameShow(IAimpConfig)");

        if (_native == null || config == null)
        {
            return AimpResult.Fail();
        }

        var pointer = config is IAimpNativeObject native
            ? native.NativePointer
            : Marshal.GetIUnknownForObject(config);

        try
        {
            return AimpResult.From(_native.FrameShow(pointer, forceShow ? 1 : 0));
        }
        finally
        {
            if (pointer != IntPtr.Zero)
            {
                Marshal.Release(pointer);
            }
        }
    }

    private AimpActionResult Execute(IAimpOptionsDialogFrame frame, Func<IntPtr, int> action)
    {
        if (_native == null || frame == null)
        {
            return AimpResult.Fail();
        }

        // The managed frame is not a native object; pin a CCW adapter for it.
        var bridge = new OptionsDialogFrameBridge(frame);
        var pointer = AimpComHelper.GetPointer(bridge, typeof(IAIMPOptionsDialogFrameNative));

        return AimpResult.From(action(pointer));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}