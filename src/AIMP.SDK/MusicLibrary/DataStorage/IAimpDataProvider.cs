// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Provides an access to data in data storage.
    /// Must be implemented by plugin on same level as the <see cref="AIMP.SDK.MusicLibrary.Extension.IAimpExtensionDataStorage"/> interface.
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpDataProvider
    {
        /// <summary>
        /// Gets the data.
        /// </summary>
        /// <param name="fields">List of field names that requires the data.
        /// List populates automatically in dependency what fields are used by user or marked as required.</param>
        /// <param name="filter">Plugin must take it into account, if the <see cref="AIMP.SDK.MusicLibrary.Extension.CapabilitiesType.AIMPML_DATASTORAGE_CAP_FILTERING"/> flag is defined in the <see cref="AIMP.SDK.MusicLibrary.Extension.IAimpExtensionDataStorage.Capabilities"/> property value.</param>
        /// <param name="data">Can be: <see cref="IAimpDataProviderSelection"/> or string - text information that displays to user in table of Music Library(formatting via simple BB codes are supported).</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetData(IList<string> fields, IAimpDataFilter filter, out object data);
    }
}