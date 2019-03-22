﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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
    public interface IAimpServiceMusicLibraryUI
    {
        /// <summary>
        /// Gets the file list from table view.
        /// </summary>
        /// <param name="flags">The flags.</param>
        /// <param name="list">The list.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFiles(FilesType flags, out IAimpFileList list);

        /// <summary>
        /// Gets the grouping filter.
        /// </summary>
        /// <param name="filter">The filter.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetGroupingFilter(out IAimpDataFilter filter);

        /// <summary>
        /// Gets the grouping filter path.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetGroupingFilterPath(out string path);

        /// <summary>
        /// Sets the grouping filter path.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult SetGroupingFilterPath(string path);
    }
}