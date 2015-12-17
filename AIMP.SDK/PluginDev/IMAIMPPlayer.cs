using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Player
    /// </summary>
    public interface IMAIMPPlayerFirstLevel: IDisposable
    {
        /// <summary>
        /// Audio channel balance (form -50 to 50)
        /// </summary>
        int ChanelBallance { get; set; }
        /// <summary>
        /// Is mute
        /// </summary>
        bool IsMute { get; set; }
        /// <summary>
        /// Volume
        /// </summary>
        uint Volume { get; set; }
        /// <summary>
        /// Player state
        /// </summary>
        AIMPPlayingState PlayingState { get; }
        /// <summary>
        /// Player version
        /// </summary>
        uint Version { get; }

        /// <summary>
        /// Working with configuration file
        /// </summary>
        IMAIMPConfigurationManager ConfigurationManager { get; }
        /// <summary>
        /// Working with language file
        /// </summary>
        IMAIMPLanguageManager LanguageManager { get; }
        /// <summary>
        /// Player effects
        /// </summary>
        IMAIMPEffects Effects { get; }
        /// <summary>
        /// Information about currently playing track
        /// </summary>
        IMAIMPCurrentPlayingInfo CurrentPlayingInfo { get; }
        /// <summary>
        /// Information about playing order
        /// </summary>
        IMAIMPPlayingOrderParams PlayingOrderParams { get; }
        /// <summary>
        /// Additional parameters
        /// </summary>
        IMAIMPAdditionalParams AdditionalParams { get; }
        /// <summary>
        /// AIMP Equalizer
        /// </summary>
        IMAIMPEqualizer Equalizer { get; }
        /// <summary>
        /// Working with platlists
        /// </summary>
        IMAIMPPlaylistManager PlaylistManager { get; }
        /// <summary>
        /// Working with cover arts
        /// </summary>
        IMAIMPCoverArtManager CoverArtManager { get; }
        /// <summary>
        /// AIMP events
        /// </summary>
        IMAIMPEventManager EventManager { get; }

        /// <summary>
        /// Play next track
        /// </summary>
        void NextTrack();
        /// <summary>
        /// Pause
        /// </summary>
        void Pause();
        /// <summary>
        /// Play
        /// </summary>
        void Play();
        /// <summary>
        /// Play previous track
        /// </summary>
        void PrevTrack();
        /// <summary>
        /// Stop
        /// </summary>
        void Stop();
    }

}
