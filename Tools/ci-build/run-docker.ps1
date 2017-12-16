param(
    [Parameter(Mandatory=$true)] [string] $dockerSonarContainer
)

$mysqlContainerName = "dev.mysql";
$sonarContainerName = "dev.sonarqube"

$ErrorActionPreference = "Stop"

if (-not (Get-Module -ListAvailable -Name Docker )) {
	Install-Module -Scope CurrentUser Docker
}

$r = docker inspect --format "{{.State.Running}}" $mysqlContainerName
if ($r -eq $false) {
	docker start $mysqlContainerName
	
	do
	{
		Start-Sleep -s 10	
		$r = docker inspect --format "{{.State.Running}}" $mysqlContainerName
		if ($r -eq $false) {
			docker start $mysqlContainerName
		}
		else {
			$log = docker logs $mysqlContainerName
			if ($log -contains "mysqld: ready for connections" -eq $true) {
			}
		}
	}	
	while ($r -eq $false)	
}

#$r = docker inspect --format "{{.State.Running}}" $sonarContainerName
#if ($r -eq $false) {
#	docker start $sonarContainerName
#}