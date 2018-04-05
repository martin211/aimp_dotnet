// Copyright Matthias Koch, Sebastian Karasek 2018.
// Distributed under the MIT License.
// https://github.com/nuke-build/nuke/blob/master/LICENSE

// Generated with Nuke.CodeGeneration, LOCAL VERSION.
// Generated from https://github.com/nuke-build/tools/blob/master/metadata/SonarQube.json.

using JetBrains.Annotations;
using Nuke.Common.Tools;
using Nuke.Core;
using Nuke.Core.Execution;
using Nuke.Core.Tooling;
using Nuke.Core.Utilities.Collections;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Linq;
using System.Text;

namespace Nuke.Common.Tools.SonarQube
{
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    public static partial class SonarQubeTasks
    {
        /// <summary><p>Path to the SonarQube executable.</p></summary>
        public static string SonarQubePath => ToolPathResolver.GetPackageExecutable("msbuild.sonarqube.runner.tool", "SonarScanner.MSBuild.exe");
        static partial void PreProcess(SonarQubeBeginSettings toolSettings);
        static partial void PostProcess(SonarQubeBeginSettings toolSettings);
        /// <summary><p>The SonarScanner for MSBuild is the recommended way to launch a SonarQube or SonarCloud analysis for projects/solutions using MSBuild or dotnet command as build tool. It is the result of a collaboration between SonarSource and Microsoft.SonarScanner for MSBuild is distributed as a standalone command line executable and as build steps for VSTS/TFS and a plugin for Jenkins.It supports .Net Core multi-platform projects and it can be used on non-Windows platforms.</p><p>For more details, visit the <a href="https://msdn.microsoft.com/en-us/library/ms164311.aspx">official website</a>.</p></summary>
        public static void SonarQubeBegin(Configure<SonarQubeBeginSettings> configurator = null, ProcessSettings processSettings = null)
        {
            var toolSettings = configurator.InvokeSafe(new SonarQubeBeginSettings());
            PreProcess(toolSettings);
            var process = ProcessTasks.StartProcess(toolSettings, processSettings);
            process.AssertZeroExitCode();
            PostProcess(toolSettings);
        }
        static partial void PreProcess(SonarQubeEndSettings toolSettings);
        static partial void PostProcess(SonarQubeEndSettings toolSettings);
        /// <summary><p>The SonarScanner for MSBuild is the recommended way to launch a SonarQube or SonarCloud analysis for projects/solutions using MSBuild or dotnet command as build tool. It is the result of a collaboration between SonarSource and Microsoft.SonarScanner for MSBuild is distributed as a standalone command line executable and as build steps for VSTS/TFS and a plugin for Jenkins.It supports .Net Core multi-platform projects and it can be used on non-Windows platforms.</p><p>For more details, visit the <a href="https://msdn.microsoft.com/en-us/library/ms164311.aspx">official website</a>.</p></summary>
        public static void SonarQubeEnd(Configure<SonarQubeEndSettings> configurator = null, ProcessSettings processSettings = null)
        {
            var toolSettings = configurator.InvokeSafe(new SonarQubeEndSettings());
            PreProcess(toolSettings);
            var process = ProcessTasks.StartProcess(toolSettings, processSettings);
            process.AssertZeroExitCode();
            PostProcess(toolSettings);
        }
    }
    #region SonarQubeBeginSettings
    /// <summary><p>Used within <see cref="SonarQubeTasks"/>.</p></summary>
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    [Serializable]
    public partial class SonarQubeBeginSettings : ToolSettings
    {
        /// <summary><p>Path to the SonarQube executable.</p></summary>
        public override string ToolPath => base.ToolPath ?? SonarQubeTasks.SonarQubePath;
        /// <summary><p>Specifies the key of the analyzed project in SonarQube.</p></summary>
        public virtual string ProjectKey { get; internal set; }
        /// <summary><p>Specifies the name of the analyzed project in SonarQube. Adding this argument will overwrite the project name in SonarQube if it already exists.</p></summary>
        public virtual string ProjectName { get; internal set; }
        /// <summary><p>Specifies the version of your project.</p></summary>
        public virtual string Version { get; internal set; }
        /// <summary><p>Specifies the username or access token to authenticate with to SonarQube. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        public virtual string UserName { get; internal set; }
        /// <summary><p>Specifies the password for the SonarQube username in the `sonar.login` argument. This argument is not needed if you use authentication token. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        public virtual string UserPassword { get; internal set; }
        /// <summary><p>Sets the logging verbosity to detailed. Add this argument before sending logs for troubleshooting.</p></summary>
        public virtual bool? Verbose { get; internal set; }
        /// <summary><p></p></summary>
        public virtual string HostUrl { get; internal set; }
        /// <summary><p></p></summary>
        public virtual IReadOnlyDictionary<string, object> Properties => PropertiesInternal.AsReadOnly();
        internal Dictionary<string, object> PropertiesInternal { get; set; } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);
        /// <summary><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        public virtual string ProjectBaseDir { get; internal set; }
        /// <summary><p>Set the working directory for an analysis triggered with the SonarQube Scanner or the SonarQube Ant Task (versions greater than 2.0). Path must be relative and unique for each project. (warning) Beware: the specified folder is deleted before each analysis.</p></summary>
        public virtual string SonarWorkingDirectory { get; internal set; }
        protected override void AssertValid()
        {
            base.AssertValid();
            ControlFlow.Assert(ProjectKey != null, "ProjectKey != null");
        }
        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            arguments
              .Add("begin")
              .Add("/k:\"{value}\"", ProjectKey)
              .Add("/n:\"{value}\"", ProjectName)
              .Add("/v:\"{value}\"", Version)
              .Add("/d:sonar.login=\"{value}\"", UserName)
              .Add("/d:sonar.password=\"{value}\"", UserPassword)
              .Add("/d:sonar.verbose=\"{value}\"", Verbose)
              .Add("/d:sonar.host.url=\"{value}\"", HostUrl)
              .Add("/d:{value}", Properties, "{key}={value}", disallowed: ';')
              .Add("/d:sonar.projectBaseDir=\"{value}\"", ProjectBaseDir)
              .Add("/d:sonar.working.directory=\"{value}\"", SonarWorkingDirectory);
            return base.ConfigureArguments(arguments);
        }
    }
    #endregion
    #region SonarQubeEndSettings
    /// <summary><p>Used within <see cref="SonarQubeTasks"/>.</p></summary>
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    [Serializable]
    public partial class SonarQubeEndSettings : ToolSettings
    {
        /// <summary><p>Path to the SonarQube executable.</p></summary>
        public override string ToolPath => base.ToolPath ?? SonarQubeTasks.SonarQubePath;
        /// <summary><p>Specifies the username or access token to authenticate with to SonarQube. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        public virtual string UserName { get; internal set; }
        /// <summary><p>Specifies the password for the SonarQube username in the `sonar.login` argument. This argument is not needed if you use authentication token. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        public virtual string UserPassword { get; internal set; }
        /// <summary><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        public virtual string ProjectBaseDir { get; internal set; }
        /// <summary><p>Set the working directory for an analysis triggered with the SonarQube Scanner or the SonarQube Ant Task (versions greater than 2.0). Path must be relative and unique for each project. (warning) Beware: the specified folder is deleted before each analysis.</p></summary>
        public virtual string SonarWorkingDirectory { get; internal set; }
        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            arguments
              .Add("end")
              .Add("/d:sonar.login=\"{value}\"", UserName)
              .Add("/d:sonar.password=\"{value}\"", UserPassword)
              .Add("/d:sonar.projectBaseDir=\"{value}\"", ProjectBaseDir)
              .Add("/d:sonar.working.directory=\"{value}\"", SonarWorkingDirectory);
            return base.ConfigureArguments(arguments);
        }
    }
    #endregion
    #region SonarQubeBeginSettingsExtensions
    /// <summary><p>Used within <see cref="SonarQubeTasks"/>.</p></summary>
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    public static partial class SonarQubeBeginSettingsExtensions
    {
        #region ProjectKey
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.ProjectKey"/>.</em></p><p>Specifies the key of the analyzed project in SonarQube.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetProjectKey(this SonarQubeBeginSettings toolSettings, string projectKey)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectKey = projectKey;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.ProjectKey"/>.</em></p><p>Specifies the key of the analyzed project in SonarQube.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetProjectKey(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectKey = null;
            return toolSettings;
        }
        #endregion
        #region ProjectName
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.ProjectName"/>.</em></p><p>Specifies the name of the analyzed project in SonarQube. Adding this argument will overwrite the project name in SonarQube if it already exists.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetProjectName(this SonarQubeBeginSettings toolSettings, string projectName)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectName = projectName;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.ProjectName"/>.</em></p><p>Specifies the name of the analyzed project in SonarQube. Adding this argument will overwrite the project name in SonarQube if it already exists.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetProjectName(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectName = null;
            return toolSettings;
        }
        #endregion
        #region Version
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.Version"/>.</em></p><p>Specifies the version of your project.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetVersion(this SonarQubeBeginSettings toolSettings, string version)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Version = version;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.Version"/>.</em></p><p>Specifies the version of your project.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetVersion(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Version = null;
            return toolSettings;
        }
        #endregion
        #region UserName
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.UserName"/>.</em></p><p>Specifies the username or access token to authenticate with to SonarQube. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetUserName(this SonarQubeBeginSettings toolSettings, string userName)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserName = userName;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.UserName"/>.</em></p><p>Specifies the username or access token to authenticate with to SonarQube. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetUserName(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserName = null;
            return toolSettings;
        }
        #endregion
        #region UserPassword
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.UserPassword"/>.</em></p><p>Specifies the password for the SonarQube username in the `sonar.login` argument. This argument is not needed if you use authentication token. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetUserPassword(this SonarQubeBeginSettings toolSettings, string userPassword)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserPassword = userPassword;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.UserPassword"/>.</em></p><p>Specifies the password for the SonarQube username in the `sonar.login` argument. This argument is not needed if you use authentication token. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetUserPassword(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserPassword = null;
            return toolSettings;
        }
        #endregion
        #region Verbose
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.Verbose"/>.</em></p><p>Sets the logging verbosity to detailed. Add this argument before sending logs for troubleshooting.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetVerbose(this SonarQubeBeginSettings toolSettings, bool? verbose)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Verbose = verbose;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.Verbose"/>.</em></p><p>Sets the logging verbosity to detailed. Add this argument before sending logs for troubleshooting.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetVerbose(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Verbose = null;
            return toolSettings;
        }
        /// <summary><p><em>Enables <see cref="SonarQubeBeginSettings.Verbose"/>.</em></p><p>Sets the logging verbosity to detailed. Add this argument before sending logs for troubleshooting.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings EnableVerbose(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Verbose = true;
            return toolSettings;
        }
        /// <summary><p><em>Disables <see cref="SonarQubeBeginSettings.Verbose"/>.</em></p><p>Sets the logging verbosity to detailed. Add this argument before sending logs for troubleshooting.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings DisableVerbose(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Verbose = false;
            return toolSettings;
        }
        /// <summary><p><em>Toggles <see cref="SonarQubeBeginSettings.Verbose"/>.</em></p><p>Sets the logging verbosity to detailed. Add this argument before sending logs for troubleshooting.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ToggleVerbose(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.Verbose = !toolSettings.Verbose;
            return toolSettings;
        }
        #endregion
        #region HostUrl
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.HostUrl"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetHostUrl(this SonarQubeBeginSettings toolSettings, string hostUrl)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.HostUrl = hostUrl;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.HostUrl"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetHostUrl(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.HostUrl = null;
            return toolSettings;
        }
        #endregion
        #region Properties
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.Properties"/> to a new dictionary.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetProperties(this SonarQubeBeginSettings toolSettings, IDictionary<string, object> properties)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal = properties.ToDictionary(x => x.Key, x => x.Value, StringComparer.OrdinalIgnoreCase);
            return toolSettings;
        }
        /// <summary><p><em>Clears <see cref="SonarQubeBeginSettings.Properties"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings ClearProperties(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal.Clear();
            return toolSettings;
        }
        /// <summary><p><em>Adds a new key-value-pair <see cref="SonarQubeBeginSettings.Properties"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings AddProperty(this SonarQubeBeginSettings toolSettings, string propertyKey, object propertyValue)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal.Add(propertyKey, propertyValue);
            return toolSettings;
        }
        /// <summary><p><em>Removes a key-value-pair from <see cref="SonarQubeBeginSettings.Properties"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings RemoveProperty(this SonarQubeBeginSettings toolSettings, string propertyKey)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal.Remove(propertyKey);
            return toolSettings;
        }
        /// <summary><p><em>Sets a key-value-pair in <see cref="SonarQubeBeginSettings.Properties"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetProperty(this SonarQubeBeginSettings toolSettings, string propertyKey, object propertyValue)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal[propertyKey] = propertyValue;
            return toolSettings;
        }
        #region OutDir
        /// <summary><p><em>Sets <c>OutDir</c> in <see cref="SonarQubeBeginSettings.Properties"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetOutDir(this SonarQubeBeginSettings toolSettings, string outDir)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal["OutDir"] = outDir;
            return toolSettings;
        }
        /// <summary><p><em>Resets <c>OutDir</c> in <see cref="SonarQubeBeginSettings.Properties"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetOutDir(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.PropertiesInternal.Remove("OutDir");
            return toolSettings;
        }
        #endregion
        #endregion
        #region ProjectBaseDir
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.ProjectBaseDir"/>.</em></p><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetProjectBaseDir(this SonarQubeBeginSettings toolSettings, string projectBaseDir)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectBaseDir = projectBaseDir;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.ProjectBaseDir"/>.</em></p><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetProjectBaseDir(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectBaseDir = null;
            return toolSettings;
        }
        #endregion
        #region SonarWorkingDirectory
        /// <summary><p><em>Sets <see cref="SonarQubeBeginSettings.SonarWorkingDirectory"/>.</em></p><p>Set the working directory for an analysis triggered with the SonarQube Scanner or the SonarQube Ant Task (versions greater than 2.0). Path must be relative and unique for each project. (warning) Beware: the specified folder is deleted before each analysis.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings SetSonarWorkingDirectory(this SonarQubeBeginSettings toolSettings, string sonarWorkingDirectory)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.SonarWorkingDirectory = sonarWorkingDirectory;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeBeginSettings.SonarWorkingDirectory"/>.</em></p><p>Set the working directory for an analysis triggered with the SonarQube Scanner or the SonarQube Ant Task (versions greater than 2.0). Path must be relative and unique for each project. (warning) Beware: the specified folder is deleted before each analysis.</p></summary>
        [Pure]
        public static SonarQubeBeginSettings ResetSonarWorkingDirectory(this SonarQubeBeginSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.SonarWorkingDirectory = null;
            return toolSettings;
        }
        #endregion
    }
    #endregion
    #region SonarQubeEndSettingsExtensions
    /// <summary><p>Used within <see cref="SonarQubeTasks"/>.</p></summary>
    [PublicAPI]
    [ExcludeFromCodeCoverage]
    public static partial class SonarQubeEndSettingsExtensions
    {
        #region UserName
        /// <summary><p><em>Sets <see cref="SonarQubeEndSettings.UserName"/>.</em></p><p>Specifies the username or access token to authenticate with to SonarQube. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeEndSettings SetUserName(this SonarQubeEndSettings toolSettings, string userName)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserName = userName;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeEndSettings.UserName"/>.</em></p><p>Specifies the username or access token to authenticate with to SonarQube. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeEndSettings ResetUserName(this SonarQubeEndSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserName = null;
            return toolSettings;
        }
        #endregion
        #region UserPassword
        /// <summary><p><em>Sets <see cref="SonarQubeEndSettings.UserPassword"/>.</em></p><p>Specifies the password for the SonarQube username in the `sonar.login` argument. This argument is not needed if you use authentication token. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeEndSettings SetUserPassword(this SonarQubeEndSettings toolSettings, string userPassword)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserPassword = userPassword;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeEndSettings.UserPassword"/>.</em></p><p>Specifies the password for the SonarQube username in the `sonar.login` argument. This argument is not needed if you use authentication token. If this argument is added to the begin step, it must also be added on the end step.</p></summary>
        [Pure]
        public static SonarQubeEndSettings ResetUserPassword(this SonarQubeEndSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.UserPassword = null;
            return toolSettings;
        }
        #endregion
        #region ProjectBaseDir
        /// <summary><p><em>Sets <see cref="SonarQubeEndSettings.ProjectBaseDir"/>.</em></p><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        [Pure]
        public static SonarQubeEndSettings SetProjectBaseDir(this SonarQubeEndSettings toolSettings, string projectBaseDir)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectBaseDir = projectBaseDir;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeEndSettings.ProjectBaseDir"/>.</em></p><p>Use this property when you need analysis to take place in a directory other than the one from which it starts. E.G. analysis begins from jenkins/jobs/myjob/workspace but the files to be analyzed are in ftpdrop/cobol/project1. The path may be relative or absolute. Specify not the the source directory, but some parent of the source directory. The value specified here becomes the new "analysis directory", and other paths are then specified as though the analysis were starting from the new sonar.projectBaseDir. Note that the analysis process will need write permissions in this directory; it is where the sonar.working.directory will be created.</p></summary>
        [Pure]
        public static SonarQubeEndSettings ResetProjectBaseDir(this SonarQubeEndSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.ProjectBaseDir = null;
            return toolSettings;
        }
        #endregion
        #region SonarWorkingDirectory
        /// <summary><p><em>Sets <see cref="SonarQubeEndSettings.SonarWorkingDirectory"/>.</em></p><p>Set the working directory for an analysis triggered with the SonarQube Scanner or the SonarQube Ant Task (versions greater than 2.0). Path must be relative and unique for each project. (warning) Beware: the specified folder is deleted before each analysis.</p></summary>
        [Pure]
        public static SonarQubeEndSettings SetSonarWorkingDirectory(this SonarQubeEndSettings toolSettings, string sonarWorkingDirectory)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.SonarWorkingDirectory = sonarWorkingDirectory;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeEndSettings.SonarWorkingDirectory"/>.</em></p><p>Set the working directory for an analysis triggered with the SonarQube Scanner or the SonarQube Ant Task (versions greater than 2.0). Path must be relative and unique for each project. (warning) Beware: the specified folder is deleted before each analysis.</p></summary>
        [Pure]
        public static SonarQubeEndSettings ResetSonarWorkingDirectory(this SonarQubeEndSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.SonarWorkingDirectory = null;
            return toolSettings;
        }
        #endregion
    }
    #endregion
}
