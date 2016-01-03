namespace AIMP.SDK.GUI.Controls.Events
{
    using System.Drawing;

    public class AimpMouseWheelEventArgs : AimpMouseEventArgs
    {
        public int WheelDelta { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpMouseWheelEventArgs(PointF point, AimpUIModifiers modifiers, int wheelDelta)
            : base(point, modifiers)
        {
            WheelDelta = wheelDelta;
        }
    }
}