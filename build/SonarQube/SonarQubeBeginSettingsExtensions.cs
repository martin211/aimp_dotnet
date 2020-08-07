using JetBrains.Annotations;
using Nuke.Common.Tooling;

namespace Aimp.DotNet.Build
{
    public static class SonarBeginSettingsExtensions
    {
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.ProjectBaseDir"/>.</em></p><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        [Pure]
        public static SonarBeginSettings SetProjectBaseDir(this SonarBeginSettings toolSettings, string projectBaseDir)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectBaseDir = projectBaseDir;
            return toolSettings;
        }

        public static SonarBeginSettings SetVerbose2(this SonarBeginSettings toolSettings, bool value)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Verbose1 = value;
            return toolSettings;
        }
    }
}