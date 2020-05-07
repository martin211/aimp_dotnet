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
using System;

namespace AIMP.SDK
{
    public class AimpErrorArgs : EventArgs
    {
        public AimpErrorArgs(ActionResultType aimpActionResult, string message)
        {
            ActionResultType = aimpActionResult;
            Message = message;
        }

        public AimpErrorArgs(ActionResultType aimpActionResult, string message, string stackTrace) : this(aimpActionResult, message)
        {
            StackTrace = stackTrace;
        }

        public ActionResultType ActionResultType { get; }

        public string Message { get; }

        public string StackTrace { get; set; }
    }

    public interface IAimpObject
    {
        event EventHandler<AimpErrorArgs> AimpObjectError;
    }
}