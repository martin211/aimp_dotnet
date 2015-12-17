using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// AIMP Equalizer
    /// </summary>
    public interface IMAIMPEqualizer
    {
        /// <summary>
        /// Is equalizer enabled
        /// </summary>
        bool Enabled { get; set; }

        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider1000Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider10kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider125Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider12kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider14kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider1500Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider16kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider170Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider250Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider2kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider310Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider31Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider3kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider4kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider600Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider63Hz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider6kHz { get; set; }
        /// <summary>
        /// From -50 (-15.0 db) to 50 (15.0 db)
        /// </summary>
        int Slider8kHz { get; set; }

        /// <summary>
        /// Value of equalizer slider
        /// </summary>
        /// <param name="SliderID">Number of slider</param>
        /// <returns>Slider value</returns>
        int this[int SliderID]
        {
            get;
            set;
        }
        /// <summary>
        /// Number of equalizer sliders
        /// </summary>
        int SlidersCount { get; }

        /// <summary>
        /// Frequency value for each slider
        /// </summary>
        System.Collections.ObjectModel.ReadOnlyCollection<uint> SlidersValues
        {
            get;
        }
    }
}
