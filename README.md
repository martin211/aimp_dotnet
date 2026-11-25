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

## Layout

```
src/
  aimp_dotnet.sln                     solution (shim x86/x64 + managed projects)
  SDK/
    AIMP.Host/                        stable loader: AppDomain per plugin, SDK version isolation
    AIMP.SDK/                         single managed assembly:
      SDK/                            public v1 plugin API
      Runtime/                        internal v1 object implementations
      Native/                         [ComImport] projections of api*.h
      Bridges/                        CCW bridges for extensions
      Loader/                         plugin host and per-plugin bootstrap
      Internal/                       low-level COM/string/logging helpers
    aimp_dotnet/                      native bootstrap DLL (aimp_dotnet.dll)
  Plugins/
    dotnet_musiclibrary/              dotnet_musiclibrary port (media library demo)
    dotnet_simple/                    minimal example plugin
  Aimp.Shim.SmokeTest/               console test that loads the shim like AIMP does
  build.ps1                          build + smoke test
  deploy.ps1                         copy the result into an AIMP installation
```

## Build

Requires Visual Studio 2022+ with the C++ and .NET desktop workloads
(MSVC and .NET Framework 4.8 targeting pack).

```powershell
cd src
pwsh -File .\build.ps1
```

The ready-to-install folders appear in `src/bin/out/x86` and `src/bin/out/x64`.

## Versioning

The first three version components mirror the AIMP SDK version (currently
`6.00.3100`). GitVersion adds our own revision as the prerelease suffix and as
the fourth `FileVersion` component:

| Build | SemVer | AssemblyVersion | FileVersion |
|---|---|---|---|
| pull request | `6.0.3100-beta.N` | `6.0.3100.0` | `6.0.3100.N` |
| `master` | `6.0.3100-rc.N` | `6.0.3100.0` | `6.0.3100.N` |
| stable tag `v6.0.3100` | `6.0.3100` | `6.0.3100.0` | `6.0.3100.0` |

The base version is configured once in `GitVersion.yml` (`next-version`). When
AIMP publishes a new SDK, update it there, for example to `6.0.3200`.

Stable releases are created only from a tag that points to a commit reachable
from `master`:

```powershell
git tag v6.0.3100
git push origin v6.0.3100
```

The CI checks that:

- a tag build is an ancestor of `origin/master`;
- a tag build has no prerelease suffix and matches the tag name;
- `master` builds use the `rc` label;
- pull request builds use the `beta` label.

Local builds without CI use `6.0.3100` / `6.0.3100.0` from
`src/Directory.Build.props`.

## Legacy version

The previous C++/CLI implementation is tagged **`v1`** and removed from the working
tree. To look at it:

```powershell
git worktree add ..\aimp_dotnet-v1 v1
```

The CI/NUKE build scripts in the repository root still describe the `v1` layout and
will be updated when the new pipeline is decided.

## License

*AIMP DotNet* is licensed under the [Apache 2.0](LICENSE).
