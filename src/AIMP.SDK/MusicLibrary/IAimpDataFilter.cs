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

namespace AIMP.SDK.MusicLibrary
{
    public enum SortDirectionType
    {
        AIMPML_FILTER_SORTDIRECTION_ASCENDING = 0,
        AIMPML_FILTER_SORTDIRECTION_DESCENDING = 1
    }

    public interface IAimpDataFilter : IAimpDataFilterGroup
    {
        /// <summary>
        /// Gets or sets the offset.
        /// </summary>
        int Offset { get; set; }

        int Limit { get; set; }

        string SortBy { get; set; }

        /// <summary>
        /// Gets or sets the sort direction. AIMPML_FILTER_SORTBY
        /// </summary>
        /// <value>
        /// The sort direction.
        /// </value>
        SortDirectionType SortDirection { get; set; }

        string SearchString { get; set; }

        int AlphaBeticIndex { get; set; }

        AimpActionResult Assign(IAimpDataFieldFilter source);

        AimpActionResult Clone(out IAimpDataFilter source);
    }
}