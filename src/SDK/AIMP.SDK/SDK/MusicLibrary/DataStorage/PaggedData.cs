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