$gitCommand = "git"
$npmCommand = "${Env:ProgramFiles(x86)}\nodejs\npm.cmd"
$nodeCommand = "${Env:ProgramFiles(x86)}\nodejs\node.exe"
$gulpCommand = ".\node_modules\.bin\gulp.cmd"

function Write-ToLog() {
    param(
        [string] $msg
    )

    $dt = [System.DateTime]::UtcNow.ToString("T", [System.Globalization.CultureInfo]::InvariantCulture)
    "[$dt] $msg" | Out-File $logFile -Append
    Write-Output "[$dt] $msg"
}

function Invoke-ValidateCommand() {
    param($command)
    return (Get-Command $command -ErrorAction SilentlyContinue) -ne $null
}

function Invoke-ValidateCommandVersion() {
    param($command, $version)
    return (Get-Command $command | % Version) -eq $version
}

function Invoke-BuildDocumentation() {
    param(
        [string] $docsPath = "",
        [string] $logFile = ".\build.log",
        [string] $docfxUrl = "https://github.com/dotnet/docfx/releases/download/2.16.4/docfx.zip",
        [string] $nodeJSUrl = "https://nodejs.org/dist/v6.10.3/node-v6.10.3-x64.msi"
    )

    $docfxCommand = "$env:LOCALAPPDATA\docfx\docfx.exe"
    $docFile = Join-Path $docsPath "docfx.json"

    Push-Location $scriptHome

    if (-not($logFile)) {
        Write-ToLog("Create log file '$($logFile)'")
        New-Item -ItemType File $logFile
    }

    Write-ToLog("=== Starting generate documentation at '$($docsPath)'")
    
    # Check is docfx.exe exists
    if (-not(Invoke-ValidateCommand($docfxCommand))) {
        Write-ToLog("Downloading DocFX package...")
        New-Item -Path "$env:LOCALAPPDATA\DocFX" -Type directory -Force | Out-Null
        [Net.WebRequest]::DefaultWebProxy.Credentials = [Net.CredentialCache]::DefaultCredentials
        $outFile = "$env:LOCALAPPDATA\docfx\docfx.zip"
        Invoke-WebRequest $docfxUrl -OutFile $outFile
        Write-ToLog("Extract docfx.zip")
        Add-Type -AssemblyName System.IO.Compression.FileSystem
        [System.IO.Compression.ZipFile]::ExtractToDirectory("$outFile", "$env:LOCALAPPDATA\DocFX")
    }

    # Update submodules
    #if (-not(Invoke-ValidateCommand($gitCommand))) {
        #Write-ToLog("Git is required however it is not installed.")
    #}

    if (-not(Invoke-ValidateCommand($npmCommand)) -or -not(Invoke-ValidateCommandVersion($npmCommand, "6.10.3.0"))) {
        Write-ToLog("Npm is required however it is not installed.")
        Write-ToLog("Download NodeJS")

        if (-not(Test-Path "$env:LOCALAPPDATA\Temp")) {
            New-Item -Path "$env:LOCALAPPDATA\Temp" -Type directory | Out-Null
        }

        $outFile = "$env:LOCALAPPDATA\Temp\node.msi"
        Invoke-WebRequest $nodeJSUrl -OutFile $outFile

        Write-ToLog("Install NodeJS")
        if ($logFile -ne "") {
            & msiexec /a $outFile /qnb /L*V+ $logFile 'TARGETDIR="c:\Program Files (x86)"'
        } else {
            & msiexec /a $outFile /qnb 'TARGETDIR="c:\Program Files (x86)"'
        }

        Start-Sleep -s 30

        Write-ToLog("Update Path environment.")
        $env:Path += ";c:\Program Files (x86)\nodejs"
    }

    Write-ToLog("Install npm dependencies")
    & $npmCommand install --save-dev | Out-File $logFile -Append

    Write-ToLog("Install bower dependencies")
    & $nodeCommand .\node_modules\bower\bin\bower install | Out-File $logFile -Append

    Write-ToLog("Execute gulp task 'default'")
    & $gulpCommand default | Out-File $logFile -Append

    Write-ToLog("Execute docfx for '$($docFile)'")
    if (-not($docFile)) {
        Write-ToLog("'$($docFile)' not found. Exit")
    } else {
        & $docfxCommand $docFile | Out-File $logFile -Append
    }

    Pop-Location
    Write-ToLog("=== End generate documentation")
}

Export-ModuleMember -Function Invoke-BuildDocumentation
