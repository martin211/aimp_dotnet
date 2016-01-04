namespace AIMP.SDK.GUI.Controls.Form
{
    using System;

    using AIMP.SDK.GUI.Controls.Events;

    public class AimpFormShortCutArgs : EventArgs
    {
        public int Key { get; set; }

        public AimpUIModifiers Modifiers { get; set; }

        public bool Handled { get; set; }
    }
}