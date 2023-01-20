//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataStorage;

public class PaggedData
{
    public PaggedData(object data, string pageId)
    {
        Data = data;
        PageId = pageId;
    }

    /// <summary>
    /// Gets or sets the page data.
    /// </summary>
    public object Data { get; set; }
    
    /// <summary>
    /// Gets or sets the page identifier.
    /// </summary>
    public string PageId { get; set; }

    /// <summary>
    /// Gets or sets the no data text.
    /// </summary>
    public string NoData { get; set; }

    /// <summary>
    /// 
    /// </summary>
    public bool IsEmpty => !string.IsNullOrWhiteSpace(NoData);
}

/// <summary>
/// Provides an access to data in data storage.
/// Must be implemented by plugin on same level as the
/// <see cref="AIMP.SDK.MusicLibrary.Extension.IAimpExtensionDataStorage" /> interface.
/// You must use this interface instead of the <see cref="IAimpDataProvider"/> if you data storage uses the page-by-page access method.
/// Interface implementation must support asynchronous access.
/// </summary>
public interface IAimpDataProvider2
{
    /// <summary>
    /// Gets the data.
    /// </summary>
    /// <param name="fields">List of field names that requires the data.
    /// List populates automatically in dependency what fields are used by user or marked as required. </param>
    /// <param name="filter">The data filter.</param>
    /// <param name="pageId">Argument is used to page-by-page navigation if data storage supports it.</param>
    /// <returns>Operation result <seealso cref="AimpActionResult" /></returns>
    AimpActionResult<PaggedData> GetData(IList<string> fields, IAimpDataFilter filter, string pageId);
}