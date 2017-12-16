$githubreleases = "$PSScriptRoot\GitHubReleases.psm1"
$githubtags = "$PSScriptRoot\GitHubTags.psm1"
Import-Module -force $githubreleases
Import-Module -force $githubtags

function New-Tag
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String] $origTag
    )

    $splitString = $origTag.Split(".")
    $strnum = $splitString[$splitString.Length-1]
    $num = [convert]::ToInt32($strnum, 10)
    $num += 1
    $splitString[$splitString.Length-1] = $num
    return $splitString -join "."
}

$repoUrl = "https://github.com/anthonydresser/PowerShellForGitHub"

$commit = git rev-parse HEAD

$release = Get-GitHubReleasesForRespository -repositoryUrl $repoUrl

$tag = $release.tag_name

$tagInfo = Get-GitHubReleaseTagForRepository -repositoryUrl $repoUrl -tag_name $tag

if ($tagInfo.commit.sha -ne $tag)
{
    Write-Host "Uploading new prerelease"
    $new_tag = New-Tag -origTag $tag
    Write-Host "changed $tag to $new_tag"
    Add-GitHubReleaseForRepository -repositoryUrl $repoUrl -versionTag $new_tag -target "master" -body "This is a automated prerelease" -isPrerelease $TRUE
}

