using AIMP.Internal;

namespace AIMP.SDK.Logger;

/// <summary>
/// Access to the logger used by the SDK and the plugin.
///
/// The SDK routes its own diagnostics through the logger the plugin
/// registers. Until then, and when a plugin does not provide one, messages
/// go to <see cref="InternalLogger"/> (<see cref="System.Diagnostics.Debug"/>).
/// </summary>
public static class AimpLogging
{
    /// <summary>
    /// Logger currently used by the SDK: the registered plugin logger or
    /// the default <see cref="InternalLogger"/>.
    /// </summary>
    public static IAimpLogger Logger => AimpLog.Logger;

    /// <summary>
    /// Registers the plugin logger.
    ///
    /// Call it from <see cref="AimpPlugin.Initialize"/> or override
    /// <see cref="AimpPlugin.InitializeLogger"/> instead. Passing
    /// <c>null</c> restores the default <see cref="InternalLogger"/>.
    /// </summary>
    /// <param name="logger">Plugin logger implementation.</param>
    public static void Register(IAimpLogger logger)
    {
        AimpLog.Register(logger);
    }

    /// <summary>
    /// Restores the default <see cref="InternalLogger"/>.
    /// </summary>
    public static void Reset()
    {
        AimpLog.Register(null);
    }
}