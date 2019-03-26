// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.Options
{
    using System;

    public enum OptionsDialogFrameNotificationType
    {
        /// <summary>
        /// Custom frame should initialize all settings with values from configuration file.
        /// </summary>
        AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOAD = 0x1,

        /// <summary>
        /// localization has been changed, custom frame should update localization of embedded controls.
        /// </summary>
        AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOCALIZATION = 0x2,

        /// <summary>
        /// Custom frame should save all settings to configuration file.
        /// </summary>
        AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_SAVE = 0x3,

        /// <summary>
        /// Notification occurs before saving to an ability to validate settings.
        /// If one of settings is not valid - plugin should raise the exception. Note that text of exception will not shown to user.
        /// </summary>
        AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_CAN_SAVE = 0x4
    }

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
        void Notification(OptionsDialogFrameNotificationType id);
    }
}