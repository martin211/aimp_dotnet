using Nuke.Common.Tooling;
using Nuke.Common.Tools.SonarScanner;

namespace Aimp.DotNet.Build
{
    public class SonarBeginSettings : SonarScannerBeginSettings
    {
        public virtual string ProjectBaseDir { get; internal set; }

        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            var args = base.ConfigureArguments(arguments);
            args.Add("/d:sonar.projectBaseDir=\"{value}\"", ProjectBaseDir);

            return args;
        }
    }
}