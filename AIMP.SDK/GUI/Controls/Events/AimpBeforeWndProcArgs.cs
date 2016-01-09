namespace AIMP.SDK.GUI.Controls.Events
{
    using System;
    public class AimpBeforeWndProcArgs : EventArgs
    {
        public int Message { get; set; }

        public int ParamW { get; set; }

        public int ParamL { get; set; }

        public int ResultL { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpBeforeWndProcArgs(int message, int paramW, int paramL, int resultL)
        {
            Message = message;
            ParamW = paramW;
            ParamL = paramL;
            ResultL = resultL;
        }
    }
}