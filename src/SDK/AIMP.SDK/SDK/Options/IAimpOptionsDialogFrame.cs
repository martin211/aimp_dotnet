using System;

namespace AIMP.SDK.Options;

/// <summary>
/// Interface IAimpOptionsDialogFrame
/// Implements the <see cref="AIMP.SDK.IAimpExtension" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpExtension" />
public interface IAimpOptionsDialogFrame : IAimpExtension
{
    /// <summary>
    /// Gets the name.
    /// </summary>
    /// <returns>System.String.</returns>
    string GetName();

    /// <summary>
    /// Creates the frame.
    /// </summary>
    /// <param name="parentWindow">The parent window.</param>
    /// <returns>IntPtr.</returns>
    IntPtr CreateFrame(IntPtr parentWindow);

    /// <summary>
    /// Destroys the frame.
    /// </summary>
    void DestroyFrame();

    /// <summary>
    /// Occurs when [notification].
    /// </summary>
    /// <param name="id">The identifier.</param>
    void Notification(OptionsDialogFrameNotificationType id);
}