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

        public RectangleF AlignmentMargins { get; set; }

        public RectangleF Anchors { get; set; }

        public RectangleF Bounds { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.Object"/> class.
        /// </summary>
        public AimpUIControlPlacement(AimpUIControlAlignment alignment, RectangleF alignmentMargins, RectangleF anchors, RectangleF bounds)
        {
            Alignment = alignment;
            AlignmentMargins = alignmentMargins;
            Anchors = anchors;
            Bounds = bounds;
        }
    }
}