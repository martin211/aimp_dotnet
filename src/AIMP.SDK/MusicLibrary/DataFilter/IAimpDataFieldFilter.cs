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

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public enum FieldFilterOperationType
    {
        Equals = 0,
        NotEquals = 1,
        Between = 2,
        LessThan = 3,
        LessThanOrEquals = 4,
        GreaterThan = 5,
        GreaterThanOrEquals = 6,
        Contains = 7,
        BeginsWith = 8,
        EndsWith = 9
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
        /// This value is used if the <see cref="IAimpDataFieldFilter.Operation"/> property is set to the <see cref="FieldFilterOperationType.Between"/> value.
        /// </summary>
        object Value2 { get; set; }
    }
}