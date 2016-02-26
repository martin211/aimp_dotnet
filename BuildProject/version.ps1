param(
	[string]$currentVersion = "",
	[string]$projectPath = "")

Function CheckPath($fullPath)
{
	if (!(Test-Path -Path $fullPath))
	{
		Write-Error "Error: Path '$fullPath' does not exists"
		return $false
	}
	
	return $true
}

Write-Output "=== Start: Version replace ======"
Write-Output "Version: '$currentVersion'"
Write-Output "ProjectPath: '$currentVersion'"

if (!(CheckPath($projectPath)))
{	
	Exit
}

Write-Output "Replacing 'aimp_dotnet.rc'"

if (!([System.IO.File]::Exists($projectPath + "\aimp_dotnet\aimp_dotnet.rc")))
{
	Write-Error "Error: File '$CurrentVersionFolder\aimp_dotnet\aimp_dotnet.rc' does not exists"
	Exit
}

$reader = New-Object System.IO.StreamReader($projectPath + "\aimp_dotnet\aimp_dotnet.rc")

$content = $reader.ReadToEnd()
$content = $content.Replace("1.0.0.1", $currentVersion)
$content = $content.Replace("1,0,0,1", $currentVersion.Replace(".", ","))
$reader.Close()

$outputFile = Join-Path $projectPath "\aimp_dotnet\aimp_dotnet.rc"

$projectFileStream = New-Object System.IO.StreamWriter($outputFile, $false)
$projectFileStream.WriteLine($content)
$projectFileStream.Close()