// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
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
    public interface IAimpServiceLyrics : IAimpService
    {
        /// <summary>
        /// Gets a lyrics for file.
        /// </summary>
        /// <param name="fileInfo"></param>
        /// <param name=""></param>
        /// <returns></returns>
        AimpActionResult<int> Get(IAimpFileInfo fileInfo, LyricsFlags flags, object userData);

        /// <summary>
        /// Aborts a current active task.
        /// </summary>
        /// <returns></returns>
        AimpActionResult Cancel(int taskId, LyricsFlags flags);

        /// <summary>
        /// 
        /// </summary>
        event AimpServiceLyricsReceive LyricsReceive;
    }
}