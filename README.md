![alt tag](https://ci.appveyor.com/api/projects/status/github/martin211/aimp_dotnet?branch=master&svg=true)

# AIMP DotNet SDK plugin
 Microsoft .Net SDK for AIMP v3.60 / AIMP 4.00 media player (www.aimp.ru)
 
 
# About the Plugin
 This plug-in adds support for DotNet plugins at the AIMP media player.
 Currently does not fully implements the original SDK.
 
 Implemented services:
 - MenuManager
 - ActionManager (has not the hotkeys implementation)
 - AlbumArtManager
 - ConfigurationManager
 - MUIManager
 - PlayListManager
 - Visualization
 - Play back

# Installation

1. Download last release
2. Copy plugin to %AIMP%\Plugins folder (example: plugins\dotnet_myplugin)
3. Rename file aimp_dotnet.dll to dotnet_myplugin.dll
4. Add reference to AIMP.SDK.dll to your plugin project
 
# License
Apache 2.0
