## AIMP DotNet SDK
[![Github All Releases](https://img.shields.io/github/downloads/martin211/aimp_dotnet/latest/aimp.sdk.zip.svg)](https://github.com/martin211/aimp_dotnet/releases/latest)
[![test](https://img.shields.io/github/tag/martin211/aimp_dotnet.svg)](https://img.shields.io/github/tag/martin211/aimp_dotnet.svg)

## What is it?
*AIMP DotNet* allows you to create a plugin for [AIMP](http://www.aimp.ru) media player on .Net

### Description
AIMP DotNet SDK this is a proxy plugin written on C++ CLI and C++. It provide ability to call AIMP methods directly from C# code.
SDK contain two parts:
1. AIMP.SDK library.
   Contains a definitions for SDK interfaces.
2. aimp_dotnet library
   Contains implementations of interfaces from AIMP.SDK library. All code written on C++ CLI and some native parts on C++

For more information you can use demo plugins.

### How to write plugin
1. Use [NuGet package](https://www.nuget.org/packages/AimpSDK/)
2. Optional. Install [Command Task Runner](https://marketplace.visualstudio.com/items?itemName=MadsKristensen.CommandTaskRunner) extension for Visual Studio
3. Remember that a aimp_dotnet.dll this is a entry point for AIMP plugin. And it should be called as your plugin. You can use CopyPlugin.ps1 script to get correct plugin structure.

## How to build
### Prerequisites
1. [Visual Studio 2017](https://www.visualstudio.com/downloads/) or MsBuild tools 2017
2. Following components should be installed: 
	- VS++ 2017 v141
	- Visual C++ ATL support
	- C++/CLI support
    - Windows SDK Version: 10.0.17763.0

## License
*AIMP DotNet* is licensed under the [Apache 2.0](LICENSE).
