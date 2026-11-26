namespace AIMP.SDK.Options;

/// <summary>
/// Interface IAimpServiceOptionsDialog
/// Implements the <see cref="AIMP.SDK.IAimpService" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpService" />
public interface IAimpServiceOptionsDialog : IAimpService
{
    /// <summary>
    /// Frames the modified.
    /// </summary>
    /// <param name="frame">The frame.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult FrameModified(IAimpOptionsDialogFrame frame);

    /// <summary>
    /// Frames the show.
    /// </summary>
    /// <param name="frame">The frame.</param>
    /// <param name="forceShow">if set to <c>true</c> [force show].</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult FrameShow(IAimpOptionsDialogFrame frame, bool forceShow);

    /// <summary>
    /// Shows the settings frame for an <see cref="IAimpConfig"/> (AIMP 6.0+).
    /// </summary>
    AimpActionResult FrameShow(IAimpConfig config, bool forceShow);
}