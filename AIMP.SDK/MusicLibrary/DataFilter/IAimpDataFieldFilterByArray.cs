namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public interface IAimpDataFieldFilterByArray
    {
        /// <summary>
        /// Gets or sets the filter filed.
        /// </summary>
        string Filed { get; set; }

        AimpActionResult GetData(uint[] values, int count);

        AimpActionResult SetData(uint[] values, int count);
    }
}