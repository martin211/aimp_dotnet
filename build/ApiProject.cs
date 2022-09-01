//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using Nuke.Common.Git;

internal class ApiProject
{
    public string RepositoryUrl { get; set; }

    public string PackageId { get; set; }

    public GitRepository Repository => GitRepository.FromUrl(RepositoryUrl);
}
