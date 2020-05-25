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