//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Lyrics.Objects;

namespace AIMP.SDK.Lyrics
{
    /// <summary>
    /// Enum LyricsFlags
    /// </summary>
    [Flags]
    public enum LyricsFlags
    {
        /// <summary>
        /// The none
        /// </summary>
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

    /// <summary>
    /// Delegate AimpServiceLyricsReceive
    /// </summary>
    /// <param name="lyrics">The lyrics.</param>
    /// <param name="userData">The user data.</param>
    public delegate void AimpServiceLyricsReceive(IAimpLyrics lyrics, string userData);

    /// <summary>
    /// Allowed access to the song text.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceLyrics : IAimpService
    {
        /// <summary>
        /// Gets a lyrics for file.
        /// </summary>
        /// <param name="fileInfo">The file info <see cref="IAimpFileInfo" />.</param>
        /// <param name="flags">The lyrics flags <see cref="LyricsFlags" />.</param>
        /// <param name="userData">A user data passed to function.</param>
        /// <returns>Return the <see cref="AimpActionResult" /> with async task id.</returns>
        AimpActionResult<IntPtr> Get(IAimpFileInfo fileInfo, LyricsFlags flags, string userData);

        /// <summary>
        /// Aborts a current active task.
        /// </summary>
        /// <param name="taskId">The task identifier.</param>
        /// <param name="flags">The flags.</param>
        /// <returns><see cref="AimpActionResult" /></returns>
        AimpActionResult Cancel(IntPtr taskId, LyricsFlags flags);

        /// <summary>
        /// Occurs when [lyrics receive].
        /// </summary>
        event AimpServiceLyricsReceive LyricsReceive;
    }
}
