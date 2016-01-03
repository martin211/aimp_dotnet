namespace AIMP.SDK.GUI.Controls.Events
{
    using System;
    public class AimpBeforeWndProcArgs : EventArgs
    {
        public int Message { get; set; }

        public int ParamW { get; set; }

        public int ParamL { get; set; }

        public int ResultL { get; set; }
    }
}