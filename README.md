# AIMP DotNet Sdk plugin
 Microsoft .Net SDK for AIMP v3.60 / AIMP 4.00 media player (wwww.aimp.ru)
 
 
# About the Plugin
 This plug-in adds support for DotNet plugins at the AIMP media player.
 Currently does not fully implements the original SDK.
 
 Implemented services:
 - MenuManager
 - ActionManager (has not the hotkeys implementation)
 - AlbumArtManager
 - ConfigurationManager
 - MUIManager
 - PlayListManager (in progress)

# Dependencies
 boost 1.5X. 
 You can download binaries from sourceforge.
 
# Compilation
 Download boost binaries.
 Copy '../boost/' folder to the 'aimp_dotnet/include/' folder.
 Copy all files from 'lib32-msvc-14.0' folder to the 'aimp_dotnet/lib/' folder.
 
# Installation

1. Download last release
2. Copy plugin to %AIMP%\Plugins folder (example: plugins\dotnet_myplugin)
3. Rename file aimp_dotnet.dll to dotnet_myplugin.dll
4. Add reference to AIMP.SDK.dll to your plugin project
 
# License
Apache 2.0
