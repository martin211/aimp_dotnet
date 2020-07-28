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

using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    /// <summary>
    /// Interface IAimpDataFieldFilterByArray
    /// </summary>
    public interface IAimpDataFieldFilterByArray
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
        AimpActionResult GetData(IList<object> values);

        /// <summary>
        /// Sets the data.
        /// </summary>
        /// <param name="values">The values.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetData(IList<object> values);
    }
}