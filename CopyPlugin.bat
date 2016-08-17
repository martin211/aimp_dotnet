set ConfigurationName=%~1

IF %ConfigurationName% == "Debug" (
    IF NOT EXIST "$(SolutionDir)..\AIMP4.00\Plugins\$(TargetName)" mkdir "$(SolutionDir)..\AIMP4.00\Plugins\$(TargetName)"
        copy "$(TargetPath)" "$(SolutionDir)..\AIMP4.00\Plugins\$(TargetName)\$(ProjectName)_plugin.dll"
        copy "$(SolutionDir)$(ConfigurationName)\aimp_dotnet.dll" "$(SolutionDir)..\AIMP4.00\Plugins\$(TargetName)\$(ProjectName).dll"
        copy "$(SolutionDir)\AIMP.SDK\$(OutDir)AIMP.SDK.dll" "$(SolutionDir)..\AIMP4.00\Plugins\$(TargetName)\AIMP.SDK.dll"
)

IF %ConfigurationName% == "Release" (
    IF NOT EXIST "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos" mkdir "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos"
    IF NOT EXIST "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos\$(TargetName)" mkdir "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos\$(TargetName)"

    copy "$(TargetPath)" "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos\$(TargetName)\$(ProjectName)_plugin.dll"
    copy "$(SolutionDir)\AIMP.SDK\$(OutDir)AIMP.SDK.dll" "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos\$(TargetName)\AIMP.SDK.dll"
    copy "$(SolutionDir)$(ConfigurationName)\aimp_dotnet.dll" "$(SolutionDir)\$(ConfigurationName)\AIMP.SDK\Demos\$(TargetName)\$(ProjectName).dll"
)