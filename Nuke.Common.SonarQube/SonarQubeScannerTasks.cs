using System;
using System.Diagnostics.CodeAnalysis;
using JetBrains.Annotations;
using Nuke.Core.Tooling;

namespace Nuke.Common.SonarQube
{
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    [Serializable]
    public partial class SonarQubeScannerSettings : ToolSettings
    {
        public override string ToolPath => base.ToolPath ?? SonarQubeScannerTasks.GetToolPath();

        public string ProjectKey { get; internal set; }

        public string ProjectName { get; internal set; }

        public string Version { get; internal set; }

        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            return base.ConfigureArguments(arguments);
        }
    }

    public static partial class SonarQubeScannerTasks
    {
        internal static string GetToolPath()
        {
            return ToolPathResolver.TryGetEnvironmentExecutable("SONARQUBE_EXE")
                   ?? ToolPathResolver.GetPackageExecutable("msbuild.sonarqube.runner.tool", "SonarQube.Scanner.MSBuild.exe");
        }

        public static void Begin(Configure<SonarQubeScannerSettings> configurator = null, ProcessSettings processSettings = null)
        {
            var toolSettings = configurator.InvokeSafe(new SonarQubeScannerSettings());
            PrePro
        }

        public static void End(Configure<SonarQubeScannerSettings> configurator = null, ProcessSettings processSettings = null)
        {

        }
    }
}
