using System;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Base abstract class for AIMP Plugin.
    /// </summary>
    public abstract class AimpPluginBase: MarshalByRefObject
    {
        /// <summary>
        /// If true, then plugin has setting dialog
        /// </summary>
        public abstract bool HasSettingDialog
        {
            get;
        }

        /// <summary>
        /// Show settings dialog
        /// </summary>
        /// <param name="parentWindow">Parent window</param>
        public abstract void ShowSettingDialog(System.Windows.Forms.IWin32Window parentWindow);
        
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

        internal int PluginId
        {
            get;
            set;
        }

        internal IAimpPlayer AimpPlayer;

        internal IAimpPlayer PlayerFLvl
        {
            get {return AimpPlayer;}
        }
    }
}
