$nodeCommand = "${Env:ProgramFiles(x86)}\nodejs\node.exe"

function Invoke-ValidateCommandVersion() {
    param($command, $version)
    return (Get-Command $command | % Version) -eq $version
}

Invoke-ValidateCommandVersion -command $nodeCommand -version "6.10.3.0"