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

<#
    .SYNOPSIS Function which gets list of releases for given repository
    .PARAM
        repositoryUrl Array of repository urls which we want to get releases from
    .PARAM
        gitHubAccessToken GitHub API Access Token.
            Get github token from https://github.com/settings/tokens 
            If you don't provide it, you can still use this script, but you will be limited to 60 queries per hour.
    .EXAMPLE
        $releases = Get-GitHubReleasesForRespository -repositoryUrl @('https://github.com/PowerShell/xPSDesiredStateConfiguration')
#>
function Get-GitHubReleasesForRespository
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String[]] $repositoryUrl,
        $gitHubAccessToken = $script:gitHubToken
    )

    $resultToReturn = @()

    $index = 0
    
    foreach ($repository in $repositoryUrl)
    {
        Write-Host "Getting releases for repository $repository" -ForegroundColor Yellow

        $repositoryName = Get-GitHubRepositoryNameFromUrl -repositoryUrl $repository
        $repositoryOwner = Get-GitHubRepositoryOwnerFromUrl -repositoryUrl $repository

        # Create query for issues
        $query = "$script:gitHubApiReposUrl/$repositoryOwner/$repositoryName/releases?"

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

                Write-Verbose "$index. $($release.html_url) ## Created: $($release.created_at) ## Closed: $($release.tag_name)"
                $index++

                $resultToReturn += $release
            }
            $query = Get-NextResultPage -jsonResult $jsonResult
        } while ($query -ne $null)
    }

    return $resultToReturn
}

function Get-GitHubLastReleaseForRepository
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String] $repositoryUrl,
        $gitHubAccessToken = $script:gitHubToken
    )

    Write-Host "Getting latest release for repository $repository" -ForegroundColor Yellow

    $repositoryName = Get-GitHubRepositoryNameFromUrl -repositoryUrl $repository
    $repositoryOwner = Get-GitHubRepositoryOwnerFromUrl -repositoryUrl $repository

    # Create query for issues
    $query = "$script:gitHubApiReposUrl/$repositoryOwner/$repositoryName/releases/latest?"

    if (![string]::IsNullOrEmpty($gitHubAccessToken))
    {
        $query += "&access_token=$gitHubAccessToken"
    }

    do
    {
        try
        {
            $jsonResult = Invoke-WebRequest $query
            $release = ConvertFrom-Json -InputObject $jsonResult.content
        }
        catch [System.Net.WebException] {
            Write-Error "Failed to execute query with exception: $($_.Exception)`nHTTP status code: $($_.Exception.Response.StatusCode)"
            return $null
        }
        catch {
            Write-Error "Failed to execute query with exception: $($_.Exception)"
            return $null
        }

    } while ($query -ne $null)

    return $release
}

function Add-GitHubReleaseForRepository
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String] $repositoryUrl,
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string] $versionTag,
        [string] $target,
        [string] $name,
        [string] $body,
        [boolean] $isDraft,
        [boolean] $isPrerelease,
        [String[]] $files,
        [String[]] $fileTypes,
        $gitHubAccessToken = $script:gitHubToken
    )

    Write-Host "Creating release for repository $repositoryUrl" -ForegroundColor Yellow

    $repositoryName = Get-GitHubRepositoryNameFromUrl -repositoryUrl $repositoryUrl
    $repositoryOwner = Get-GitHubRepositoryOwnerFromUrl -repositoryUrl $repositoryUrl

    # Create query for releases
    $query = "$script:gitHubApiReposUrl/$repositoryOwner/$repositoryName/releases?access_token=$gitHubAccessToken"
    
    $json = @{
        "tag_name" = $versionTag
    }

    if (![string]::IsNullOrEmpty($target))
    {
        $json.add("target_commitish", $target)
    }

    if (![string]::IsNullOrEmpty($name))
    {
        $json.add("name", $name)
    }

    if (![string]::IsNullOrEmpty($body))
    {
        $json.add("body", $body)
    }

    if ($isDraft)
    {
        $json.add("draft", $isDraft)
    }

    if ($isPrerelease)
    {
        $json.add("prerelease", $isPrerelease)
    }

    $JSONF = $json | convertto-json 

    try
    {
        $jsonResult = Invoke-WebRequest -uri $query -Method POST -Body $JSONF -ContentType "application/json"
        $release = ConvertFrom-Json -InputObject $jsonResult.content
    }
    catch [System.Net.WebException] {
        Write-Error "Failed to execute query with exception: $($_.Exception)`nHTTP status code: $($_.Exception.Response.StatusCode)"
        return $null
    }
    catch {
        Write-Error "Failed to execute query with exception: $($_.Exception)"
        return $null
    }

    if ($files.count -gt 0)
    {
        Post-GitHubAssetForRelease -repository $repositoryUrl -releaseId $release.id -files $files -fileTypes $fileTypes
    }


    Write-Verbose "Release located at $($jsonResult.headers.location)"

}

function Add-GitHubAssetForRelease
{
    param
    (
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String] $repositoryUrl,
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String] $releaseId,
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String[]] $files,
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [String[]] $fileTypes

    )


    Write-Host "Uploading asset(s) for release $releaseId for repository $repositoryUrl" -ForegroundColor Yellow

    $repositoryName = Get-GitHubRepositoryNameFromUrl -repositoryUrl $repositoryUrl
    $repositoryOwner = Get-GitHubRepositoryOwnerFromUrl -repositoryUrl $repositoryUrl

    # Create query for issues
    $query = "$script:gitHubAPIUploadUrl/$repositoryOwner/$repositoryName/releases/$releaseId/assets?access_token=$gitHubAccessToken"
    if ($fileTypes.Length -eq 1) 
    {
        for ($i=1; $i -lt $files.Length; $i++)
        {
            $fileTypes += $fileTypes[0]
        }
    } elseif ($fileTypes.Length -ne $files.Length) {
        Write-Error "File type array length must match the length of the files array or be 1 indicating all files have the same type"
        return $null
    }
    
    for ($i=0; $i -lt $files.Length; $i++)
    {
        $childFiles = Get-Childitem $files[$i] -Name
        foreach($file in $childFiles)
        {
            try
            {
                Write-Host "Uploading $file"
                $name = $file.split("\")
                $name = $name[$name.length-1].split("/")
                $name = $name[$name.length-1]
                $tempQuery = $query + "&name=$name"
                $jsonResult = Invoke-WebRequest -uri $tempQuery -Method POST -InFile $file -ContentType "application/$($fileTypes[$i])"
            }
            catch [System.Net.WebException] {
                Write-Error "Failed to execute query with exception: $($_.Exception)`nHTTP status code: $($_.Exception.Response.StatusCode)"
                return $null
            }
            catch {
                Write-Error "Failed to execute query with exception: $($_.Exception)"
                return $null
            }
        }
        
    }

    Write-Host "Finished uploading files"  -ForegroundColor Yellow
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