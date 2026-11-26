using System;
using AIMP.SDK;

namespace DemoPlugin
{
    internal static class Utils
    {
        public static ActionResultType CheckResult(ActionResultType actionResult)
        {
            if (actionResult != ActionResultType.OK)
            {
                Logger.Instance.AddInfoMessage($"{Environment.StackTrace}: {actionResult}");
            }

            return actionResult;
        }
    }
}
