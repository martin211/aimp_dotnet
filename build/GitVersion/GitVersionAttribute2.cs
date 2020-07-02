// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System.Reflection;
using Nuke.Common.CI.AppVeyor;
using Nuke.Common.CI.AzurePipelines;
using Nuke.Common.CI.TeamCity;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.GitVersion;

namespace Aimp.DotNet.Build
{
    public class GitVersion2Attribute : GitVersionAttribute
    {
        public string UserName { get; set; }
        public string Password { get; set; }

        public GitVersion2Attribute()
        {
            Framework = "netcoreapp3.1";
        }

        public override object GetValue(MemberInfo member, object instance)
        {
            var gitVersion = GitVersionTasks.GitVersion(s => s
                    .SetFramework(Framework)
                    .SetNoFetch(NoFetch)
                    .DisableLogOutput()
                    .SetUsername(UserName)
                    .SetPassword(Password)
                    .SetUpdateAssemblyInfo(UpdateAssemblyInfo))
                .Result;

            if (UpdateBuildNumber)
            {
                AzurePipelines.Instance?.UpdateBuildNumber(gitVersion.FullSemVer);
                TeamCity.Instance?.SetBuildNumber(gitVersion.FullSemVer);
                AppVeyor.Instance?.UpdateBuildNumber($"{gitVersion.FullSemVer}.build.{AppVeyor.Instance.BuildNumber}");
            }

            return gitVersion;
        }
    }
}