using System;
using System.Drawing;

namespace AIMP.SDK.GUI.Controls
{
    public interface IAimpUIControl
    {
        string CustomData { get; set; }

        bool Enabled { get; set; }

        string Hint { get; set; }

        string Name { get; set; }

        IAimpUIWinControl Parent { get; set; }

        IAimpUIPopupMenu PopupMenu { get; set; }

        bool Visible { get; set; }

        AimpActionResult GetPlacement(out AimpUIControlPlacement placement);

        AimpActionResult GetPlacementConstraints(out AimpUIControlPlacementConstraints placementConstraints);

        AimpActionResult SetPlacement(AimpUIControlPlacement placement);

        AimpActionResult SetPlacementConstraints(AimpUIControlPlacementConstraints placementConstraints);

        AimpActionResult ClientToScreen(out PointF point);

        AimpActionResult ScreenToClient(out PointF point);

        AimpActionResult Invalidate();

        AimpActionResult PaintTo(IntPtr parent, int x, int y);
    }
}