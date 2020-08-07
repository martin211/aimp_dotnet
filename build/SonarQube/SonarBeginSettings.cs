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
        internal bool? Verbose1;

        public virtual string ProjectBaseDir { get; internal set; }

        public override bool? Verbose => Verbose1;

        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            var args = base.ConfigureArguments(arguments);
            args.Add("/d:sonar.projectBaseDir=\"{value}\"", ProjectBaseDir);
            if (Verbose1.HasValue && Verbose1.Value)
            {
                args.Add("/d:sonar.verbose={value}", Verbose1.ToString().ToLower());
            }

            return args;
        }
    }
}