## AIMP DotNet SDK

*AIMP DotNet* lets you write a plugin for the [AIMP](http://www.aimp.ru) media player
in **pure C#** - no C++/CLI wrapper, no native proxy layer. Both x86 and x64 builds
of the player are supported.

## How it works

A tiny native DLL (`aimp_dotnet.dll`) is the only thing AIMP loads. It starts the
CLR, asks the managed host for the plugin object and hands the resulting COM
callable wrapper (CCW) back to the player. From that point every `IAIMPPlugin`
vtable call goes straight into managed code; services such as `IAIMPCore` are
called back through ordinary COM interop.

```
AIMP -> aimp_dotnet.dll (native, no /clr)
     -> AIMP.Host.dll (stable): AppDomain per plugin -> loads that plugin's AIMP.SDK.dll
     -> AIMP.SDK.dll (net48): PluginHost -> NativePluginBridge -> CCW
     -> AIMP calls IAIMPPlugin vtable directly in C#
```

See [src/README.md](src/README.md) for the architecture, the public API and the
plugin authoring guide.

## Build

Requires Visual Studio 2022+ with the C++ and .NET desktop workloads
(MSVC and .NET Framework 4.8 targeting pack).

```powershell
cd src
pwsh -File .\build.ps1
```

The ready-to-install folders appear in `src/bin/out/x86` and `src/bin/out/x64`.

## License

*AIMP DotNet* is licensed under the [Apache 2.0](LICENSE).
