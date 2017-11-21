param(
    [Parameter(Mandatory=$true)] [string]  $solutionPath,
    [Parameter(Mandatory=$false)] [string] $version,
    [Parameter(Mandatory=$false)] [string] $branch,
	[Parameter(Mandatory=$true)] [string] $configuration
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $solutionPath)) {
    throw [System.IO.FileNotFoundException] "$solutionPath not found."
}

Write-Output "Checking prerequisites:"
Get-Command MSBuild
Write-Output "All prerequisites in place"

Write-Output "Starting build $sonarProjectName [version=$version,branch=$branch]"
Start-Process MSBuild -ArgumentList "$solutionPath /t:Clean,Build /p:BuildNumber=$version /p:Configuration=$configuration; /p:Platform=AnyCPU /p:PlatformToolset=v141" -Wait -NoNewWindow 