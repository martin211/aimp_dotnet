// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
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

        /// <summary>
        /// Gets or sets the filter operation.
        /// </summary>
        FieldFilterOperationType Operation { get; set; }

        /// <summary>
        /// Gets or sets the filter value.
        /// </summary>
        object Value1 { get; set; }

        /// <summary>
        /// This value is used if the <see cref="IAimpDataFieldFilter.Operation"/> property is set to the <see cref="FieldFilterOperationType.AIMPML_FIELDFILTER_OPERATION_BETWEEN"/> value.
        /// </summary>
        object Value2 { get; set; }
    }
}