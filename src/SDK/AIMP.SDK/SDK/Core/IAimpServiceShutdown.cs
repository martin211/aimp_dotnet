namespace AIMP.SDK.Core;

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