using System;
using System.IO;
using AIMP.SDK.Logger;

namespace AIMP.SDK;

/// <summary>
/// Base class for AIMP Plugin.
/// Implements the <see cref="IAimpPlugin" />
/// </summary>
/// <seealso cref="IAimpPlugin" />
public abstract class AimpPlugin : IAimpPlugin
{
    /// <summary>
    /// Gets or sets the logger.
    /// </summary>
    public IAimpLogger Logger { get; private set; }

    /// <summary>
    /// Gets or sets the aimp player.
    /// </summary>
    /// <value>The aimp player.</value>
    public IAimpPlayer AimpPlayer { get; set; }

    /// <summary>
    /// Gets or sets the plugin identifier.
    /// </summary>
    /// <value>The plugin identifier.</value>
    public int PluginId { get; set; }

    /// <summary>
    /// Gets the main player interface <see cref="IAimpPlayer" />.
    /// </summary>
    /// <value>The player.</value>
    public IAimpPlayer Player => AimpPlayer;

    /// <summary>
    /// Inside this function, plugin should perform all initialization.
    /// </summary>
    public abstract void Initialize();

    /// <summary>
    /// Inside this function, plugin should dispose all resources.
    /// </summary>
    public abstract void Dispose();

    /// <summary>
    /// Initializes the logger.
    /// </summary>
    /// <returns></returns>
    public virtual IAimpLogger InitializeLogger()
    {
        return new InternalLogger();
    }

    /// <summary>
    /// Called when [dispose].
    /// </summary>
    public void OnDispose()
    {
        Dispose();
        if (AimpPlayer != null)
        {
            AimpPlayer.Dispose();
            AimpPlayer = null;
        }
    }

    /// <summary>
    /// Called when [pre initialize].
    /// </summary>
    /// <param name="player">The player.</param>
    public virtual void OnPreInitialize(IAimpPlayer player)
    {
        AimpPlayer = player;
    }

    /// <summary>
    /// Called when [initialize].
    /// </summary>
    /// <param name="player">The player.</param>
    /// <param name="unId">The un identifier.</param>
    public void OnInitialize(IAimpPlayer player, int unId)
    {
        PluginId = unId;
        var path = Path.GetDirectoryName(GetType().Assembly.Location);
        AppDomain.CurrentDomain.SetData("APPBASE", path);
        Environment.CurrentDirectory = path;

        Logger = InitializeLogger();
        AimpLogging.Register(Logger);

        Initialize();
    }
}