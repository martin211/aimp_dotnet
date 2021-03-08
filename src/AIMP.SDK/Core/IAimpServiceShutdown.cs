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

namespace AIMP.SDK.Core
{
    [Flags]
    public enum ShutdownType : uint
    {
        Hibernate = 0x1,
        PowerOff = 0x2,
        Sleep = 0x3,
        Reboot = 0x4,
        LogOff = 0x5,
        CloseApp = 0x10,
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
