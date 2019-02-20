// ******************************************/
// Evgeniy Bogdan (c) 2019
// IAimpServiceLyrics.cs
// ******************************************/

using System;
using AIMP.SDK.FileManager;

namespace AIMP.SDK.Lyrics
{
    public enum LyricsFlags
    {
        /// <summary>
        /// Search without cache.
        /// </summary>
        Nocache = 1,

        /// <summary>
        /// The method will not return a control until the operation is completed.
        /// </summary>
        WaitFor = 4
    }

    public delegate void AimpServiceLyricsReceive(IAimpLyrics lyrics, object userData);

    /// <summary>
    /// Allowed access to the song text.
    /// </summary>
    public interface IAimpServiceLyrics
    {
        /// <summary>
        /// Gets a lyrics for file.
        /// </summary>
        /// <param name="fileInfo"></param>
        /// <param name=""></param>
        /// <returns></returns>
        AimpActionResult Get(IAimpFileInfo fileInfo, LyricsFlags flags, object userData, out IntPtr taskId);

        /// <summary>
        /// Aborts a current active task.
        /// </summary>
        /// <returns></returns>
        AimpActionResult Cancel(IntPtr taskId, LyricsFlags flags);

        /// <summary>
        /// 
        /// </summary>
        event AimpServiceLyricsReceive LyricsReceive;
    }
}