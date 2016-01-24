using System.Drawing;

namespace AIMP.SDK.GUI.Controls
{
    public enum AimpUIControlAlignment
    {
        ualNone = 0,
        ualTop = 1,
        ualBottom = 2,
        ualLeft = 3,
        ualRight = 4,
        ualClient = 5
    }

    // ReSharper disable once InconsistentNaming
    public struct AimpUIControlPlacement
    {
        public AimpUIControlAlignment Alignment { get; set; }

        public Rectangle AlignmentMargins { get; set; }

        public Rectangle Anchors { get; set; }

        public Rectangle Bounds { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.Object"/> class.
        /// </summary>
        public AimpUIControlPlacement(AimpUIControlAlignment alignment, Rectangle alignmentMargins, Rectangle anchors, Rectangle bounds)
        {
            Alignment = alignment;
            AlignmentMargins = alignmentMargins;
            Anchors = anchors;
            Bounds = bounds;
        }
    }
}