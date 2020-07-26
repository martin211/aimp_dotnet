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

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public enum FilterGroupOperationType
    {
        Or,
        And,
        NotOr,
        NotAnd
    }

    /// <summary>
    /// Provides an ability to group few filters.
    /// </summary>
    public interface IAimpDataFilterGroup
    {
        /// <summary>
        /// Gets or sets the rule processing results from subsidiaries filters.
        /// </summary>
        FilterGroupOperationType Operation { get; set; }

        /// <summary>
        /// Adds the new child filter to the group.
        /// </summary>
        /// <param name="field">The field name.</param>
        /// <param name="value1">The value1.</param>
        /// <param name="value2">The value2.</param>
        /// <param name="operation">The rule processing results from subsidiaries filters.</param>
        AimpActionResult<IAimpDataFieldFilter> Add(string field, object value1, object value2, FieldFilterOperationType operation);

        AimpActionResult<IAimpDataFieldFilterByArray> Add(string field, object[] values, int count);

        /// <summary>
        /// Adds the child group.
        /// </summary>
        AimpActionResult<IAimpDataFilterGroup> AddGroup();

        /// <summary>
        /// Clears the filter.
        /// </summary>
        AimpActionResult Clear();

        /// <summary>
        /// Deletes the filter by specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Gets the child group by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="group">The filter group <seealso cref="IAimpDataFilterGroup"/>.</param>
        AimpActionResult<IAimpDataFilterGroup> GetFilterGroup(int index);

        /// <summary>
        /// Gets the child field filter by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fieldFilter">The field filter <seealso cref="IAimpDataFieldFilter"/>.</param>
        AimpActionResult<IAimpDataFieldFilter> GetFieldFilter(int index);

        /// <summary>
        /// Gets the child count.
        /// </summary>
        int GetChildCount();

        void BeginUpdate();

        void EndUpdate();
    }
}