using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public interface IAimpDataFieldFilterByArray
    {
        /// <summary>
        /// Gets or sets the filter field.
        /// </summary>
        string Field { get; set; }

        AimpActionResult GetData(IList<object> values);

        AimpActionResult SetData(IList<object> values);
    }
}