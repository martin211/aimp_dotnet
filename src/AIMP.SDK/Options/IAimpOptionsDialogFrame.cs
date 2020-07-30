// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;

namespace AIMP.SDK.Options
{
    /// <summary>
    /// Enum OptionsDialogFrameNotificationType
    /// </summary>
    public enum OptionsDialogFrameNotificationType
    {
        /// <summary>
        /// Custom frame should initialize all settings with values from configuration file.
        /// </summary>
        Load = 0x1,

        /// <summary>
        /// localization has been changed, custom frame should update localization of embedded controls.
        /// </summary>
        Localization = 0x2,

        /// <summary>
        /// Custom frame should save all settings to configuration file.
        /// </summary>
        Save = 0x3,

        /// <summary>
        /// Notification occurs before saving to an ability to validate settings.
        /// If one of settings is not valid - plugin should raise the exception. Note that text of exception will not shown to
        /// user.
        /// </summary>
        CanSave = 0x4
    }

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
}