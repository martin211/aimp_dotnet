using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Contains addition operations, that doesn't correspond to other categories
    /// </summary>
    public interface IMAIMPAdditionalParams
    {
        /// <summary>
        /// Style of player's timer
        /// </summary>
        AIMPTimerDisplayStyle TimerDisplayStyle { get; set; }
        /// <summary>
        /// Is player window has TopMost state
        /// </summary>
        bool IsOnTopMost { get; set; }

        /// <summary>
        /// Get path to some player file
        /// </summary>
        /// <param name="elem">File</param>
        /// <returns>Path to file</returns>
        string GetPathTo(AIMPPathToFile elem);
        /// <summary>
        /// Load track information from file
        /// </summary>
        /// <param name="FilePath">Path to file</param>
        /// <returns>Track info</returns>
        MAIMPFileInfo GetTrackInfoFromFile(string FilePath);
        /// <summary>
        /// Load track information from file to MAIMPFileInfo object
        /// </summary>
        /// <param name="Dest">Object for storing loaded information</param>
        /// <param name="FilePath">Path to file</param>
        void GetTrackInfoFromFile(MAIMPFileInfo Dest, string FilePath);
        /// <summary>
        /// Load track information from file to MAIMPFileInfo object
        /// </summary>
        /// <param name="Dest">Object for storing loaded information. This object should contains a path to audio file.</param>
        void GetTrackInfoFromFile(MAIMPFileInfo Dest);

        /// <summary>
        /// Return supported extensions as string. Extensions are separated by ';'
        /// </summary>
        /// <param name="ExtType">Type of extension</param>
        /// <returns>Supported extensions</returns>
        string GetSupportedExtensions(AIMPExtensionType ExtType);

        /// <summary>
        /// Calling function in AIMP
        /// </summary>
        /// <param name="cf">Function, that should call</param>
        void CallFunction(AIMPCallFunction cf);



       // System.Windows.Forms.IWin32Window GetAIMPWindow(AIMPPlayerWindow WndType);
        //void TestFunc();
    }
}
