namespace AIMP.SDK.GUI.Controls
{
    using System;

    public interface IAimpUIWinControl : IAimpUIControl
    {
        bool Focused { get; set; }

        int TabOrder { get; set; }

        object GetControl(int index, string iid);

        int GetControlCount();

        IntPtr GetHandle();

        bool HasHandle { get; set; }

        void SetFocus();
    }
}