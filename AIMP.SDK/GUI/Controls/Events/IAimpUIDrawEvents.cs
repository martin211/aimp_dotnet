using System;
using System.Drawing;

namespace AIMP.SDK.GUI.Controls.Events
{
    public class AimpDrawEventArgs : EventArgs
    {
        public IntPtr DC { get; private set; }

        public Rectangle Rectangle { get; private set; }

        public AimpDrawEventArgs(IntPtr dc, Rectangle rectangle)
        {
            DC = dc;
            Rectangle = rectangle;
        }
    }

    public interface IAimpUIDrawEvents
    {
        event AimpUIControlEventHandler<AimpDrawEventArgs> OnDraw;
    }
}