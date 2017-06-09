// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    [Flags]
    public enum CapabilitiesFlags
    {
        None = 0,
        HideAllData = 1,
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
        AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection);

        /// <summary>
        /// Gets the capabilities.
        /// </summary>
        CapabilitiesFlags GetCapabilities();

        /// <summary>
        /// Returns the data for next level of selected node in grouping tree.
        /// </summary>
        /// <param name="selection">The selection.</param>
        /// <param name="data">The data.</param>
        AimpActionResult GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data);

        /// <summary>
        /// Returns the name of top level field for alphabetic index.
        /// </summary>
        /// <param name="fieldName">Name of the field.</param>
        AimpActionResult GetFieldForAlphabeticIndex(out string fieldName);
    }
}