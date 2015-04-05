using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// AIMP effects
    /// </summary>
    public interface IMAIMPEffects
    {
        /// <summary>
        /// Reverberation (from 0 to 100)
        /// </summary>
        uint Reverberation { get; set; }
        /// <summary>
        /// Echo (from 0 to 100)
        /// </summary>
        uint Echo { get; set; }
        /// <summary>
        /// Chorus (form 0 to 100)
        /// </summary>
        uint Chorus { get; set; }
        /// <summary>
        /// Flanger (from 0 to 100)
        /// </summary>
        uint Flanger { get; set; }
        /// <summary>
        /// Playing speed in percents (from 50% to 150%)
        /// </summary>
        uint Speed { get; set; }
    }
}
