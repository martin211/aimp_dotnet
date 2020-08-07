using Nuke.Common.Git;

internal class ApiProject
{
    public string RepositoryUrl { get; set; }

    public string PackageId { get; set; }

    public GitRepository Repository => GitRepository.FromUrl(RepositoryUrl);
}
