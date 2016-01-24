namespace AIMP.SDK.GUI.Controls
{
    using System;
    using System.Drawing;

    using AIMP.SDK.GUI.Controls.Events;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIControl : IAimpUIMouseEvents, IAimpUIMouseWheelEvents, IAimpUIPlacementEvents, IAimpUIPopupMenuEvents
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

        AimpActionResult ClientToScreen(out Point point);

        AimpActionResult ScreenToClient(out Point point);

        AimpActionResult Invalidate();

        AimpActionResult PaintTo(IntPtr parent, int x, int y);
    }
}