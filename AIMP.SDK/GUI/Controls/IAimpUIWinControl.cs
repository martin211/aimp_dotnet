namespace AIMP.SDK.GUI.Controls
{
    using System;

    using AIMP.SDK.GUI.Controls.Events;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIWinControl : IAimpUIControl, IAimpUIKeyboardEvents, IAimpUIWndProcEvents
    {
        bool Focused { get; set; }

        int TabOrder { get; set; }

        AimpActionResult GetControl(IAimpUIControl control, int index, string iid);

        int GetControlCount();

        IntPtr GetHandle();

        bool HasHandle();

        AimpActionResult SetFocus();
    }
}