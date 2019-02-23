param($installPath, $toolsPath, $package, $project)

$projectPath = (Split-Path $project.FullName)
#$npmPath = (join-path $toolsPath "npm.cmd")
Get-Command npm
cd $projectPath
Write-Output "Install npm packages at $projectPath"
& npm install
Write-Output "Prepare js file"
(Get-Content $projectPath\gulpfile.js).replace('[project]', $project.Name) | Set-Content $projectPath\gulpfile.js