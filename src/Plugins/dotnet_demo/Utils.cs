﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

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
