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
        public AimpErrorArgs(AimpActionResult aimpActionResult, string message)
        {
            AimpActionResult = aimpActionResult;
            Message = message;
        }

        public AimpErrorArgs(AimpActionResult aimpActionResult, string message, string stackTrace) : this(aimpActionResult, message)
        {
            StackTrace = stackTrace;
        }

        public AimpActionResult AimpActionResult { get; }

        public string Message { get; }

        public string StackTrace { get; set; }
    }

    public interface IAimpObject
    {
        event EventHandler<AimpErrorArgs> AimpObjectError;
    }
}