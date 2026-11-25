namespace AIMP.SDK.MusicLibrary.DataFilter;

/// <summary>
/// Interface IAimpDataFieldFilter
/// </summary>
public interface IAimpDataFieldFilter : IAimpFilter
{
    /// <summary>
    /// Gets or sets the filter field.
    /// </summary>
    /// <value>The field.</value>
    string Field { get; set; }

    /// <summary>
    /// Gets or sets the filter operation.
    /// </summary>
    /// <value>The operation.</value>
    FieldFilterOperationType Operation { get; set; }

    /// <summary>
    /// Gets or sets the filter value.
    /// </summary>
    /// <value>The value1.</value>
    object Value1 { get; set; }

    /// <summary>
    /// This value is used if the <see cref="IAimpDataFieldFilter.Operation" /> property is set to the
    /// <see cref="FieldFilterOperationType.Between" /> value.
    /// </summary>
    /// <value>The value2.</value>
    object Value2 { get; set; }
}