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

        protected override Arguments ConfigureProcessArguments(Arguments arguments)
        {
            var args = base.ConfigureProcessArguments(arguments);
            args.Add("/d:sonar.projectBaseDir=\"{value}\"", ProjectBaseDir);
            return args;
        }
    }
}