namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public enum FilterGroupOperationType
    {
        OR,
        AND,
        NOTOR,
        NOTAND
    }

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
        /// <param name="filter">[out] The added filter.</param>
        AimpActionResult Add(string field, Variant value1, Variant value2, FilterGroupOperationType operation, out IAimpDataFieldFilter filter);

        AimpActionResult Add(string field, Variant[] values, int count, out IAimpDataFieldFilterByArray filter);

        /// <summary>
        /// Adds the child group.
        /// </summary>
        /// <param name="group">The group.</param>
        AimpActionResult AddGroup(out IAimpDataFilterGroup group);

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
        /// <returns></returns>
        AimpActionResult GetChild(int index, out IAimpDataFilterGroup group);

        /// <summary>
        /// Gets the child field filter by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fieldFilter">The field filter <seealso cref="IAimpDataFieldFilter"/>.</param>
        /// <returns></returns>
        AimpActionResult GetChild(int index, out IAimpDataFieldFilter fieldFilter);

        int GetChildCount();
    }
}