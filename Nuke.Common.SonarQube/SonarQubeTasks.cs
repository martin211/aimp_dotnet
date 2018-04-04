using System;
using System.Diagnostics.CodeAnalysis;
using JetBrains.Annotations;
using Nuke.Core.Tooling;

namespace Nuke.Common.Tools.SonarQube
{
    public static partial class SonarQubeTasks
    {
        private static string GetToolPath()
        {
            return ToolPathResolver.TryGetEnvironmentExecutable("SONARQUBE_EXE")
                   ?? ToolPathResolver.GetPackageExecutable("msbuild.sonarqube.runner.tool", "SonarQube.Scanner.MSBuild.exe");
        }

        public static void SonarQubeEnd(Configure<SonarQubeEndSettings> configurator = null,
            ProcessSettings processSettings = null)
        {
            var toolSettings = configurator.InvokeSafe(new SonarQubeEndSettings());
            var process = ProcessTasks.StartProcess(toolSettings, processSettings);
            process.AssertZeroExitCode();
        }
    }

    [PublicAPI]
    [ExcludeFromCodeCoverage]
    [Serializable]
    public partial class SonarQubeEndSettings : ToolSettings
    {
        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            arguments.Add("end");
            return base.ConfigureArguments(arguments);
        }
    }
}