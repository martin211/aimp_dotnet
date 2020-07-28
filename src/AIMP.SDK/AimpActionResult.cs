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

    [DebuggerDisplay("{ResultType}")]
    public class AimpActionResult
    {
        public AimpActionResult(ActionResultType resultType)
        {
            ResultType = resultType;
        }

        public ActionResultType ResultType { get; }
    }

    [DebuggerDisplay("{ResultType, Result}")]
    public class AimpActionResult<TObject> : AimpActionResult
    {
        public AimpActionResult(ActionResultType resultType) : base(resultType)
        {
            Result = default(TObject);
        }

        public AimpActionResult(ActionResultType resultType, TObject result) : base(resultType)
        {
            if (resultType == ActionResultType.OK && result != null)
            {
                Result = result;
            }
        }

        public TObject Result { get; }
    }

    public class AimpActionResult<TObject1, TObject2> : AimpActionResult
    {
        public AimpActionResult(ActionResultType resultType, TObject1 obj1, TObject2 obj2) : base(resultType)
        {
            Item1 = obj1;
            Item2 = obj2;
        }

        public TObject1 Item1 { get; set; }

        public TObject2 Item2 { get; set; }
    }
}
