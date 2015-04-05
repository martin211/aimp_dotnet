using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Contains information about playing order
    /// </summary>
    public interface IMAIMPPlayingOrderParams
    {
        /// <summary>
        /// Repeate current track
        /// </summary>
        bool IsRepeatTrack { get; set; }
        /// <summary>
        /// Action after end of playlist
        /// </summary>
        AIMPOnPlaylistEndAction OnPlaylistEndAction { get; set; }
        /// <summary>
        /// Repeate playlist with only one track
        /// </summary>
        bool IsNotRepeatePlaylistWithOneFile { get; set; }
        /// <summary>
        /// Is shuffle mode enabled
        /// </summary>
        bool IsShuffleMode { get; set; }
    }
}
