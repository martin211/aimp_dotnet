using System.Drawing;
using AIMP.SDK.Actions.Objects;

namespace AIMP.SDK.FileManager;

/// <summary>
/// Service provides an ability to show context menu with the list of supported macros for the IAimpServiceFileInfoFormatter service. 
/// </summary>
public interface IAimpServiceFileInfoFormatterUtils
{
    /// <summary>
    /// Shows the macros legend.
    /// </summary>
    /// <param name="screenTarget">The placement of menu invoker in screen coordinates, context menu will not intersects this area.
    /// If you need to show context menu under mouse cursor, just defined the ScreenTarget as shown below:
    /// ScreenTarget.Left = ScreenTarget.Right = Cursor.X;
    /// ScreenTarget.Top = ScreenTarget.Bottom = Cursor.Y;</param>
    /// <param name="actionEvent">Refer to the IAIMPActionEvent.
    /// The Data parameter of the IAimpActionEvent.OnExecute method will contains selected macro as IAimpString.</param>
    AimpActionResult ShowMacrosLegend(RectangleF screenTarget, IAimpActionEvent actionEvent);

    /// <summary>
    /// Shows the macros legend for the specified formatter ID (AIMP 6.0+).
    /// </summary>
    AimpActionResult ShowMacrosLegend(RectangleF screenTarget, IAimpActionEvent actionEvent, int formatterId);
}