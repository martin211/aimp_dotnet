using System;
using AIMP.SDK;

namespace DemoPlugin
{
    internal static class Utils
    {
        public static AimpActionResult CheckResult(AimpActionResult actionResult)
        {
            if (actionResult != AimpActionResult.Ok)
            {
                Logger.Instance.AddInfoMessage($"{Environment.StackTrace}: {actionResult}");
            }

            return actionResult;
        }
    }
}