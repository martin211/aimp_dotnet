//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Diagnostics.CodeAnalysis;
using JetBrains.Annotations;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.SonarScanner;

namespace Aimp.DotNet.Build
{
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    [Serializable]
    public class SonarBeginSettings : SonarScannerBeginSettings
    {
        public virtual string ProjectBaseDir { get; internal set; }

        public virtual string PvsStudioReportPath { get; internal set; }

        protected override Arguments ConfigureProcessArguments(Arguments arguments)
        {
            var args = base.ConfigureProcessArguments(arguments);
            args.Add("/d:sonar.projectBaseDir=\"{value}\"", ProjectBaseDir);

            if (!string.IsNullOrWhiteSpace(PvsStudioReportPath))
            {
                args.Add("/d:sonar.pvs-studio.reportPath=\"{value}\"", PvsStudioReportPath);
            }

            return args;
        }
    }
}