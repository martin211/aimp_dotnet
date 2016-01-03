namespace AIMP.SDK.GUI.Controls.Events
{
    using System.Drawing;

    public class AimpMouseMoveArgs : AimpMouseArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpMouseMoveArgs(PointF point, AimpUIModifiers modifiers)
            : base(point, modifiers)
        {
        }
    }
}