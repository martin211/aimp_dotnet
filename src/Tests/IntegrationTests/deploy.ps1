#  ----------------------------------------------------
#  Installs the AimpTestRunner integration test plugin.
#
#  Unlike normal plugins it also needs the NUnit engine assemblies and the
#  test resources, so the whole build output folder is copied.
#  ----------------------------------------------------

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $AimpDirectory,

    [ValidateSet('x86', 'x64')]
    [string] $Platform = 'x86',

    [ValidateSet('Debug', 'Release')]
    [string] $Configuration = 'Release',

    [string] $Name = 'AimpTestRunner'
)

$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent (Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path))

if (-not (Test-Path (Join-Path $AimpDirectory 'aimp.exe'))) {
    throw "'$AimpDirectory' does not look like an AIMP installation (aimp.exe not found)."
}

$source = Join-Path $root "Tests\IntegrationTests\bin\$Platform\$Configuration"
if (-not (Test-Path $source)) {
    throw "Test plugin output not found: $source. Run build.ps1 first."
}

$shim = Join-Path $root "SDK\bin\$Platform\$Configuration\aimp_dotnet.dll"
if (-not (Test-Path $shim)) {
    $shim = Join-Path $root "SDK\bin\$Platform\$Configuration\aimp_managed.dll"
}
if (-not (Test-Path $shim)) {
    $shim = Join-Path $root "bin\out\$Platform\aimp_managed\aimp_managed.dll"
}
if (-not (Test-Path $shim)) {
    throw "Native shim not found. Run build.ps1 first."
}

$hostDll = Join-Path $root 'bin\managed\AIMP.Host.dll'
if (-not (Test-Path $hostDll)) {
    throw "AIMP.Host.dll not found. Run build.ps1 first."
}

$target = Join-Path (Join-Path $AimpDirectory 'Plugins') $Name
if (Test-Path $target) {
    Remove-Item $target -Recurse -Force
}

New-Item $target -ItemType Directory -Force | Out-Null
Copy-Item (Join-Path $source '*') $target -Recurse -Force

# AIMP loads <name>\<name>.dll; the managed assembly is <name>_plugin.dll.
$managed = Join-Path $target 'AimpTestRunner.dll'
if (Test-Path $managed) {
    Move-Item $managed (Join-Path $target ($Name + '_plugin.dll')) -Force
}

Copy-Item $shim (Join-Path $target ($Name + '.dll'))
Copy-Item $hostDll (Join-Path $target 'AIMP.Host.dll')

Get-ChildItem $target -Filter *.log -ErrorAction SilentlyContinue | Remove-Item -Force

Write-Host "Deployed integration tests to: $target"
Get-ChildItem $target | ForEach-Object { Write-Host "  $($_.Name)" }
