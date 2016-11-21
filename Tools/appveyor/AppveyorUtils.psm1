function Edit-ReplaceByFormat {
    param(
        [string] $fileToReplace,
        [string] $contentToReplace,
        [string] $replaceTo
    )

    Write-Output "Start replace content at source: '$fileToReplace'"
    Write-Output "Replace: '$contentToReplace' to the '$replaceTo'"

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
    Write-Host "Extracting archive '$outFile' to the folder '$unzipFolder'"
    [System.IO.Compression.ZipFile]::ExtractToDirectory("$outFile", "$unzipFolder")
}

function Start-SonarAnalysis {
    param(
        [string] $projectKey,
        [string] $projectPath,
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
        [string] $toolsPath = (Get-Item -Path ".\" -Verbose).FullName
    )

    Write-Output "End SonarQube analize"
    $sonarMsbuildPath = Join-Path $toolsPath $Sonar_MsBuildToolExe
    Write-Output "$sonarMsbuildPath"
	& $sonarMsbuildPath end > null
}