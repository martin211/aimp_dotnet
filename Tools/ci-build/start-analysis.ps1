param(
    [Parameter(Mandatory=$true)] [string]  $solutionPath,
    [Parameter(Mandatory=$true)] [string]  $sonarProjectKey,
    [Parameter(Mandatory=$true)] [string]  $sonarProjectName,
    [Parameter(Mandatory=$false)] [string] $version,
	[Parameter(Mandatory=$false)] [string] $branch
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $solutionPath)) {
    throw [System.IO.FileNotFoundException] "$solutionPath not found."
}

Write-Output "Checking prerequisites:"
Write-Output ""
Get-Command MSBuild.SonarQube.Runner
Get-Command MSBuild
#Get-Command dotCover
#Get-Command nunit-console
Write-Output "All prerequisites in place"
Write-Output ""
#NuGet restore $solutionPath

Write-Output "Starting SonarQube publish analysis for project $sonarProjectName [id=$sonarProjectKey,version=$version,branch=$branch]"
MSBuild.SonarQube.Runner begin `
    /k:$sonarProjectKey `
    "/n:$sonarProjectName" `
    "/v:$version" `
    "/d:sonar.msbuild.testProjectPattern=[^\\]*(Unit)?Tests$" `
    "/d:sonar.branch=$branch " `
	"/d:sonar.cxx.compiler.reportPath=../msbuild.log " `
	"/d:sonar.cxx.compiler.charset=UTF-8 " `
	"/d:sonar.cxx.compiler.regex=^(.*)\((\d+)\)\x20*:\x20warning\x20(C\d+):(.*)$ "
    #/d:sonar.cs.dotcover.reportsPaths=dotCover.html

	if ($LASTEXITCODE -ne 0) {
        throw "Job failed."
    }