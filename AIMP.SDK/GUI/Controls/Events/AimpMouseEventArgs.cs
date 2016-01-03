namespace AIMP.SDK.GUI.Controls.Events
{
    using System;
    using System.Drawing;

    [Flags]
    public enum AimpUIModifiers
    {
        AIMPUI_FLAGS_MOD_ALT = 1,

        AIMPUI_FLAGS_MOD_CTRL = 2,

        AIMPUI_FLAGS_MOD_SHIFT = 4
    }

    public abstract class AimpMouseEventArgs : EventArgs
    {
        public PointF Point { get; set; }

        public AimpUIModifiers Modifiers { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        protected AimpMouseEventArgs(PointF point, AimpUIModifiers modifiers)
        {
            Point = point;
            Modifiers = modifiers;
        }
    }
}