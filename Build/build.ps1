param
(
	[parameter(Position=0,Mandatory=$true,ValueFromPipeline=$true)]
	[ValidateScript({Test-Path -Path $_ -PathType Leaf})]
	[string] $projFile,

	[parameter(Mandatory=$true)]
	[string]
	$target,

	[parameter(Mandatory=$true)]
	[string]
	$version,

	$configuration = "Release",

	[parameter(Mandatory=$true)]
	$projectDir,

	$timeout = 30
)
Start-Sleep 20
Import-Module CiBuildTools
$job = Start-Job -name BuildJob -ScriptBlock {Invoke-BuildProject -Path $projFile -target $target -projectParameters "/p:Version=$version /p:Configuration=$configuration /p:DeploymentFolder=artifacts" -BuildLogDirectoryPath $projectDir/Build/logs -KeepBuildLogOnSuccessfulBuilds -ShowBuildOutputInCurrentWindow}

$job | Wait-Job -Timeout $timeout
Get-Job -name BuildJob | ?{$_.State -eq 'Running'} | Stop-Job -PassThru
$j = Get-Job -name BuildJob
if ($j.State -eq "Stopped") {
	Write-Error "Job '$target' was stopped by timeout. Checking logs or increment timeout."
}