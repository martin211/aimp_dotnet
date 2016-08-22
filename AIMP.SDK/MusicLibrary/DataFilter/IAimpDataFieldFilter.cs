using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public enum FieldFilterOperationType
    {
        AIMPML_FIELDFILTER_OPERATION_EQUALS,
        AIMPML_FIELDFILTER_OPERATION_NOTEQUALS,
        AIMPML_FIELDFILTER_OPERATION_BETWEEN,
        AIMPML_FIELDFILTER_OPERATION_LESSTHAN,
        AIMPML_FIELDFILTER_OPERATION_LESSTHANOREQUALS,
        AIMPML_FIELDFILTER_OPERATION_GREATERTHAN,
        AIMPML_FIELDFILTER_OPERATION_GREATERTHANOREQUALS,
        AIMPML_FIELDFILTER_OPERATION_CONTAINS,
        AIMPML_FIELDFILTER_OPERATION_BEGINSWITH,
        AIMPML_FIELDFILTER_OPERATION_ENDSWITH
    }

    public interface IAimpDataFieldFilter
    {
        /// <summary>
        /// Gets or sets the filter field.
        /// </summary>
        IAimpDataField Field { get; set; }

        FieldFilterOperationType Operation { get; set; }

        Variant Value1 { get; set; }

        Variant Value2 { get; set; }
    }
}