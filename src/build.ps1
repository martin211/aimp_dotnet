#  ----------------------------------------------------
#  AIMP managed host - build script
#
#  Builds:
#    src/SDK/bin/<platform>/<config>/aimp_dotnet.dll    native shim
#    src/bin/managed/AIMP.Host.dll                      stable launcher
#    src/bin/managed/AIMP.SDK.dll                       managed host + public SDK
#    src/Plugins/.../bin/dotnet_musiclibrary.dll        music library demo plugin
#    src/Plugins/.../bin/Aimp.SamplePlugin.dll          example plugin (not deployed)
#    src/Plugins/Aimp.Demo/bin/dotnet_demo.dll          dotnet_demo port
#    src/Plugins/dotnet_ExtendDialogWindow/bin/...      options/external dialog demo
#
#  Assembles a ready to copy layout in bin/out/<platform>.
#  The Visual Studio solution (aimp_dotnet.sln) produces the same binaries.
#  ----------------------------------------------------

[CmdletBinding()]
param(
    [ValidateSet('Debug', 'Release')]
    [string] $Configuration = 'Release',

    [switch] $SkipTests,

    # Optional version values (for example from GitVersion).
    [string] $Version,
    [string] $AssemblyVersion,
    [string] $FileVersion,
    [string] $InformationalVersion
)

$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path

$versionArguments = @()
if (-not [string]::IsNullOrWhiteSpace($Version)) {
    $versionArguments += "/p:Version=$Version"
}
if (-not [string]::IsNullOrWhiteSpace($AssemblyVersion)) {
    $versionArguments += "/p:AssemblyVersion=$AssemblyVersion"
}
if (-not [string]::IsNullOrWhiteSpace($FileVersion)) {
    $versionArguments += "/p:FileVersion=$FileVersion"
}
if (-not [string]::IsNullOrWhiteSpace($InformationalVersion)) {
    $versionArguments += "/p:InformationalVersion=$InformationalVersion"
}

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

$msbuild = Find-MSBuild
Write-Host "MSBuild : $msbuild"

$platforms = @(
    @{ Name = 'x86'; Native = 'Win32'; Target = 'x86' },
    @{ Name = 'x64'; Native = 'x64'; Target = 'x64' }
)

function Invoke-MSBuild {
    param([string] $Project, [string[]] $Arguments)

    & $msbuild $Project @Arguments /nologo /v:m
    if ($LASTEXITCODE -ne 0) {
        throw "Build failed: $Project"
    }
}

Write-Host '=== managed host and plugins ==='
Invoke-MSBuild "$root\SDK\AIMP.SDK\AIMP.SDK.csproj" (@('/restore', "/p:Configuration=$Configuration") + $versionArguments)
Invoke-MSBuild "$root\SDK\AIMP.Host\AIMP.Host.csproj" (@('/restore', "/p:Configuration=$Configuration") + $versionArguments)
Invoke-MSBuild "$root\Plugins\dotnet_musiclibrary\Aimp.MusicLibraryPlugin.csproj" (@('/restore', "/p:Configuration=$Configuration") + $versionArguments)
Invoke-MSBuild "$root\Plugins\dotnet_simple\Aimp.SamplePlugin.csproj" (@('/restore', "/p:Configuration=$Configuration") + $versionArguments)
Invoke-MSBuild "$root\Plugins\Aimp.Demo\Aimp.Demo.csproj" (@('/restore', "/p:Configuration=$Configuration") + $versionArguments)
Invoke-MSBuild "$root\Plugins\dotnet_ExtendDialogWindow\dotnet_ExtendDialogWindow.csproj" (@('/restore', "/p:Configuration=$Configuration") + $versionArguments)

function Find-ManagedDll([string] $name) {
    $file = Get-ChildItem -Path $root -Recurse -Filter $name -File |
        Where-Object {
            $_.FullName -notmatch '\\obj\\' -and
            $_.FullName -notmatch '\\bin\\out\\'
        } |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1

    if (-not $file) {
        throw "Managed output not found: $name"
    }

    return $file.FullName
}

$managedOutput = Join-Path $root 'bin\managed'
$musicLibraryDll = Find-ManagedDll 'dotnet_musiclibrary.dll'
$samplePluginDll = Find-ManagedDll 'Aimp.SamplePlugin.dll'
$demoPluginDll = Find-ManagedDll 'dotnet_demo.dll'
$extDialogPluginDll = Find-ManagedDll 'dotnet_ExtendDialogWindow.dll'

foreach ($platform in $platforms) {
    Write-Host "=== shim $($platform.Name) ==="
    Invoke-MSBuild "$root\SDK\aimp_dotnet\Aimp.Shim.vcxproj" (@(
        "/p:Configuration=$Configuration",
        "/p:Platform=$($platform.Native)",
        '/m'
    ) + $versionArguments)

    Write-Host "=== integration test plugin $($platform.Name) ==="
    Invoke-MSBuild "$root\Tests\IntegrationTests\AimpTestRunner.csproj" (@(
        '/restore',
        "/p:Configuration=$Configuration",
        "/p:Platform=$($platform.Target)"
    ) + $versionArguments)

    # The shim DLL name comes from TargetName in Aimp.Shim.vcxproj. Accept the
    # current and the legacy name so a rename in the project cannot break the
    # packaging step.
    $shimDirectory = Join-Path $root "SDK\bin\$($platform.Name)\$Configuration"
    $shim = @('aimp_dotnet.dll', 'aimp_managed.dll') |
        ForEach-Object { Join-Path $shimDirectory $_ } |
        Where-Object { Test-Path $_ } |
        Select-Object -First 1

    if (-not $shim) {
        $found = @(Get-ChildItem $shimDirectory -Filter '*.dll' -ErrorAction SilentlyContinue |
            ForEach-Object { $_.Name })
        $hint = if ($found.Count -eq 0) { 'no DLLs were produced' } else { $found -join ', ' }
        throw "Shim output not found in '$shimDirectory' (expected aimp_dotnet.dll); found: $hint"
    }

    $output = Join-Path $root "bin\out\$($platform.Name)"
    if (Test-Path $output) {
        Remove-Item $output -Recurse -Force
    }

    # SDK payload: native shim, managed SDK/host and their dependencies.
    # The SDK archive always ships the shim as aimp_dotnet.dll.
    $sdkDirectory = Join-Path $output 'sdk'
    New-Item $sdkDirectory -ItemType Directory -Force | Out-Null
    Copy-Item $shim (Join-Path $sdkDirectory 'aimp_dotnet.dll')
    Get-ChildItem $managedOutput -Filter '*.dll' | Copy-Item -Destination $sdkDirectory -Force

    # Demo plugins: each plugin gets its own AIMP folder with a renamed shim.
    $pluginsDirectory = Join-Path $output 'plugins'
    New-Item $pluginsDirectory -ItemType Directory -Force | Out-Null

    $demoPlugins = @(
        @{ Name = 'dotnet_musiclibrary'; Dll = $musicLibraryDll },
        @{ Name = 'dotnet_simple'; Dll = $samplePluginDll },
        @{ Name = 'dotnet_demo'; Dll = $demoPluginDll },
        @{ Name = 'dotnet_ExtendDialogWindow'; Dll = $extDialogPluginDll }
    )

    foreach ($demo in $demoPlugins) {
        $target = Join-Path $pluginsDirectory $demo.Name
        New-Item $target -ItemType Directory -Force | Out-Null
        Copy-Item $shim (Join-Path $target ($demo.Name + '.dll'))
        Get-ChildItem $managedOutput -Filter '*.dll' | Copy-Item -Destination $target -Force
        Copy-Item $demo.Dll (Join-Path $target ($demo.Name + '_plugin.dll'))
    }

    # Backward-compatible ready-to-deploy music library demo folder.
    # The smoke test and deploy.ps1 still expect aimp_managed\aimp_managed.dll.
    $legacyTarget = Join-Path $output 'aimp_managed'
    New-Item $legacyTarget -ItemType Directory -Force | Out-Null
    Copy-Item $shim (Join-Path $legacyTarget 'aimp_managed.dll')
    Get-ChildItem $managedOutput -Filter '*.dll' | Copy-Item -Destination $legacyTarget -Force
    Copy-Item $musicLibraryDll (Join-Path $legacyTarget 'dotnet_musiclibrary.dll')

    Write-Host "=== smoke test $($platform.Name) ==="
    Invoke-MSBuild "$root\Aimp.Shim.SmokeTest\Aimp.Shim.SmokeTest.csproj" (@(
        '/restore',
        '/t:Rebuild',
        "/p:Configuration=$Configuration",
        "/p:Platform=$($platform.Target)",
        "/p:OutputPath=$output\"
    ) + $versionArguments)
}

if (-not $SkipTests) {
    foreach ($platform in $platforms) {
        $output = Join-Path $root "bin\out\$($platform.Name)"
        $executable = Join-Path $output 'Aimp.Shim.SmokeTest.exe'

        Write-Host ''
        Write-Host "=== running smoke test ($($platform.Name)) ==="
        & $executable
        if ($LASTEXITCODE -ne 0) {
            throw "Smoke test failed for $($platform.Name)."
        }

        $log = Join-Path $output 'aimp_managed\aimp_managed.log'
        if (Test-Path $log) {
            Write-Host '--- aimp_managed.log ---'
            Get-Content $log | ForEach-Object { Write-Host "  $_" }
        }

        $shimLog = Join-Path $output 'aimp_managed\aimp_dotnet.log'
        if (Test-Path $shimLog) {
            Write-Host '--- aimp_dotnet.log ---'
            Get-Content $shimLog | ForEach-Object { Write-Host "  $_" }
        }
    }
}

Write-Host ''
Write-Host 'Done. Copy bin/out/x86 (or x64) into the AIMP "Plugins" folder.'
