#  ----------------------------------------------------
#  Installs one managed plugin into an AIMP installation.
#
#  AIMP 5 expects: Plugins\<name>\<name>.dll.  The native shim is copied
#  under <name>.dll, the managed plugin as <name>_plugin.dll.  Run the
#  script once per plugin with a different -Name to install several
#  plugins side by side.
#
#  Examples:
#    pwsh -File .\deploy.ps1 -AimpDirectory "C:\AIMP" -Platform x86 `
#        -Name dotnet_musiclibrary
#
#    pwsh -File .\deploy.ps1 -AimpDirectory "C:\AIMP" -Platform x86 `
#        -Name MyPlugin -PluginDll ".\out\MyPlugin.dll"
#  ----------------------------------------------------

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $AimpDirectory,

    [ValidateSet('x86', 'x64')]
    [string] $Platform = 'x86',

    # Name of the AIMP plugin and of its folder. Must match <name>.dll.
    [string] $Name = 'aimp_managed',

    # Managed plugin assembly. Defaults to the built music library demo.
    [string] $PluginDll,

    [ValidateSet('Debug', 'Release')]
    [string] $Configuration = 'Release'
)

$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path

if (-not (Test-Path (Join-Path $AimpDirectory 'aimp.exe'))) {
    throw "'$AimpDirectory' does not look like an AIMP installation (aimp.exe not found)."
}

# Native shim: prefer the project output, fall back to the assembled layout.
$shim = Join-Path $root "SDK\bin\$Platform\$Configuration\aimp_managed.dll"
if (-not (Test-Path $shim)) {
    $shim = Join-Path $root "bin\out\$Platform\aimp_managed\aimp_managed.dll"
}
if (-not (Test-Path $shim)) {
    throw "Native shim not found. Run build.ps1 first."
}

# Managed host + public SDK.
$sdkDll = Join-Path $root 'bin\managed\AIMP.SDK.dll'
if (-not (Test-Path $sdkDll)) {
    $sdkDll = Get-ChildItem -Path $root -Recurse -Filter 'AIMP.SDK.dll' -File |
        Where-Object { $_.FullName -notmatch '\\obj\\' -and $_.FullName -notmatch '\\bin\\out\\' } |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
}
if (-not (Test-Path $sdkDll)) {
    throw "AIMP.SDK.dll not found. Run build.ps1 first."
}

# Version stable launcher shared by every plugin folder.
$hostDll = Join-Path $root 'bin\managed\AIMP.Host.dll'
if (-not (Test-Path $hostDll)) {
    $hostDll = Get-ChildItem -Path $root -Recurse -Filter 'AIMP.Host.dll' -File |
        Where-Object { $_.FullName -notmatch '\\obj\\' -and $_.FullName -notmatch '\\bin\\out\\' } |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
}
if (-not (Test-Path $hostDll)) {
    throw "AIMP.Host.dll not found. Run build.ps1 first."
}

# Managed plugin assembly.
if (-not $PluginDll) {
    $PluginDll = Join-Path $root 'Plugins\dotnet_musiclibrary\bin\dotnet_musiclibrary.dll'
}
if (-not (Test-Path $PluginDll)) {
    $PluginDll = Join-Path $root "bin\out\$Platform\aimp_managed\dotnet_musiclibrary.dll"
}
if (-not (Test-Path $PluginDll)) {
    throw "Managed plugin DLL not found: $PluginDll"
}

$target = Join-Path (Join-Path $AimpDirectory 'Plugins') $Name
if (Test-Path $target) {
    Remove-Item $target -Recurse -Force
}

New-Item $target -ItemType Directory -Force | Out-Null

Copy-Item $shim (Join-Path $target ($Name + '.dll'))

# Dependencies shipped next to the plugin assembly (System.*, etc.).
$pluginDirectory = Split-Path $PluginDll
$pluginFullPath = (Resolve-Path $PluginDll).Path
Get-ChildItem $pluginDirectory -Filter '*.dll' |
    Where-Object {
        $_.FullName -ne $pluginFullPath -and
        $_.Name -ne 'AIMP.SDK.dll' -and
        $_.Name -ne 'AIMP.Host.dll'
    } |
    Copy-Item -Destination $target -Force

# SDK, extra dependencies and the stable host. Copied last so the SDK's exact
# dependency versions win over plugin-local copies.
Get-ChildItem (Split-Path $sdkDll) -Filter '*.dll' |
    Copy-Item -Destination $target -Force

Copy-Item $PluginDll (Join-Path $target ($Name + '_plugin.dll'))

Write-Host "Deployed '$Name' to: $target"
Get-ChildItem $target | ForEach-Object { Write-Host "  $($_.Name)" }
