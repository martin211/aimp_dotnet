namespace AIMP.SDK.GUI.Controls
{
    using System;

    public interface IAimpUIWinControl : IAimpUIControl
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