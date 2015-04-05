using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{

    /// <summary>
    /// AIMP Event Information
    /// </summary>
    [Serializable]
    public class MAIMPPlayerEventArgs : EventArgs
    {
        /// <summary>
        /// Creates concrete AIMP event argument
        /// </summary>
        /// <param name="evTp"></param>
        public MAIMPPlayerEventArgs(AIMP2CallbackType evTp)
        {
            _EventType = evTp;
        }

        /// <summary>
        /// Event type
        /// </summary>
        public AIMP2CallbackType EventType
        {
            get
            {
                return _EventType;
            }
        }

        /// <summary>
        /// Raised on effects change
        /// </summary>
        public static readonly MAIMPPlayerEventArgs EffectChange = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_EFFECT_CHANGED);
        /// <summary>
        /// Raised on Equlizer sliders change
        /// </summary>
        public static readonly MAIMPPlayerEventArgs EQChange = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_EQ_CHANGED);
        /// <summary>
        /// Raise on playing info change
        /// </summary>
        public static readonly MAIMPPlayerEventArgs InfoUpdate = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_INFO_UPDATE);
        /// <summary>
        /// Raise on playing file
        /// </summary>
        public static readonly MAIMPPlayerEventArgs PalyFile = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_PLAY_FILE);
        /// <summary>
        /// Raise on player state change
        /// </summary>
        public static readonly MAIMPPlayerEventArgs PlayerState = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_PLAYER_STATE);
        /// <summary>
        /// Raise on status change
        /// </summary>
        public static readonly MAIMPPlayerEventArgs StatusChange = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_STATUS_CHANGE);
        /// <summary>
        /// Raise on track position change
        /// </summary>
        public static readonly MAIMPPlayerEventArgs TrackPosChange = new MAIMPPlayerEventArgs(AIMP2CallbackType.AIMP_TRACK_POS_CHANGED);

        private AIMP2CallbackType _EventType;
    }

    /// <summary>
    /// Delegate for player events
    /// </summary>
    /// <param name="sender">Sender</param>
    /// <param name="args">Arguments</param>
	public delegate void MAIMPPlayerEventsDelegate(object sender, MAIMPPlayerEventArgs args);
}
