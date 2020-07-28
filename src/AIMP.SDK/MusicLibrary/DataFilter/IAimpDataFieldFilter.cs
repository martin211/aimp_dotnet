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
    /// <summary>
    ///     Enum FieldFilterOperationType
    /// </summary>
    public enum FieldFilterOperationType
    {
        /// <summary>
        ///     The equals
        /// </summary>
        Equals = 0,

        /// <summary>
        ///     The not equals
        /// </summary>
        NotEquals = 1,

        /// <summary>
        ///     The between
        /// </summary>
        Between = 2,

        /// <summary>
        ///     The less than
        /// </summary>
        LessThan = 3,

        /// <summary>
        ///     The less than or equals
        /// </summary>
        LessThanOrEquals = 4,

        /// <summary>
        ///     The greater than
        /// </summary>
        GreaterThan = 5,

        /// <summary>
        ///     The greater than or equals
        /// </summary>
        GreaterThanOrEquals = 6,

        /// <summary>
        ///     Determines whether this instance contains the object.
        /// </summary>
        Contains = 7,

        /// <summary>
        ///     The begins with
        /// </summary>
        BeginsWith = 8,

        /// <summary>
        ///     The ends with
        /// </summary>
        EndsWith = 9
    }

    /// <summary>
    ///     Interface IAimpDataFieldFilter
    /// </summary>
    public interface IAimpDataFieldFilter
    {
        /// <summary>
        ///     Gets or sets the filter field.
        /// </summary>
        /// <value>The field.</value>
        string Field { get; set; }

        /// <summary>
        ///     Gets or sets the filter operation.
        /// </summary>
        /// <value>The operation.</value>
        FieldFilterOperationType Operation { get; set; }

        /// <summary>
        ///     Gets or sets the filter value.
        /// </summary>
        /// <value>The value1.</value>
        object Value1 { get; set; }

        /// <summary>
        ///     This value is used if the <see cref="IAimpDataFieldFilter.Operation" /> property is set to the
        ///     <see cref="FieldFilterOperationType.Between" /> value.
        /// </summary>
        /// <value>The value2.</value>
        object Value2 { get; set; }
    }
}