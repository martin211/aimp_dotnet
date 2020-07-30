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
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Enum CapabilitiesFlags
    /// </summary>
    [Flags]
    public enum CapabilitiesFlags
    {
        /// <summary>
        /// The none
        /// </summary>
        None = 0,

        /// <summary>
        /// The hide all data
        /// </summary>
        HideAllData = 1,

        /// <summary>
        /// The dont sort
        /// </summary>
        DontSort = 2
    }

    /// <summary>
    /// Interface provides an ability to specify custom data provider for a grouping tree.
    /// </summary>
    public interface IAimpGroupingTreeDataProvider
    {
        /// <summary>
        /// Plugin must build the data filter for table based on current Selection.
        /// </summary>
        /// <param name="filter">The filter.</param>
        /// <param name="selection">The selection.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection);

        /// <summary>
        /// Gets the capabilities.
        /// </summary>
        /// <returns>CapabilitiesFlags.</returns>
        CapabilitiesFlags GetCapabilities();

        /// <summary>
        /// Returns the data for next level of selected node in grouping tree.
        /// </summary>
        /// <param name="selection">The selection.</param>
        /// <returns>AimpActionResult&lt;IAimpGroupingTreeDataProviderSelection&gt;.</returns>
        AimpActionResult<IAimpGroupingTreeDataProviderSelection> GetData(IAimpGroupingTreeSelection selection);

        /// <summary>
        /// Returns the name of top level field for alphabetic index.
        /// </summary>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> GetFieldForAlphabeticIndex();
    }
}