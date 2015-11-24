using System;

namespace AIMP.SDK.Services.Options
{
    /// <summary>
    /// 
    /// </summary>
    /// <param name="id">The identifier.</param>
    public delegate void AimpOptionFrameHandler(int id);

    /// <summary>
    /// 
    /// </summary>
    public interface IAimpOptionsDialogFrame : IAimpExtension
    {
        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <returns></returns>
        string GetName();

        /// <summary>
        /// Creates the frame.
        /// </summary>
        /// <param name="parentWindow">The parent window.</param>
        /// <returns></returns>
        IntPtr CreateFrame(IntPtr parentWindow);

        /// <summary>
        /// Destroys the frame.
        /// </summary>
        void DestroyFrame();

        /// <summary>
        /// Occurs when [notification].
        /// </summary>
        event AimpOptionFrameHandler Notification;
    }
}