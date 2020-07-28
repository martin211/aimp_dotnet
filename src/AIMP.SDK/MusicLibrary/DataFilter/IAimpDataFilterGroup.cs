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
    /// <summary>
    /// Enum FilterGroupOperationType
    /// </summary>
    public enum FilterGroupOperationType
    {
        /// <summary>
        /// The or
        /// </summary>
        Or,
        /// <summary>
        /// The and
        /// </summary>
        And,
        /// <summary>
        /// The not or
        /// </summary>
        NotOr,
        /// <summary>
        /// The not and
        /// </summary>
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
        /// <value>The operation.</value>
        FilterGroupOperationType Operation { get; set; }

        /// <summary>
        /// Adds the new child filter to the group.
        /// </summary>
        /// <param name="field">The field name.</param>
        /// <param name="value1">The value1.</param>
        /// <param name="value2">The value2.</param>
        /// <param name="operation">The rule processing results from subsidiaries filters.</param>
        /// <returns>AimpActionResult&lt;IAimpDataFieldFilter&gt;.</returns>
        AimpActionResult<IAimpDataFieldFilter> Add(string field, object value1, object value2, FieldFilterOperationType operation);

        /// <summary>
        /// Adds the specified field.
        /// </summary>
        /// <param name="field">The field.</param>
        /// <param name="values">The values.</param>
        /// <param name="count">The count.</param>
        /// <returns>AimpActionResult&lt;IAimpDataFieldFilterByArray&gt;.</returns>
        AimpActionResult<IAimpDataFieldFilterByArray> Add(string field, object[] values, int count);

        /// <summary>
        /// Adds the child group.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpDataFilterGroup&gt;.</returns>
        AimpActionResult<IAimpDataFilterGroup> AddGroup();

        /// <summary>
        /// Clears the filter.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Clear();

        /// <summary>
        /// Deletes the filter by specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Gets the child group by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpDataFilterGroup&gt;.</returns>
        AimpActionResult<IAimpDataFilterGroup> GetFilterGroup(int index);

        /// <summary>
        /// Gets the child field filter by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpDataFieldFilter&gt;.</returns>
        AimpActionResult<IAimpDataFieldFilter> GetFieldFilter(int index);

        /// <summary>
        /// Gets the child count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetChildCount();

        /// <summary>
        /// Begins the update.
        /// </summary>
        void BeginUpdate();

        /// <summary>
        /// Ends the update.
        /// </summary>
        void EndUpdate();
    }
}