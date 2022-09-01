//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    /// <summary>
    /// Interface IAimpDataFieldFilterByArray
    /// </summary>
    public interface IAimpDataFieldFilterByArray : IAimpFilter
    {
        /// <summary>
        /// Gets or sets the filter field.
        /// </summary>
        /// <value>The field.</value>
        string Field { get; set; }

        /// <summary>
        /// Gets the data.
        /// </summary>
        /// <param name="values">The values.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult<IList<object>> GetData();

        /// <summary>
        /// Sets the data.
        /// </summary>
        /// <param name="values">The values.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetData(IList<object> values);
    }
}
