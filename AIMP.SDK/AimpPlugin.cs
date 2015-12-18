using System;

namespace AIMP.SDK
{
    using AIMP.SDK.Player;

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
    /// Base abstract class for AIMP Plugin.
    /// </summary>
    public abstract class AimpPlugin : MarshalByRefObject, IAimpPlugin
    {
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
            AimpPlayer = player;
            Initialize();
        }

        public int PluginId
        {
            get;
            set;
        }

        public IAimpPlayer AimpPlayer;

        public IAimpPlayer Player
        {
            get { return AimpPlayer; }
        }
    }
}
