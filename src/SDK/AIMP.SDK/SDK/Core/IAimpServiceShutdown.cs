//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.Core
{
    /// <summary>
    /// The shutdown type enum
    /// </summary>
    [Flags]
    public enum ShutdownType : uint
    {
        /// <summary>
        /// Hibernate
        /// </summary>
        Hibernate = 0x1,

        /// <summary>
        /// Power off
        /// </summary>
        PowerOff = 0x2,

        /// <summary>
        /// Sleep
        /// </summary>
        Sleep = 0x3,

        /// <summary>
        /// Reboot
        /// </summary>
        Reboot = 0x4,

        /// <summary>
        /// Log off
        /// </summary>
        LogOff = 0x5,

        /// <summary>
        /// Close app
        /// </summary>
        CloseApp = 0x10,

        /// <summary>
        /// No confirm
        /// </summary>
        NoConfirm = 0x20
    }

    /// <summary>
    /// Interface IAIMPServiceShutdown provides an ability to shutdown Windows or the application.
    /// </summary>
    public interface IAimpServiceShutdown
    {
        /// <summary>
        /// Restarts the specified arguments.
        /// </summary>
        /// <param name="arguments">Command line parameters, can be null.</param>
        AimpActionResult Restart(string arguments);

        /// <summary>
        /// Shutdowns the specified shutdown type.
        /// <p>
        /// Flags Hibernate, Shutdown, LogOff, Reboot and Sleep must not be used at same time.
        /// </p>
        /// <p>
        /// Flag CloseApp can be used only with Sleep or Hibernate.
        /// </p>
        /// </summary>
        /// <param name="shutdownType">Type of the shutdown.</param>
        AimpActionResult Shutdown(ShutdownType shutdownType);
    }
}
