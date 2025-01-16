namespace AIMP.SDK.MusicLibrary;

public interface IAimpSortItem : IAimpSortDirection
{
    /// <summary>
    /// Gets or sets the sort field name.
    /// </summary>
    string FieldName { get; set; }
}
