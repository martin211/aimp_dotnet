using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public enum FieldFilterOperationType
    {
        AIMPML_FIELDFILTER_OPERATION_EQUALS = 0,
        AIMPML_FIELDFILTER_OPERATION_NOTEQUALS = 1,
        AIMPML_FIELDFILTER_OPERATION_BETWEEN = 2,
        AIMPML_FIELDFILTER_OPERATION_LESSTHAN = 3,
        AIMPML_FIELDFILTER_OPERATION_LESSTHANOREQUALS = 4,
        AIMPML_FIELDFILTER_OPERATION_GREATERTHAN = 5,
        AIMPML_FIELDFILTER_OPERATION_GREATERTHANOREQUALS = 6,
        AIMPML_FIELDFILTER_OPERATION_CONTAINS = 7,
        AIMPML_FIELDFILTER_OPERATION_BEGINSWITH = 8,
        AIMPML_FIELDFILTER_OPERATION_ENDSWITH = 9
    }

    public interface IAimpDataFieldFilter
    {
        /// <summary>
        /// Gets or sets the filter field.
        /// </summary>
        string Field { get; set; }

        FieldFilterOperationType Operation { get; set; }

        object Value1 { get; set; }

        object Value2 { get; set; }
    }
}