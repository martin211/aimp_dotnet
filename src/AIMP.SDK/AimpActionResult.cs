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

    public class AimpActionResult
    {
        public AimpActionResult(ActionResultType resultType)
        {
            ResultType = resultType;
        }

        public ActionResultType ResultType { get; }
    }

    public class AimpActionResult<TObject> : AimpActionResult
    {
        public AimpActionResult(ActionResultType resultType, TObject result) : base(resultType)
        {
            if (resultType == ActionResultType.OK && result != null)
            {
                Result = result;
            }
        }

        public TObject Result { get; }
    }
}
