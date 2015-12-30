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

    public struct AimpUIControlPlacement
    {
        public AimpUIControlAlignment Alignment { get; set; }

        public RectangleF AlignmentMargins { get; set; }

        public RectangleF Anchors { get; set; }

        public RectangleF Bounds { get; set; }
    }
}