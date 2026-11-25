#  ----------------------------------------------------
#  Builds one plugin and deploys it into the configured AIMP installation.
#
#  Used by the generated Rider run configurations as a before-launch step:
#  only the plugin being debugged is built and copied, other plugins are
#  left untouched.
#  ----------------------------------------------------

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $Project,

    [ValidateSet('Debug', 'Release')]
    [string] $Configuration = 'Debug',

    [ValidateSet('x86', 'x64')]
    [string] $Platform = 'x86',

    # Overrides AimpDir from AimpSettings.props / AIMP_DIR.
    [string] $AimpDirectory
)

$ErrorActionPreference = 'Stop'

function Find-MSBuild {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (Test-Path $vswhere) {
        $found = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' |
            Select-Object -First 1
        if ($found) {
            return $found
        }
    }

    if (-not [string]::IsNullOrWhiteSpace($env:MSBUILD_EXE_PATH) -and (Test-Path $env:MSBUILD_EXE_PATH)) {
        return $env:MSBUILD_EXE_PATH
    }

    $command = Get-Command msbuild.exe -ErrorAction SilentlyContinue
    if ($command) {
        return $command.Source
    }

    $fallback = Get-ChildItem 'C:\Program Files\Microsoft Visual Studio\*\*\MSBuild\Current\Bin\MSBuild.exe' `
        -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($fallback) {
        return $fallback.FullName
    }

    throw 'MSBuild.exe was not found. Install Visual Studio with the C++ workload.'
}

if (-not (Test-Path $Project)) {
    throw "Project not found: $Project"
}

if (-not [string]::IsNullOrWhiteSpace($AimpDirectory) -and
    -not (Test-Path (Join-Path $AimpDirectory 'AIMP.exe'))) {
    throw "'$AimpDirectory' does not look like an AIMP installation (AIMP.exe not found)."
}

$msbuild = Find-MSBuild
$arguments = @(
    $Project,
    '/t:DeployPlugin',
    "/p:Configuration=$Configuration",
    "/p:Platform=$Platform",
    "/p:AimpPlatform=$Platform",
    '/nologo',
    '/v:m'
)

if (-not [string]::IsNullOrWhiteSpace($AimpDirectory)) {
    $arguments += "/p:AimpDir=$AimpDirectory"
}

Write-Host "Deploying $Project ($Configuration|$Platform) to AIMP"
& $msbuild @arguments
if ($LASTEXITCODE -ne 0) {
    throw "Deploy failed: $Project"
}
