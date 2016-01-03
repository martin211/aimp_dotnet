namespace AIMP.SDK.GUI.Controls.Events
{
    using System.Drawing;

    public class AimpMouseMoveEventArgs : AimpMouseEventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpMouseMoveEventArgs(PointF point, AimpUIModifiers modifiers)
            : base(point, modifiers)
        {
        }
    }
}