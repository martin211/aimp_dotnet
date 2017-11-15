param(
    [Parameter(Mandatory=$true)] [string] $dockerSonarContainer
)

$ErrorActionPreference = "Stop"

if (-not (Get-Module -ListAvailable -Name Docker )) {
	Install-Module -Scope CurrentUser Docker
}