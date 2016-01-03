namespace AIMP.SDK.GUI.Controls.Events
{
    using System;
    using System.Drawing;

    public enum AimpUIMouseButton
    {
        umbLeft = 0,
        umbRight = 1,
        umbMiddle = 2
    };

    public class AimpMouseClickEventArgs : AimpMouseEventArgs
    {
        public AimpUIMouseButton Button { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpMouseClickEventArgs(PointF point, AimpUIModifiers modifiers, AimpUIMouseButton button)
            : base(point, modifiers)
        {
            Button = button;
        }
    }
}