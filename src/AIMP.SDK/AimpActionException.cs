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
    public class AimpActionException : Exception
    {
        public AimpActionException(ActionResultType resultType)
        {
            ResultType = resultType;
        }

        public AimpActionException(ActionResultType resultType, string message) : base(message)
        {
            ResultType = resultType;
        }

        public ActionResultType ResultType { get; }
    }
}