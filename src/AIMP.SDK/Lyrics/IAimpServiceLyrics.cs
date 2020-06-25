// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK.FileManager;

namespace AIMP.SDK.Lyrics
{
    [Flags]
    public enum LyricsFlags
    {
        None = 0,

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
    public interface IAimpServiceLyrics : IAimpService
    {
        /// <summary>
        /// Gets a lyrics for file.
        /// </summary>
        /// <param name="fileInfo">The file info <see cref="IAimpFileInfo"/>.</param>
        /// <param name="flags">The lyrics flags <see cref="LyricsFlags"/>.</param>
        /// <param name="userData">A user data passed to function.</param>
        /// <returns>Return the <see cref="AimpActionResult"/> with async task id.</returns>
        AimpActionResult<IntPtr> Get(IAimpFileInfo fileInfo, LyricsFlags flags, object userData);

        /// <summary>
        /// Aborts a current active task.
        /// <param name="taskId">The task identity.</param>
        /// <param name="flags">The lyrics flags <see cref="LyricsFlags"/>.</param>
        /// </summary>
        /// <returns><see cref="AimpActionResult"/></returns>
        AimpActionResult Cancel(IntPtr taskId, LyricsFlags flags);

        /// <summary>
        /// 
        /// </summary>
        event AimpServiceLyricsReceive LyricsReceive;
    }
}