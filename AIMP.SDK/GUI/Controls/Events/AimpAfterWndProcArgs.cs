using System;
using System.Collections.Generic;
using System.Linq;
namespace AIMP.SDK.GUI.Controls.Events
{
    public class AimpAfterWndProcArgs
    {
        public int Message { get; set; }

        public int ParamW { get; set; }

        public int ParamL { get; set; }

        public int ResultL { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.Object"/> class.
        /// </summary>
        public AimpAfterWndProcArgs(int message, int paramW, int paramL, int resultL)
        {
            Message = message;
            ParamW = paramW;
            ParamL = paramL;
            ResultL = resultL;
        }
    }
}
