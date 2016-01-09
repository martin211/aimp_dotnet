namespace AIMP.SDK.GUI.Controls.Events
{
    using System;
    using System.Drawing;

    public class AimpContextPopupArgs : EventArgs
    {
        public PointF Point { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public AimpContextPopupArgs(PointF point)
        {
            Point = point;
        }
    }
}