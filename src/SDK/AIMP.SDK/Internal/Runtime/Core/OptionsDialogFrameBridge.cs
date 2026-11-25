using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Options;
using AIMP.SDK.Options;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// Native <c>IAIMPOptionsDialogFrame</c> over a managed frame.
/// </summary>
[ComVisible(true)]
[ClassInterface(ClassInterfaceType.None)]
internal sealed class OptionsDialogFrameBridge :
    IAIMPOptionsDialogFrameNative,
    IAIMPOptionsDialogFrameKeyboardHelperNative,
    IAIMPOptionsDialogFrameKeyboardHelper2Native
{
    private readonly IAimpOptionsDialogFrame _frame;

    public OptionsDialogFrameBridge(IAimpOptionsDialogFrame frame)
    {
        _frame = frame ?? throw new ArgumentNullException(nameof(frame));
    }

    [PreserveSig]
    public int GetName(out IntPtr value)
    {
        value = AimpString.CreateNative(_frame.GetName() ?? string.Empty);
        return value == IntPtr.Zero ? unchecked((int)0x80004005) : 0;
    }

    [PreserveSig]
    public IntPtr CreateFrame(IntPtr parentWindow)
    {
        return _frame.CreateFrame(parentWindow);
    }

    [PreserveSig]
    public void DestroyFrame()
    {
        _frame.DestroyFrame();
    }

    [PreserveSig]
    public void Notification(int id)
    {
        _frame.Notification((OptionsDialogFrameNotificationType)id);
    }

    [PreserveSig]
    public int DialogKey(ushort charCode, int unused)
    {
        return Safe.Run(
            () =>
            {
                var helper = _frame as IAimpOptionsDialogFrameKeyboardHelper;
                return helper != null && helper.DialogKey(charCode) ? 1 : 0;
            },
            0);
    }

    [PreserveSig]
    public int SelectFirstControl()
    {
        return Safe.Run(
            () =>
            {
                var helper = _frame as IAimpOptionsDialogFrameKeyboardHelper;
                return helper != null && helper.SelectFirstControl() ? 1 : 0;
            },
            0);
    }

    [PreserveSig]
    public int SelectNextControl(int findForward, int checkTabStop)
    {
        return Safe.Run(
            () =>
            {
                var helper = _frame as IAimpOptionsDialogFrameKeyboardHelper;
                return helper != null && helper.SelectNextControl(findForward != 0, checkTabStop != 0) ? 1 : 0;
            },
            0);
    }

    [PreserveSig]
    public int SelectLastControl()
    {
        return Safe.Run(
            () =>
            {
                var helper = _frame as IAimpOptionsDialogFrameKeyboardHelper2;
                return helper != null && helper.SelectLastControl() ? 1 : 0;
            },
            0);
    }
}