function Edit-ReplaceByFormat {
    param(
        [string] $fileToReplace,
        [string] $contentToReplace,
        [string] $replaceTo
    )

    Write-Output "Start replace content at source: '$fileToReplace'"

    if (!([System.IO.File]::Exists($fileToReplace)))
    {
        Write-Error "Error: File '$fileToReplace' does not exists"
        Exit
    }

    $reader = New-Object System.IO.StreamReader($fileToReplace)
    $content = $reader.ReadToEnd()

    $content = $content.Replace($contentToReplace, $replaceTo)
    $reader.Close()

    $projectFileStream = New-Object System.IO.StreamWriter($fileToReplace, $false)
    $projectFileStream.WriteLine($content)
    $projectFileStream.Close()
}

function Invoke-DownloadFile {
    param (
        [string] $fileUrl,
        [string] $outFile
    )
    
    Invoke-WebRequest -Uri "$fileUrl" -OutFile $outFile

    if (!(Test-Path -Path $outFile)) {
        Write-Error "Error: File '$paramValue' was not found"
        Exit
    }
}

function Invoke-ExtractFile {
    param (
        [string] $inputFile,
        [string] $outputPath
    )

    Add-Type -AssemblyName System.IO.Compression.FileSystem
    Write-Host "Extracting archive '$inputFile' to the folder '$outputPath'"
    [System.IO.Compression.ZipFile]::ExtractToDirectory("$inputFile", "$outputPath")
}

$Sonar_MsBuildToolExe = "MSBuild.SonarQube.Runner.exe"

function Start-SonarAnalysis {
    param(
        [string] $projectKey,        
        [string] $version,
        [string] $solutionFile,
        [string] $toolsPath = (Get-Item -Path ".\" -Verbose).FullName,
        [string] $branch = "develop"
    )

    Write-Output "Start SonarQube analize for $solutionFile"
    $sonarMsbuildPath = Join-Path $toolsPath $Sonar_MsBuildToolExe
    & $sonarMsbuildPath begin /k:"$projectKey" /n:"$solutionFile" /v:"$version" /d:sonar.branch="$branch" /d:sonar.verbose=false
}

function Stop-SonarAnalysis {
    param (
        [string] $toolsPath = (Get-Item -Path ".\" -Verbose).FullName,
		[string] $logFile
    )

    Write-Output "End SonarQube analize"
    $sonarMsbuildPath = Join-Path $toolsPath $Sonar_MsBuildToolExe
    Write-Output "$sonarMsbuildPath"
	& $sonarMsbuildPath end > $logFile
}

function Invoke-PrepareArtifacts {
	param (
		[string] $configuration = "Debug",
		[string] $projectFolder,
		[string] $artifactsFolder
	)

	$pluginsFolder = Join-Path $projectFolder "Plugins"
	$di = New-Object System.IO.DirectoryInfo($pluginsFolder)
	$plugins = $di.GetDirectories("*");

	if (!(Test-Path $artifactsFolder))
	{
		New-Item $artifactsFolder -type directory > null
	}

	$pluginsOutFolder = Join-Path $artifactsFolder "Plugins"
	if (!(Test-Path $pluginsOutFolder))
	{
		New-Item $pluginsOutFolder -type directory > null
	}

	$sdkFolder = Join-Path $projectFolder $configuration
	if (!(Test-Path $sdkFolder))
	{
		Write-Error "SDK folder '$sdkFolder' was not found"
	}

	$sdkFile = Join-Path $sdkFolder "AIMP.SDK.dll"
	$sdkPluginFile = Join-Path $sdkFolder "aimp_dotnet.dll"

	foreach ($plugin in $plugins)
	{
		$pluginOutFolder = Join-Path $plugin.FullName "bin\$configuration"
		if (!(Test-Path -Path $pluginOutFolder))
		{
			continue
		}
		
		$sourceFile = [System.IO.Path]::Combine($pluginOutFolder, $plugin.Name +'.dll')		
		$outFolder = Join-Path $pluginsOutFolder $plugin.Name	
			
		if (!(Test-Path $outFolder))
		{
			New-Item $outFolder -type directory > null
		}
				
		$destinationFile = [System.IO.Path]::Combine($outFolder, $plugin.Name + "_plugin.dll")
		
		Copy-Item $sourceFile -Destination $destinationFile -Recurse
		Copy-Item $sdkFile -Destination (Join-Path $outFolder "AIMP.SDK.dll")
		Copy-Item $sdkPluginFile -Destination ([System.IO.Path]::Combine($outFolder, $plugin.Name + ".dll"))
		
		$langFolder = Join-Path $plugin.FullName "langs"
		
		if (Test-Path -Path $langFolder)
		{
			Copy-Item $langFolder -Destination $outFolder -Recurse -Force
		}
	}

	Copy-Item $sdkFile -Destination $artifactsFolder
	Copy-Item $sdkPluginFile -Destination $artifactsFolder
}

function Invoke-PushArtifacts {
	param (
		[string] $inputPath
	)
	
	Push-AppveyorArtifact $inputPath
}

function Invoke-CompressArtifacts {
	param (
		[string] $archiveName,
		[string] $inputPath,
		[string] $outputPath
	)
	
	$output = Join-Path $outputPath $archiveName
	$input = Join-Path $inputPath "*"
	
	$compressCommand = "7z"			
	& $compressCommand a $output $input
}