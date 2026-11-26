# AIMP Managed Host

Цель: **плагин, написанный на C#, загружается в AIMP без C++/CLI**.

Это текущая реализация `aimp_dotnet`. Старая C++/CLI версия удалена из рабочего
дерева и доступна по тегу `v1`:

```powershell
git worktree add ..\aimp_dotnet-v1 v1
```

Публичный API плагина сохранён совместимым с `v1`: пространство имён `AIMP.SDK`,
класс `AimpPlugin`, атрибут `[AimpPlugin]`, интерфейсы `IAimpPlayer`, `IAimpCore`,
`AimpActionResult` и т.д. Поэтому старые плагины собираются без изменений исходного
кода — меняется только способ загрузки в плеер.

## Что уже проверено

| Проверка | Результат |
|---|---|
| x86 шим + managed host + плагин (smoke test) | PASS |
| x64 шим + managed host + плагин (smoke test) | PASS |
| AIMP 5.40.2655 (x86), реальный плеер | плагин загружен, расширения зарегистрированы |
| AIMP 5.40.2655 x64, реальный плеер | плагин загружен, расширения зарегистрированы |

## Архитектура

```
AIMP
 │  LoadLibrary + AIMPPluginGetHeader(IAIMPPlugin**)
 ▼
aimp_dotnet.dll                     чистая нативная DLL (без /clr)
 │  CLRCreateInstance → ICLRRuntimeHost::Start
 │  ExecuteInDefaultAppDomain("AIMP.Host.Bootstrap.Start", "<dir>|<hmodule>")
 ▼
AIMP.Host.dll                        .NET Framework 4.8, стабильный ABI
 │  AppDomain на каждый плагин
 │  Assembly.LoadFrom(<dir>\AIMP.SDK.dll)  ← версия SDK из папки плагина
 │  reflection → AIMP.Loader.Bootstrap.StartPlugin(dir, module)
 ▼
AIMP.SDK.dll                         .NET Framework 4.8, версия из папки плагина
 │  PluginHost: сканирует папку, находит AimpPlugin
 │  NativePluginBridge : IAimpPluginNative  →  Marshal.GetComInterfaceForObject
 │  ShimBridge: AimpShimSetPlugin(ccw)
 ▼
aimp_dotnet.dll  запоминает указатель и возвращает его AIMP
 ▼
AIMP вызывает vtable IAIMPPlugin → напрямую в managed код
```

Ключевая идея: нативный шим **не проксирует** вызовы. Он только поднимает CLR и
отдаёт AIMP указатель на CCW. Дальше весь обмен идёт через обычный COM-interop,
без промежуточного слоя. `AIMP.Host.dll` не зависит от версии `AIMP.SDK.dll`,
поэтому разные плагины могут использовать разные версии SDK одновременно.

## Слои `AIMP.SDK`

Всё managed-хостирование, публичный API и внутренние реализации живут в одной
сборке `AIMP.SDK.dll`, но строго разделены по папкам и видимости:

| Папка | Назначение | Видимость |
|---|---|---|
| `SDK/` | Публичный `v1` API: интерфейсы, которые плагин реализует или получает из ядра, `AimpPlugin`, `AimpPluginAttribute`, `AimpActionResult`, перечисления. | `public` |
| `Runtime/` | Внутренние реализации объектов `v1` (`IAimpPlayer`, `IAimpPlaylist`, `IAimpDataStorage`, …) поверх нативных объектов AIMP. Плагин видит только интерфейсы. | `internal` |
| `Native/` | Плоские `[ComImport]`-проекции `api*.h`: vtable-порядок методов AIMP. Публичные по требованию COM/CCW, но не являются API для автора плагина. | `public` (технически) |
| `Bridges/` | CCW-мосты: превращают managed-контракт расширения (`SDK/.../Extensions`) в нативную vtable AIMP. | `internal` |
| `Loader/` | `Bootstrap` (точка входа CLR), `PluginHost` (поиск плагина), `NativePluginBridge` (`IAIMPPlugin` CCW), `ShimBridge`. | `internal` (кроме `Bootstrap`) |
| `Internal/` | Низкоуровневые помощники: COM-обёртки, `AimpString`, `AimpPropertyBag`, `AimpIids`, `AimpLog`, `AimpResult`. | `internal` |

Правило: если тип не нужен автору плагина — он `internal` и лежит вне `SDK/`.
`AimpResult` (бывший `Compat`) переводит `HRESULT` нативных вызовов в
`AimpActionResult`; `Native/` (бывший `Interop/`) содержит только объявления
нативных интерфейсов.

Пошаговая инструкция по добавлению нового сервиса:
[русский](../docfx_project/articles/adding-a-service.ru.md) /
[English](../docfx_project/articles/adding-a-service.md).

## Структура репозитория

```
src/
  aimp_dotnet.sln                     // Solution: шим (x86/x64) + managed проекты
  Directory.Build.props               // общие MSBuild-настройки всех проектов
  AimpSettings.props.example          // шаблон локального пути к AIMP
  build.ps1                           // сборка раскладки + smoke test
  deploy.ps1                          // копирование готовой раскладки в AIMP
  deploy-plugin.ps1                   // сборка и деплой одного плагина для отладки
  SDK/
    AIMP.Host/                        // стабильный загрузчик: AppDomain + версия SDK
      Bootstrap.cs
      AIMP.Host.csproj
    AIMP.SDK/                         // managed host + публичный SDK
      SDK/                            // публичный v1 API
      Runtime/                        // внутренние обёртки v1-объектов
      Native/                         // [ComImport]-проекции api*.h
      Bridges/                        // CCW-мосты расширений
      Loader/                         // Bootstrap, PluginHost, NativePluginBridge
      Internal/                       // низкоуровневые помощники
    aimp_dotnet/                      // нативная DLL (C++, без /clr)
      shim.cpp
      Aimp.Shim.vcxproj
  Plugins/
    dotnet_musiclibrary/              // порт dotnet_musiclibrary (storage, providers, preimages, меню)
    dotnet_simple/                    // минимальный пример плагина на C#
    Aimp.Demo/                        // порт старого dotnet_demo (WinForms, меню, опции, теги)
    dotnet_ExtendDialogWindow/        // настройки плагина + внешний диалог настроек
  Aimp.Shim.SmokeTest/                // консольный тест: грузит шим как AIMP и дергает vtable
```

## Сборка

```powershell
cd src
pwsh -File .\build.ps1
```

Скрипт собирает всё через MSBuild, сам подбирает `PlatformToolset` (`v143` для CI,
иначе `v145`) и прогоняет smoke test для обеих разрядностей. То же самое можно
сделать из Visual Studio, открыв `src\aimp_dotnet.sln` и выбрав конфигурацию
`Release | x86` или `Release | x64` (`smoke test` собирается под выбранную
разрядность, managed-проекты — AnyCPU, как и положено net48-библиотекам).

Версия .NET SDK берётся из `global.json` в корне репозитория
(`rollForward: latestMajor`), поэтому подойдёт любой установленный SDK 8+.

## Отладка плагина в AIMP

Обычная сборка **ничего не копирует** в AIMP. Чтобы включить отладку из IDE,
плагин помечается в своём `.csproj`:

```xml
<AimpGenerateRunConfigurations>true</AimpGenerateRunConfigurations>
```

После первой Debug-сборки в `src\.run` появляются две конфигурации Rider:

| Конфигурация | Что делает |
|---|---|
| `<plugin> (AIMP)` | запускает `AIMP.exe` под отладчиком (mixed-mode) |
| `Deploy <plugin>` | собирает только этот проект и копирует его в `<AIMP>\Plugins` |

`<plugin> (AIMP)` выполняет `Deploy <plugin>` как шаг перед запуском, поэтому
F5 разворачивает **только отлаживаемый плагин**. Остальные проекты при этом не
собираются и в AIMP не попадают.

Ранее созданные вручную конфигурации типа `.NET Project` деплой больше не
выполняют — используйте сгенерированные `...(AIMP)` или удалите старые.

Имя папки, шима и конфигураций по умолчанию берётся из `AssemblyName`
(`AimpPluginName`), при необходимости переопределяется в проекте плагина:

```xml
<AimpPluginName>MyPlugin</AimpPluginName>
```

Развёрнутая папка выглядит так:

```
<AIMP>\Plugins\dotnet_musiclibrary\
  dotnet_musiclibrary.dll          шим (aimp_dotnet.dll)
  dotnet_musiclibrary_plugin.dll   managed-плагин (Debug)
  dotnet_musiclibrary.pdb          символы плагина
  AIMP.Host.dll / .pdb
  AIMP.SDK.dll / .pdb
  aimp_dotnet.pdb                  символы шима
```

Ту же операцию можно выполнить вручную (Visual Studio или консоль):

```powershell
pwsh -File .\deploy-plugin.ps1 `
    -Project .\Plugins\Aimp.Demo\Aimp.Demo.csproj `
    -Configuration Debug -Platform x86
```

Скрипт собирает только указанный проект через MSBuild и вызывает target
`DeployPlugin`. Принудительный деплой при обычной сборке остаётся доступен
через `/p:AimpDeployOnBuild=true`.

По умолчанию используется `F:\code\aimp\AIMP5.40.2655` (x86). Путь и
разрядность задаются один раз для всех проектов: скопируй
`src\AimpSettings.props.example` в `src\AimpSettings.props` (файл в
`.gitignore`) и поправь значения:

```xml
<Project>
  <PropertyGroup>
    <AimpDir>F:\code\aimp\AIMP5.40.2655_x64</AimpDir>
    <AimpPlatform>x64</AimpPlatform>
  </PropertyGroup>
</Project>
```

`Directory.Build.props` импортирует этот файл автоматически. Также можно
использовать переменные окружения `AIMP_DIR` / `AIMP_PLATFORM` или передать
свойства в MSBuild (`/p:AimpDir=...`).

Release-сборка в AIMP ничего не копирует. Деплой выполняется только
сгенерированной конфигурацией `Deploy <plugin>`, скриптом или явным
`/p:AimpDeployOnBuild=true`.

### Тестовый плагин AimpTestRunner

`AimpTestRunner` — библиотека-плагин, поэтому запускать нужно не её саму, а
`AIMP.exe` с уже развёрнутым плагином. Для неё генерируются те же две
конфигурации:

- **Deploy AimpTestRunner** — собирает проект и копирует весь output (NUnit
  Engine, addins, ресурсы) в `<AIMP>\Plugins\AimpTestRunner`; шим — как
  `AimpTestRunner.dll`, managed-сборка — как `AimpTestRunner_plugin.dll`;
- **AimpTestRunner (AIMP)** — выполняет деплой и запускает `AIMP.exe` с
  mixed-mode debugging.

Разрядность для деплоя берётся из `AimpPlatform`, поэтому активная
конфигурация решения (`Debug | x86/x64`) на запуск не влияет. Если
конфигурации не появились — перезагрузи решение
(`File → Reload All from Disk`).

Плагин запускает тесты по событию `EventLoaded`, пишет отчёт в
`integration.tests.xml` и завершает AIMP, после чего удаляет профиль
пользователя для следующего «чистого» запуска. Если AIMP уже запущен, файлы
плагина заняты и копирование упадёт — закрой плеер перед запуском. Если AIMP
один раз не загрузил плагин, он может держать устаревшую запись в
`Profile\AIMP.ini` (`[Plugins]` / `[Plugins.CachedInfo]`); удали строки с
именем плагина или включи его в Настройки → Плагины.

### Версия AIMP и неподдерживаемые API

Версия плеера доступна через `IAimpPlayer.Version`:

```csharp
if (player.Version.IsAtLeast(6, 0))
{
    // AIMP 6.0+
}
```

`AimpVersion` содержит `Major`, `Minor`, `Build`, `IsKnown` и `IsAtLeast`.
Версия берётся из `IAIMPServiceVersionInfo`, а если сервис недоступен — из
file version `AIMP.exe`.

Обёртки API, появившихся в AIMP 6.0, проверяют версию и бросают
`AimpUnsupportedApiException` с именем API, требуемой и текущей версией.
Если версию определить не удалось, проверка не блокирует вызов. Сейчас
защищены:

- `IAimpServiceLog`, `IAimpServiceFileURI3`;
- создание `IAimpConfigFile`, `IAimpObjectList2`;
- `IAimpPlaylist.GetProperties()` (`IAimpPlaylistProperties`);
- `IAimpServiceOptionsDialog.FrameShow(IAimpConfig, ...)`;
- `formatterId`-перегрузки `IAimpServiceFileInfoFormatter` /
  `IAimpServiceFileInfoFormatterUtils`;
- регистрация `IAimpExtensionExternalCatalog` и
  `IAimpExtensionPlaylistShuffler`.

Результат:

```
bin/out/x86/
  sdk/                             SDK-набор для ручной установки
    aimp_dotnet.dll                нативный шим
    AIMP.Host.dll                  стабильный загрузчик (AppDomain)
    AIMP.SDK.dll                   хостинг + публичный SDK
  plugins/
    dotnet_musiclibrary/           готовый демо-плагин
    dotnet_simple/                 готовый пример плагина
    dotnet_demo/                   порт старого dotnet_demo
    dotnet_ExtendDialogWindow/     опции + внешний диалог настроек
  aimp_managed/                    старый ready-to-deploy MusicLibrary demo
bin/out/x64/                       то же для 64-битного плеера
```

Оба демо-плагина собираются и раскладываются в `plugins/<имя>` с собственной
копией шима, `AIMP.Host.dll` и `AIMP.SDK.dll`. Внешних зависимостей у SDK нет.

CI (`.gitea/workflows/release.yml`) дополнительно собирает два архива:

| Архив | Содержимое |
|---|---|
| `aimp.sdk-<version>.zip` | `x86/`, `x64/` (только `AIMP.Host.dll`, `AIMP.SDK.dll`, `aimp_dotnet.dll`) и `README.md` в корне |
| `aimp.demo-plugins-<version>.zip` | `x86/<plugin>/...`, `x64/<plugin>/...` — готовые демо-плагины |

## Установка в AIMP

AIMP 5 ищет плагины по схеме `Plugins\<имя>\<имя>.dll`, то есть **нативный шим
должен называться так же, как папка плагина**. Внутри папки лежат сам шим,
стабильный загрузчик `AIMP.Host.dll`, SDK и managed-плагин:

```
<AIMP>\Plugins\dotnet_musiclibrary\dotnet_musiclibrary.dll   <- шим
<AIMP>\Plugins\dotnet_musiclibrary\AIMP.Host.dll             <- загрузчик
<AIMP>\Plugins\dotnet_musiclibrary\AIMP.SDK.dll              <- SDK
<AIMP>\Plugins\dotnet_musiclibrary\dotnet_musiclibrary_plugin.dll
```

Можно скопировать `plugins\dotnet_musiclibrary` или `plugins\dotnet_simple`
из `bin/out/<platform>` в `<AIMP>\Plugins`.

или:

```powershell
pwsh -File .\deploy.ps1 -AimpDirectory "F:\code\aimp\AIMP5.40.2655" -Platform x86
```

## Логирование

Внешняя библиотека логирования SDK не нужна.

### Файл SDK

SDK ведёт тот же файл, что шим и хост: `logs\YYYYMMDD.log` в папке плагина.
Он создаётся и в Release-сборке.

| Префикс | Кто пишет |
|---|---|
| `[shim]` | нативный шим |
| `[host ...]` | `AIMP.Host.dll` |
| `[sdk] [INF]` / `[sdk] [ERR]` | SDK и перехваченные ошибки плагина |

Строки SDK содержат уровень и id потока:

```
2026-11-20 00:47:31.574 [sdk] [INF] [T1] Bootstrap: host directory '...'
2026-11-20 00:48:08.454 [sdk] [ERR] [T1] Unhandled exception | System.TypeInitializationException: ...
```

В начале файла пишется баннер: имя, версия и автор плагина из `[AimpPlugin]`,
версии `AIMP.SDK.dll`, `AIMP.Host.dll` и нативного шима, битность, CLR, версия
ОС, имя машины, PID и путь к сборке плагина.

### Перехват ошибок

- `NativePluginBridge` перехватывает исключения `Initialize`, `Finalize` и
  `SystemNotification` и пишет их в лог с уровнем `[ERR]`;
- `Safe.Run` делает то же для COM-колбэков расширений;
- в AppDomain плагина подписаны `AppDomain.UnhandledException` и
  `TaskScheduler.UnobservedTaskException`;
- если зарегистрированный логгер сам бросает исключение, SDK пишет его в свой
  файл, поэтому ошибка не теряется.

`TypeInitializationException` из статических конструкторов SDK тоже попадает
в лог — именно так был найден битый IID `IAIMPServiceActionManager`.

### Свой логгер

Публичный контракт — `AIMP.SDK.Logger.IAimpLogger`. SDK всегда пишет свои
сообщения и ошибки в файл, а зарегистрированный логгер получает их
дополнительно:

- `AimpPlugin.InitializeLogger()` — вернуть реализацию;
- `AimpLogging.Register(...)` — зарегистрировать вручную;
- `AimpLogging.Logger` — текущий логгер (или `InternalLogger` по умолчанию).

```csharp
using AIMP.SDK.Logger;

public class Plugin : AimpPlugin
{
    // Вариант 1: SDK создаёт логгер через этот метод.
    public override IAimpLogger InitializeLogger()
    {
        return new MyLogger();
    }
}

public class AnotherPlugin : AimpPlugin
{
    // Вариант 2: зарегистрировать логгер вручную.
    public override void Initialize()
    {
        AimpLogging.Register(new MyLogger());
        AimpLogging.Logger.Information("Custom event: {Value}", 42);
    }
}
```

`InternalLogger` (по умолчанию) дублирует сообщения в
`System.Diagnostics.Debug` — они видны в отладчике и DebugView. В Release
вывод в отладчик отключается, но файл `logs\YYYYMMDD.log` пишется всегда.

### Несколько плагинов одновременно

Один DLL отдаёт AIMP ровно один `IAIMPPlugin`, поэтому **каждый плагин — своя
папка и своя копия шима**. Схема имён осталась прежней:

```
Plugins\MyPluginA\
  MyPluginA.dll          <- копия aimp_dotnet.dll, переименованная под папку
  AIMP.Host.dll          <- стабильный загрузчик (одна и та же версия)
  AIMP.SDK.dll           <- SDK версии, с которой собран плагин A
  MyPluginA_plugin.dll   <- managed-плагин A

Plugins\MyPluginB\
  MyPluginB.dll          <- ещё одна копия aimp_dotnet.dll
  AIMP.Host.dll          <- та же версия, что и в A
  AIMP.SDK.dll           <- SDK версии, с которой собран плагин B
  MyPluginB_plugin.dll   <- другой managed-плагин
```

Правила:

1. Имя папки = имя AIMP-плагина = имя нативного шима (`MyPluginA.dll`).
2. Managed-плагин не должен называться так же, как шим. Суффикс `_plugin`
   рекомендуется (как в старом SDK): `MyPluginA_plugin.dll`.
3. `AIMP.Host.dll` — **одна и та же сборка** во всех папках. Это маленький
   загрузчик без зависимостей; именно он создаёт `AppDomain` и загружает
   `AIMP.SDK.dll` из папки плагина.
4. `AIMP.SDK.dll` может отличаться в каждой папке: плагин A может быть собран
   против SDK 1.x, плагин B — против SDK 2.x. Каждый `AppDomain` загружает свою
   копию SDK.
5. Несколько managed-плагинов в одной папке не поддерживаются: `PluginHost`
   выбирает один `AimpPlugin` (при наличии `*_plugin.dll` — его в первую очередь).

Каждый плагин запускается в **отдельном `AppDomain`**, поэтому статические
состояния (`AimpRuntime`, логи, зарегистрированные расширения) у плагинов не
пересекаются. Проверено загрузкой в одном процессе двух плагинов с
`AIMP.SDK.dll` версий **1.0.0.0** и **2.0.0.0**.

## Как написать свой плагин

1. Создать class library под `net48`, сослаться на `AIMP.SDK.dll`.
2. Унаследовать `AIMP.AimpPlugin` и пометить класс атрибутом `[AimpPlugin]`:

```csharp
using AIMP;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;

[AimpPlugin("My plugin", "me", "1.0.0.0",
    AimpPluginType = AimpPluginType.Addons,
    FullDescription = "Minimal managed plugin.")]
public sealed class MyPlugin : AimpPlugin
{
    public override void Initialize()
    {
        Logger.Information("profile: " + Player.Core.GetPath(AimpCorePathType.Profile));
    }

    public override void Dispose() { }
}
```

3. Положить DLL в ту же папку, что `AIMP.SDK.dll`.

## API

Публичный контракт — это интерфейсы из `AIMP.SDK.*` (`SDK/`):

```csharp
public abstract class AimpPlugin
{
    public IAimpPlayer Player { get; }
    public IAimpLogger Logger { get; }
    public virtual IAimpLogger InitializeLogger(); // регистрация логгера
    public abstract void Initialize();
    public abstract void Dispose();
}

public interface IAimpCore
{
    string GetPath(AimpCorePathType path);
    AimpActionResult<T> CreateAimpObject<T>() where T : class;
    AimpActionResult RegisterExtension(IAimpExtension extension);
    AimpActionResult UnregisterExtension(IAimpExtension extension);
}

public interface IAimpPlayer : IDisposable
{
    IAimpCore Core { get; }
    IAimpServicePlaylistManager ServicePlaylistManager { get; }
    IAimpServiceMusicLibrary ServiceMusicLibrary { get; }
    // ... остальные сервисы
}
```

Сервисы и объекты возвращают те же типы, что и в `v1`, поэтому существующий код
плагинов продолжает работать. `AimpActionResult`/`AimpActionResult<T>` несут
`ResultType` и результат вызова.

## Расширения (CCW обратно в AIMP)

Плагин реализует managed-контракт из `AIMP.SDK.*.Extensions` и регистрирует его:

```csharp
public sealed class MyStorage : IAimpExtensionDataStorage, IAimpDataProvider2 { ... }
public sealed class MyFileSystem : IAimpExtensionFileSystem { ... }

Player.Core.RegisterExtension(myStorage);
Player.Core.RegisterExtension(myFileSystem);
```

`AimpExtensionRegistrar` сам подбирает нужный сервис-хост AIMP
(`IAIMPServiceMusicLibrary`, `IAIMPServiceFileSystems`, `IAIMPServiceFileInfo`,
`IAIMPServicePlaylistManager`) и отдаёт ему CCW-мост, у которого vtable совпадает
с заголовком SDK. Один managed-объект может реализовывать несколько контрактов
(например storage + `IAimpDataProvider` + команды) — AIMP получает их через
`QueryInterface`.

Поддерживаются: `IAimpExtensionDataStorage` (+ `IAimpDataProvider`, `IAimpDataProvider2`,
все `IAimpDataStorageCommand*`), `IAimpExtensionFileSystem` (+ команды файловой
системы), `IAimpExtensionFileInfoProvider`, `IAimpExtensionPlaylistPreimageFactory`
(+ `IAimpPlaylistPreimage`, `IAimpPlaylistPreimageDataProvider`) и
`IAimpExtensionPlaylistManagerListener`.

Полный пример — `dotnet_musiclibrary`: демо-библиотека с grouping tree, фильтрами,
пресетами и командами, файловая система `myschema://`, file info provider, preimage
factory с data provider, listener плейлистов и два пункта контекстного меню.

## Ограничения прототипа

* .NET Framework 4.8 (CLR v4). Переход на .NET 8 потребует `hostfxr`/`ComWrappers`
  и переписывания изоляции плагинов (сейчас AIMP-плагин = одна папка = один плагин).
* Один managed-плагин на папку. Несколько плагинов одновременно поддерживаются
  отдельными папками и копиями шима; каждый плагин живёт в своём `AppDomain`
  (см. «Несколько плагинов одновременно»).
* Ошибки в vtable-объявлениях — это не исключение, а падение нативного кода.
  Для масштабирования объявления надо генерировать из `AIMPSDK/AIMP400/*.h`.
