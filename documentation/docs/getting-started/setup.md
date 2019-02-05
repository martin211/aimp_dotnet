# Getting Started
AIMP DotNet SDK is a proxy plugin that allow you to write plugins for [AIMP](http://aimp.ru) on C# or other .Net language.

This guide will walk you through the process of developing plugin for your AIMP media player.

## How to get
Bin releases with demo plugins https://github.com/martin211/aimp_dotnet/releases
Offical NuGet relases feed https://www.nuget.org/packages/AimpSDK
MyGet releases feed https://www.myget.org/F/aimpsdk/api/v3/index.json
MyGet feed contains the packages with beta features.

## Prerequisites
Following components should be installed on your PC:

- .NET Framework 4.6.2 or newer.
- C++ redistributable 2017

## SDK structure
SDK consists of two components.
- AIMP.SDK.dll - contains the definitions for services and objects from original SDK
- aimp_dotnet.dll - the proxy plugin

## Your first plugin
- You should add both assemblies to project references: AIMP.SDK.dll and aimp_dotnet.dll
- Add main plugin class inherited from AimpPlugin
- If you added package from NuGet, you can find gulpfile.js file at your project. Open that file and set correct values for [pluginName](https://gitlab.com/martin211/aimp_dotnet/blob/develop/src/Plugins/dotnet_SmartPlaylist/gulpfile.js#L14), [aimpFolder](https://gitlab.com/martin211/aimp_dotnet/blob/develop/src/Plugins/dotnet_SmartPlaylist/gulpfile.js#L15) and [paths](17).

##How to deploy new plugin
According the AIMP specification, the main plugin dll file should have the same name as his folder. Consequently the aimp_dotnet.dll should be renamed as **[folder_name].dll**

##Troubleshooting
1. AIMP did not display you plugin at Plugins setting.
It's mean that proxy plugin cannot find or loaded you plugin. 
The reason can be that not all related dll was copied to plugin folder.

Anyway you can check that proxy plugin is works correct. For it remove assembly of your plugin from plugin folder. Stay only the proxy plugin that should be named as [folder_name].dll. After that run the AIMP and open Plugins section at Options menu,  you should see the Proxy plugin at list. If not, check Prerequisites

  