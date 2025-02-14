﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Interface IAimpDataFilter
    /// Implements the <see cref="AIMP.SDK.MusicLibrary.DataFilter.IAimpDataFilterGroup" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.MusicLibrary.DataFilter.IAimpDataFilterGroup" />
    public interface IAimpDataFilter : IAimpDataFilterGroup
    {
        /// <summary>
        /// Gets or sets the count of records to skip.
        /// </summary>
        /// <value>The offset.</value>
        int Offset { get; set; }

        /// <summary>
        /// Gets or sets the max count of records to return. 0 - maximum is not set.
        /// </summary>
        /// <value>The limit.</value>
        int Limit { get; set; }

        /// <summary>
        /// Gets or sets the field name for sorting. Can be null.
        /// </summary>
        /// <value>The sort by.</value>
        //IList<IAimpSortItem> SortByList { get; set; }
        List<IAimpSortItem> SortByList { get; set; }

        /// <summary>
        /// Gets or sets the search string. Can be null.
        /// </summary>
        /// <value>The search string.</value>
        string SearchString { get; set; }

        /// <summary>
        /// Code of character in the alphabetic index. 0 - character is not set.
        /// </summary>
        /// <value>The index of the alpha betic.</value>
        int AlphaBeticIndex { get; set; }

        /// <summary>
        /// Copies the data from a Source filter.
        /// Note: source filter must be assigned to same data storage.
        /// </summary>
        /// <param name="source">The source.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Assign(IAimpDataFilter source);

        /// <summary>
        /// Clones to the specified source.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpDataFilter&gt;.</returns>
        AimpActionResult<IAimpDataFilter> Clone();
    }
}
