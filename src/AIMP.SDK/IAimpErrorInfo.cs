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

using System;

namespace AIMP.SDK
{
    public class ErrorInfo
    {
        public ErrorInfo(int errorCode, string message, string details)
        {
            ErrorCode = errorCode;
            Message = message;
            Details = details;
        }

        public int ErrorCode { get; set; }

        public string Message { get; set; }

        public string Details { get; set; }
    }

    public interface IAimpErrorInfo : IAimpObject
    {
        AimpActionResult<ErrorInfo> GetInfo();

        AimpActionResult<string> GetInfoFormatted();

        void SetInfo(int errorCode, string message, string details);
    }
}
