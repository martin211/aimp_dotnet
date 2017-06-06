param(
    [string] $logFile = ".\build.log",
    [string] $docfxUrl = "https://github.com/dotnet/docfx/releases/download/2.16.4/docfx.zip",
    [string] $nodeJSUrl = "https://nodejs.org/dist/v6.10.3/node-v6.10.3-x64.msi"
)

$gitCommand = "git"
$npmCommand = "c:\nodejs\npm.cmd"
$nodeCommand = "c:\nodejs\node.exe"
$gulpCommand = ".\node_modules\.bin\gulp.cmd"

$scriptPath = $MyInvocation.MyCommand.Path
$scriptHome = Split-Path $scriptPath
$docfxCommand = "$env:LOCALAPPDATA\docfx\docfx.exe"
$docFile = Join-Path $scriptHome "docfx.json"


function WriteToLog([string] $msg) {
    $dt = [System.DateTime]::UtcNow.ToString("T", [System.Globalization.CultureInfo]::InvariantCulture)
    "[$dt] $msg" | Out-File $logFile -Append
    Write-Output "[$dt] $msg"
}

function ValidateCommand {
    param($command)
    return (Get-Command $command -ErrorAction SilentlyContinue) -ne $null
}

WriteToLog("=== Starting generate documentation at '$($scriptHome)'")
Push-Location $scriptHome

if (-not($logFile)) {
    WriteToLog("Create log file '$($logFile)'")
    New-Item -ItemType File $logFile
}

# Check is docfx.exe exists
if (-not(ValidateCommand($docfxCommand))) {
    WriteToLog("Downloading DocFX package...")
    New-Item -Path "$env:LOCALAPPDATA\DocFX" -Type directory -Force | Out-Null
    [Net.WebRequest]::DefaultWebProxy.Credentials = [Net.CredentialCache]::DefaultCredentials
    $outFile = "$env:LOCALAPPDATA\docfx\docfx.zip"
    Invoke-WebRequest $docfxUrl -OutFile $outFile
    WriteToLog("Extract docfx.zip")
    Add-Type -AssemblyName System.IO.Compression.FileSystem
    [System.IO.Compression.ZipFile]::ExtractToDirectory("$outFile", "$env:LOCALAPPDATA\DocFX")
}


# Update submodules
if (-not(ValidateCommand($gitCommand))) {
    WriteToLog("Git is required however it is not installed.")
}

if (-not(ValidateCommand($npmCommand))) {
    WriteToLog("Npm is required however it is not installed.")
    WriteToLog("Download NodeJS")

    if (-not(Test-Path "$env:LOCALAPPDATA\Temp")) {
        New-Item -Path "$env:LOCALAPPDATA\Temp" -Type directory | Out-Null
    }

    $outFile = "$env:LOCALAPPDATA\Temp\node.msi"
    Invoke-WebRequest $nodeJSUrl -OutFile $outFile

    WriteToLog("Install NodeJS")
    if ($logFile -ne "") {
        & msiexec /a $outFile /qn /L*V+ $logFile
    } else {
        & msiexec /a $outFile /qn
    }

    Start-Sleep -s 30
}

WriteToLog("Update Path environment.")
$env:Path += ";c:\nodejs\"

#Write-Host "Updating submodules..."
#& $gitCommand submodule update --init
#Write-Host "Submodules updated" -ForegroundColor Green

#if (-not(Get-Module -ListAvailable -Name Invoke-MsBuild)){
#	Write-Host "Install requeried powershell modules..."
#	Install-Module -Name Invoke-MsBuild -Scope CurrentUser
#}

#foreach ($sln in (Get-ChildItem "aimp_dotnet/AIMP.SDK/AIMP.SDK.csproj")) {
#    Write-Host "Start building $($sln.FullName)"
#	$buildSucceeded = Invoke-MsBuild -Path $sln.FullName -MsBuildParameters "/target:Clean;Build /property:Configuration=$configuration"
#	if ($buildSucceeded) {
#		ProcessLastExitCode $lastexitcode "Invoke-MsBuild -Path $($sln.FullName) -MsBuildParameters /target:Clean;Build /property:Configuration=$($configuration)"
#	}
#}

WriteToLog("Install npm dependencies")
& $npmCommand install --save-dev | Out-File $logFile -Append

WriteToLog("Install bower dependencies")
& $nodeCommand .\node_modules\bower\bin\bower install | Out-File $logFile -Append

WriteToLog("Execute gulp task 'default'")
& $gulpCommand default | Out-File $logFile -Append

WriteToLog("Execute docfx for '$($docFile)'")
if (-not($docFile)) {
    WriteToLog("'$($docFile)' not found. Exit")
    exit 1
}
& $docfxCommand $docFile | Out-File $logFile -Append

Pop-Location
WriteToLog("=== End generate documentation at '$($scriptHome)'")