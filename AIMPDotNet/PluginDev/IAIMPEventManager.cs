namespace dotNetInteropPlugin.PluginDev
{
    using System;

    /// <summary>
    /// AIMP Event Information
    /// </summary>
    [Serializable]
    public class AimpEventArgs : EventArgs
    {
        /// <summary>
        /// Creates concrete AIMP event argument
        /// </summary>
        /// <param name="evTp"></param>
        //public AimpEventArgs(AIMP2CallbackType evTp)
        //{
        //    _EventType = evTp;
        //}

        ///// <summary>
        ///// Event type
        ///// </summary>
        //public AIMP2CallbackType EventType
        //{
        //    get
        //    {
        //        return _EventType;
        //    }
        //}

        ///// <summary>
        ///// Raised on effects change
        ///// </summary>
        //public static readonly AimpEventArgs EffectChange = new AimpEventArgs(AIMP2CallbackType.AIMP_EFFECT_CHANGED);
        ///// <summary>
        ///// Raised on Equlizer sliders change
        ///// </summary>
        //public static readonly AimpEventArgs EQChange = new AimpEventArgs(AIMP2CallbackType.AIMP_EQ_CHANGED);
        ///// <summary>
        ///// Raise on playing info change
        ///// </summary>
        //public static readonly AimpEventArgs InfoUpdate = new AimpEventArgs(AIMP2CallbackType.AIMP_INFO_UPDATE);
        ///// <summary>
        ///// Raise on playing file
        ///// </summary>
        //public static readonly AimpEventArgs PalyFile = new AimpEventArgs(AIMP2CallbackType.AIMP_PLAY_FILE);
        ///// <summary>
        ///// Raise on player state change
        ///// </summary>
        //public static readonly AimpEventArgs PlayerState = new AimpEventArgs(AIMP2CallbackType.AIMP_PLAYER_STATE);
        ///// <summary>
        ///// Raise on status change
        ///// </summary>
        public static readonly AimpEventArgs StatusChange = new AimpEventArgs();
        ///// <summary>
        ///// Raise on track position change
        ///// </summary>
        //public static readonly AimpEventArgs TrackPosChange = new AimpEventArgs(AIMP2CallbackType.AIMP_TRACK_POS_CHANGED);

        //private AIMP2CallbackType _EventType;
    }

    /// <summary>
    /// Delegate for player events
    /// </summary>
    /// <param name="sender">Sender</param>
    /// <param name="args">Arguments</param>
    public delegate void AimpEventsDelegate(object sender, AimpEventArgs args);

    /// <summary>
    /// AIMP event manager interface.
    /// </summary>
    public interface IAimpEventManager
    {
        /// <summary>
        /// Status changed event.
        /// </summary>
        event AimpEventsDelegate StatusChanged;

        /// <summary>
        /// Player status changed event.
        /// </summary>
        event AimpEventsDelegate PlayerStatusChanged;

        /// <summary>
        /// 
        /// </summary>
        event AimpEventsDelegate TrackPositionChanged;
    }
}