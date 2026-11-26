using System;
using System.Drawing;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Types;
using AIMP.Internal.Runtime.Actions;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.FileManager;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceFileInfoFormatterUtils"/>.
/// </summary>
internal sealed class AimpServiceFileInfoFormatterUtils : AimpObjectWrapper, IAimpServiceFileInfoFormatterUtils
{
    private readonly IAIMPServiceFileInfoFormatterUtilsNative _native;

    public AimpServiceFileInfoFormatterUtils(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileInfoFormatterUtilsNative>(borrowedPointer);
    }

    public AimpActionResult ShowMacrosLegend(RectangleF screenTarget, IAimpActionEvent actionEvent)
    {
        return ShowMacrosLegend(screenTarget, actionEvent, 0);
    }

    public AimpActionResult ShowMacrosLegend(RectangleF screenTarget, IAimpActionEvent actionEvent, int formatterId)
    {
        if (formatterId != 0)
        {
            AimpApiGuard.Require(6, 0, "IAimpServiceFileInfoFormatterUtils.ShowMacrosLegend(formatterId)");
        }

        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var rect = new AimpNativeRect
        {
            Left = (int)screenTarget.Left,
            Top = (int)screenTarget.Top,
            Right = (int)screenTarget.Right,
            Bottom = (int)screenTarget.Bottom
        };

        var handler = AimpActionEventBridge.CreatePointer(actionEvent);

        try
        {
            return AimpResult.From(_native.ShowMacrosLegend(rect, formatterId, handler));
        }
        finally
        {
            AimpComHelper.Release(handler);
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