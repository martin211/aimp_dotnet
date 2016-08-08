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
        FilterGroupOperationType Operation { get; set; }

        AimpActionResult Add(string field, uint value1, uint value2, FilterGroupOperationType operation, out IAimpDataFieldFilter filter);

        AimpActionResult Add(string field, uint[] values, int count, out IAimpDataFieldFilterByArray filter);

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

        //AimpActionResult GetChild(int index, );

        int GetChildCount();
    }
}