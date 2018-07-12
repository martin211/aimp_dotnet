// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;

namespace AIMP.SDK
{
    using Player;

    /// <summary>
    /// AIMP plugin interface.
    /// </summary>
    public interface IAimpPlugin : IDisposable
    {
        /// <summary>
        /// Initializes this instance.
        /// </summary>
        void Initialize();
    }

    /// <summary>
    /// Base class for AIMP Plugin.
    /// </summary>
    public abstract class AimpPlugin : IAimpPlugin
    {
        public IAimpPlayer AimpPlayer;

        /// <summary>
        /// Gets or sets the plugin identifier.
        /// </summary>
        public int PluginId { get; set; }

        public IAimpPlayer Player => AimpPlayer;

        /// <summary>
        /// Inside this function, plugin should perform all initialization
        /// </summary>
        public abstract void Initialize();

        /// <summary>
        /// Inside this function, plugin should dispose all resources
        /// </summary>
        public abstract void Dispose();

        internal void OnDispose()
        {
            Dispose();
#if DEBUG
            if (AimpPlayer == null)
                System.Diagnostics.Debugger.Break();
#endif
            if (AimpPlayer != null)
            {
                AimpPlayer.Dispose();
                AimpPlayer = null;
            }
        }

        internal void OnInitialize(IAimpPlayer player, int unId)
        {
#if DEBUG
            if (player == null)
                System.Diagnostics.Debugger.Break();
#endif
            PluginId = unId;
            AimpPlayer = (IAimpPlayer)player;
            Initialize();
        }
    }
}