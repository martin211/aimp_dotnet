<#
    .SYNOPSIS PowerShell module for GitHub analytics
#>

# Import module which defines $global:gitHubApiToken with GitHub API access token. Create this file it if it doesn't exist.
$apiTokensFilePath = "$PSScriptRoot\ApiTokens.psm1"
if (Test-Path $apiTokensFilePath)
{
    Write-Host "Importing $apiTokensFilePath"
    Import-Module  -force $apiTokensFilePath
}
else
{
    Write-Warning "$apiTokensFilePath does not exist, skipping import"
    Write-Warning @'
This module should define $global:gitHubApiToken with your GitHub API access token in ApiTokens.psm1. Create this file if it doesn't exist.
You can simply rename ApiTokensTemplate.psm1 to ApiTokens.psm1 and update value of $global:gitHubApiToken, then reimport this module with -Force switch.
You can get GitHub token from https://github.com/settings/tokens
If you don't provide it, you can still use this module, but you will be limited to 60 queries per hour.
'@
}

$script:gitHubToken = $global:gitHubApiToken 
$script:gitHubApiUrl = "https://api.github.com"
$script:gitHubApiReposUrl = "https://api.github.com/repos"
$script:gitHubApiOrgsUrl = "https://api.github.com/orgs"
$script:gitHubAPIUploadUrl = "https://uploads.github.com/repos"



function Get-GitHubReleaseTagForRepository
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String[]] $repositoryUrl,
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String] $tag_name,
        $gitHubAccessToken = $script:gitHubToken
    )

    Write-Host "Getting release tag $tag_name for repository $repositoryUrl" -ForegroundColor Yellow

    $repositoryName = Get-GitHubRepositoryNameFromUrl -repositoryUrl $repositoryUrl
    $repositoryOwner = Get-GitHubRepositoryOwnerFromUrl -repositoryUrl $repositoryUrl

    # Create query for issues
    $query = "$script:gitHubApiReposUrl/$repositoryOwner/$repositoryName/tags?"

    if (![string]::IsNullOrEmpty($gitHubAccessToken))
    {
        $query += "&access_token=$gitHubAccessToken"
    }

   do
        {
            try
            {
                $jsonResult = Invoke-WebRequest $query
                $releases = ConvertFrom-Json -InputObject $jsonResult.content
            }
            catch [System.Net.WebException] {
                Write-Error "Failed to execute query with exception: $($_.Exception)`nHTTP status code: $($_.Exception.Response.StatusCode)"
                return $null
            }
            catch {
                Write-Error "Failed to execute query with exception: $($_.Exception)"
                return $null
            }

            foreach ($release in $releases)
            {
                if ($release.name -eq $tag_name)
                {
                    return $release
                }
            }
            $query = Get-NextResultPage -jsonResult $jsonResult
        } while ($query -ne $null)

    return $null
}

<#
    .SYNOPSIS Obtain repository name from it's url

    .EXAMPLE Get-GitHubRepositoryNameFromUrl -repositoryUrl "https://github.com/PowerShell/xRobocopy"
#>
function Get-GitHubRepositoryNameFromUrl
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        $repositoryUrl
    )

    $repositoryName = Split-Path $repositoryUrl -Leaf
    return $repositoryName
}

<#
    .SYNOPSIS Obtain repository owner from it's url

    .EXAMPLE Get-GitHubRepositoryOwnerFromUrl -repositoryUrl "https://github.com/PowerShell/xRobocopy"
#>
function Get-GitHubRepositoryOwnerFromUrl
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        $repositoryUrl
    )

    $repositoryOwner = Split-Path $repositoryUrl -Parent
    $repositoryOwner = Split-Path $repositoryOwner -Leaf
    return $repositoryOwner
}

<#
    .SYNOPSIS Function to get next page with results from query to GitHub API

    .PARAM
        jsonResult Result from the query to GitHub API
#>
function Get-NextResultPage
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        $jsonResult
    )
    
    if($jsonResult.Headers.Link -eq $null)
    {
        return $null
    }

    $nextLinkString = $jsonResult.Headers.Link.Split(',')[0]
    
    # Get url query for the next page
    $query = $nextLinkString.Split(';')[0].replace('<','').replace('>','')
    if ($query -notmatch '&page=1')
    {
        return $query
    }
    else
    {
        return $null
    }
}
