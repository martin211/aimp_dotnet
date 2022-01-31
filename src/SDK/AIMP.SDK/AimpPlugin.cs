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
using System.IO;
using AIMP.SDK;

namespace AIMP
{
    /// <summary>
    /// AIMP plugin interface.
    /// Implements the <see cref="System.IDisposable" />
    /// </summary>
    /// <seealso cref="System.IDisposable" />
    public interface IAimpPlugin : IDisposable
    {
        /// <summary>
        /// Initializes this instance.
        /// </summary>
        void Initialize();
    }

    /// <summary>
    /// Base class for AIMP Plugin.
    /// Implements the <see cref="IAimpPlugin" />
    /// </summary>
    /// <seealso cref="IAimpPlugin" />
    public abstract class AimpPlugin : IAimpPlugin
    {
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
        /// Called when [initialize].
        /// </summary>
        /// <param name="player">The player.</param>
        /// <param name="unId">The un identifier.</param>
        public void OnInitialize(IAimpPlayer player, int unId)
        {
            PluginId = unId;
            AimpPlayer = player;
            var path = Path.GetDirectoryName(GetType().Assembly.Location);
            AppDomain.CurrentDomain.SetData("APPBASE", path);
            Environment.CurrentDirectory = path;
            Initialize();
        }
    }
}
