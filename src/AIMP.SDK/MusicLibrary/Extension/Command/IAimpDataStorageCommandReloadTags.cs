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

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    /// <summary>
    /// Interface IAimpDataStorageCommandReloadTags
    /// </summary>
    public interface IAimpDataStorageCommandReloadTags
    {
        /// <summary>
        /// Reloads the tags.
        /// </summary>
        /// <param name="files">The files.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult ReloadTags(IAimpFileList files);
    }
}