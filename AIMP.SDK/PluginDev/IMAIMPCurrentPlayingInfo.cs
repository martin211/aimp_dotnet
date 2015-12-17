using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Information about currently playing track
    /// </summary>
    public interface IMAIMPCurrentPlayingInfo
    {
        /// <summary>
        /// BitRate
        /// </summary>
        UInt32 KBPS { get; }
        /// <summary>
        /// Discretization frequency
        /// </summary>
        UInt32 KHZ { get; }
        /// <summary>
        /// Track position
        /// </summary>
        TimeSpan Position { get; set; }
        /// <summary>
        /// Track length
        /// </summary>
        TimeSpan Length { get; }
        /// <summary>
        /// Number of audio channel
        /// </summary>
        UInt32 ChanelNumber { get; }

        /// <summary>
        /// Is radio stream
        /// </summary>
        bool IsRadioCapture { get; }

        /// <summary>
        /// Stream type of current track
        /// </summary>
        AIMPStreamType StreamType { get; }


        /// <summary>
        /// Get Information about currently playing track
        /// </summary>
        /// <returns>Information</returns>
        MAIMPFileInfo GetCurrentTrackInfo();
    }
}
