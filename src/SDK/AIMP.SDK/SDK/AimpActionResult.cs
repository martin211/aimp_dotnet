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

using System.Diagnostics;
using AIMP.SDK.Objects;

namespace AIMP.SDK
{
    /// <summary>
    /// AIMP Operation Result.
    /// </summary>
    public enum ActionResultType : uint
    {
        /// <summary>
        /// Operation successful complete.
        /// </summary>
        OK = 0x00000000,

        /// <summary>
        /// General access denied error.
        /// </summary>
        AccessDenied = 0x80070005,

        /// <summary>
        /// Handle that is not valid.
        /// </summary>
        Handle = 0x80070006,

        /// <summary>
        /// One or more arguments are not valid.
        /// </summary>
        InvalidArguments = 0x80070057,

        /// <summary>
        /// Not implemented.
        /// </summary>
        NotImplemented = 0x80004001,

        /// <summary>
        /// Unexpected failure.
        /// </summary>
        Unexpected = 0x8000FFFF,

        /// <summary>
        /// Unspecified failure.
        /// </summary>
        Fail = 0x80004005
    }

    /// <summary>
    /// Class AimpActionResult.
    /// </summary>
    [DebuggerDisplay("{ResultType}")]
    public class AimpActionResult
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionResult"/> class.
        /// </summary>
        public AimpActionResult() : this(ActionResultType.Fail)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionResult" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        public AimpActionResult(ActionResultType resultType)
        {
            ResultType = resultType;
        }

        /// <summary>
        /// Gets the type of the result.
        /// </summary>
        /// <value>The type of the result.</value>
        public ActionResultType ResultType { get; }
    }

    /// <summary>
    /// Class AimpActionResult.
    /// Implements the <see cref="AIMP.SDK.AimpActionResult" />
    /// </summary>
    /// <typeparam name="TObject">The type of the t object.</typeparam>
    /// <seealso cref="AIMP.SDK.AimpActionResult" />
    [DebuggerDisplay("{ResultType, Result}")]
    public class AimpActionResult<TObject> : AimpActionResult
    {
        public AimpActionResult(TObject result) : base(ActionResultType.OK)
        {
            Result = result;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionResult{TObject}" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        public AimpActionResult() : base(ActionResultType.Fail)
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionResult{TObject}" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        public AimpActionResult(ActionResultType resultType) : base(resultType)
        {
            Result = default;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionResult{TObject}" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        /// <param name="result">The result.</param>
        public AimpActionResult(ActionResultType resultType, TObject result) : base(resultType)
        {
            if (resultType == ActionResultType.OK && !Equals(null, result))
            {
                Result = result;
            }
        }

        /// <summary>
        /// Gets the result.
        /// </summary>
        /// <value>The result.</value>
        public TObject Result { get; }
    }

    /// <summary>
    /// Class AimpActionResult.
    /// Implements the <see cref="AIMP.SDK.AimpActionResult" />
    /// </summary>
    /// <typeparam name="TObject1">The type of the t object1.</typeparam>
    /// <typeparam name="TObject2">The type of the t object2.</typeparam>
    /// <seealso cref="AIMP.SDK.AimpActionResult" />
    public class AimpActionResult<TObject1, TObject2> : AimpActionResult
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionResult{TObject1, TObject2}" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        /// <param name="obj1">The obj1.</param>
        /// <param name="obj2">The obj2.</param>
        public AimpActionResult(ActionResultType resultType, TObject1 obj1, TObject2 obj2) : base(resultType)
        {
            Item1 = obj1;
            Item2 = obj2;
        }

        /// <summary>
        /// Gets or sets the item1.
        /// </summary>
        /// <value>The item1.</value>
        public TObject1 Item1 { get; set; }

        /// <summary>
        /// Gets or sets the item2.
        /// </summary>
        /// <value>The item2.</value>
        public TObject2 Item2 { get; set; }
    }

    public sealed class StringActionResult : AimpActionResult<IAimpString>
    {
        /// <inheritdoc />
        public StringActionResult(ActionResultType resultType) : base(resultType)
        {
        }

        /// <inheritdoc />
        public StringActionResult(ActionResultType resultType, IAimpString result) : base(resultType, result)
        {
        }
    }

    public sealed class DoubleActionResult : AimpActionResult<double>
    {
        public DoubleActionResult(ActionResultType resultType) : base(resultType)
        {
        }

        public DoubleActionResult(ActionResultType resultType, double result) : base(resultType, result)
        {
        }
    }
}
