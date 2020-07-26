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

namespace AIMP.SDK.MusicLibrary
{
    public enum FilesType
    {
        All,
        Selected,
        Focused
    }

    /// <summary>
    /// Provides an access to data of UI elements for an active data storage that uses by the user.
    /// </summary>
    public interface IAimpServiceMusicLibraryUI : IAimpService
    {
        /// <summary>
        /// Gets the file list from table view.
        /// </summary>
        /// <param name="flags">The flags.</param>
        /// <param name="list">The list.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        AimpActionResult<IAimpFileList> GetFiles(FilesType flags);

        /// <summary>
        /// Gets the grouping filter.
        /// </summary>
        /// <param name="filter">The filter.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        AimpActionResult<IAimpDataFilter> GetGroupingFilter();

        /// <summary>
        /// Gets the grouping filter path.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        AimpActionResult<string> GetGroupingFilterPath();

        /// <summary>
        /// Sets the grouping filter path.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        AimpActionResult SetGroupingFilterPath(string path);
    }
}