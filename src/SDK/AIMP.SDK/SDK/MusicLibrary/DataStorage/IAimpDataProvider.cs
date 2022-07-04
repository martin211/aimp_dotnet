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
using AIMP.SDK.MusicLibrary.Extension;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Provides an access to data in data storage.
    /// Must be implemented by plugin on same level as the
    /// <see cref="AIMP.SDK.MusicLibrary.Extension.IAimpExtensionDataStorage" /> interface.
    /// You must use the <see cref="IAimpDataProvider2"/> instead of this interface if you data storage uses the page-by-page access method.
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpDataProvider
    {
        /// <summary>
        /// Gets the data.
        /// </summary>
        /// <param name="fields">List of field names that requires the data.
        /// List populates automatically in dependency what fields are used by user or marked as required.</param>
        /// <param name="filter">Plugin must take it into account, if the <see cref="CapabilitiesType.Filtering" /> flag is defined
        /// in the <see cref="AIMP.SDK.MusicLibrary.Extension.IAimpExtensionDataStorage.Capabilities" /> property value.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult" /></returns>
        AimpActionResult<object> GetData(IList<string> fields, IAimpDataFilter filter);
    }
}
