[CmdletBinding()]
Param(
    [Parameter(Mandatory=$true)]
    [string] $action,
    [Parameter(Mandatory=$true)]
    [string] $ConfigurationName,
    [Parameter(Mandatory=$true)]
    [string] $TargetName,
    [string] $TargetDir,
    [string] $SolutionDir,
    [string] $ProjectDir,
    [string] $AimpVersion = "AIMP5.00.2344"
)

Write-Output "Windows PowerShell $($Host.Version)"

$PSScriptRoot = Split-Path $MyInvocation.MyCommand.Path -Parent

###########################################################################
# CONFIGURATION
###########################################################################

$CorePath = "$SolutionDir\$ConfigurationName"
$RootFolder = $(Get-Item $SolutionDir).Parent.Parent.FullName
$OutputPath = "$RootFolder\$AimpVersion\Plugins\$TargetName"
$exclude = @('aimp_dotnet.dll','AIMP.SDK.dll')

###########################################################################

function CopyCore {
    Copy-Item "$TargetDir\aimp_dotnet.dll" -Destination "$OutputPath\$TargetName.dll" -Force
    Copy-Item "$TargetDir\AIMP.SDK.dll" -Destination "$OutputPath\AIMP.SDK.dll" -Force
}

function CopyPlugin {
    $childs = Get-ChildItem "$TargetDir\*.dll" -Exclude $exclude
    ForEach ($file in $childs) {
        if ($file.BaseName -eq $TargetName) {
            Copy-Item $file.FullName -Destination "$OutputPath\${TargetName}_plugin.dll"
        }
        else {
            Copy-Item $file.FullName -Destination "$OutputPath"
        }
    }
}

function CopyLang {
    if (Test-Path -Path "$ProjectDir\Langs\") {
        Copy-Item "$ProjectDir\Langs\*" -Destination "$OutputPath\Langs" -Force
    }
}

function CopyDebugInfo {
    Get-ChildItem "$TargetDir\*.pdb" | % { Copy-Item -Path $_ -Destination "$OutputPath" -Force }
}

Write-Output "Copy plugin:`t$TargetName"
Write-Output "Configuration:`t$ConfigurationName"
Write-Output "TargetName:`t`t$TargetName"
Write-Output "TargetDir:`t`t$TargetDir"
Write-Output "SolutionDir:`t$SolutionDir"
Write-Output "ProjectDir:`t`t$ProjectDir"
Write-Output "AimpVersion:`t$AimpVersion"

if ((Test-Path $OutputPath) -eq $false) {
    New-Item -ItemType directory -Path $OutputPath
}

if ($action -eq 'copy') {
    Write-Output "Copy Plugin libraries"
    CopyPlugin

    Write-Output "Copy Core libraries"
    CopyCore

    Write-Output "Copy Language files"
    CopyLang

    Write-Output "Copy PDB files"
    CopyDebugInfo

    exit 0;
}

if ($action -eq 'clean') {
    Remove-Item -path $OutputPath\*.dll
    Remove-Item -path $OutputPath\*.pdb
    exit 0;
}
