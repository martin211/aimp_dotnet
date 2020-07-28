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

using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary
{
    public enum SortDirectionType
    {
        Ascending = 0,
        Descending = 1
    }

    public interface IAimpDataFilter : IAimpDataFilterGroup
    {
        /// <summary>
        /// Gets or sets the count of records to skip.
        /// </summary>
        int Offset { get; set; }

        /// <summary>
        /// Gets or sets the max count of records to return. 0 - maximum is not set.
        /// </summary>
        int Limit { get; set; }

        /// <summary>
        /// Gets or sets the field name for sorting. Can be null.
        /// </summary>
        string SortBy { get; set; }

        /// <summary>
        /// Gets or sets the sort direction. AIMPML_FILTER_SORTBY
        /// </summary>
        SortDirectionType SortDirection { get; set; }

        /// <summary>
        /// Gets or sets the search string. Can be null.
        /// </summary>
        string SearchString { get; set; }

        /// <summary>
        /// Code of character in the alphabetic index. 0 - character is not set.
        /// </summary>
        int AlphaBeticIndex { get; set; }

        /// <summary>
        /// Copies the data from a Source filter.
        /// Note: source filter must be assigned to same data storage.
        /// </summary>
        /// <param name="source">The source.</param>
        AimpActionResult Assign(IAimpDataFilter source);

        /// <summary>
        /// Clones to the specified source.
        /// </summary>
        AimpActionResult<IAimpDataFilter> Clone();
    }
}