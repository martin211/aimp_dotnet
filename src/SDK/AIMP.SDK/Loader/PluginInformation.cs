// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Threading;
using AIMP.SDK;

namespace AIMP.Loader
{
    /// <summary>
    /// Delegate PluginLoadUnloadEvent
    /// </summary>
    /// <param name="sender">The sender.</param>
    public delegate void PluginLoadUnloadEvent(PluginInformation sender);

    /// <summary>
    /// Information about plugin.
    /// Implements the <see cref="System.IDisposable" />
    /// </summary>
    /// <seealso cref="System.IDisposable" />
    [Serializable]
    public class PluginInformation : IDisposable
    {
        /// <summary>
        /// The current unique plugin identifier
        /// </summary>
        private static int _curUniquePluginId = 100;

        /// <summary>
        /// The in path to assembly
        /// </summary>
        private readonly FileInfo _inPathToAssembly;

        /// <summary>
        /// Initializes a new instance of the <see cref="AIMP.Loader.PluginInformation" /> class.
        /// </summary>
        /// <param name="assemblyPath">The assembly path.</param>
        /// <param name="assemblyName">Name of the assembly.</param>
        /// <param name="className">Name of the class.</param>
        /// <param name="pluginAttribute">The plugin attribute.</param>
        public PluginInformation(FileInfo assemblyPath, string assemblyName, string className, AimpPluginAttribute pluginAttribute)
        {
            _inPathToAssembly = assemblyPath;
            PluginClassName = className;
            PluginAssemblyName = assemblyName;
            PluginInfo = pluginAttribute;
            LoadedPlugin = null;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AIMP.Loader.PluginInformation" /> class.
        /// </summary>
        /// <param name="assemblyPath">The assembly path.</param>
        /// <param name="assemblyName">Name of the assembly.</param>
        /// <param name="className">Name of the class.</param>
        /// <param name="pluginAttribute">The plugin attribute.</param>
        public PluginInformation(string assemblyPath, string assemblyName, string className, AimpPluginAttribute pluginAttribute)
        {
            _inPathToAssembly = new FileInfo(assemblyPath);
            PluginClassName = className;
            PluginAssemblyName = assemblyName;
            PluginInfo = pluginAttribute;
            LoadedPlugin = null;
        }

        /// <summary>
        /// Gets the name of the assembly file.
        /// </summary>
        /// <value>The name of the assembly file.</value>
        public string AssemblyFileName => _inPathToAssembly.Name;

        /// <summary>
        /// Gets the name of the plugin assembly.
        /// </summary>
        /// <value>The name of the plugin assembly.</value>
        public string PluginAssemblyName { get; private set; }

        /// <summary>
        /// Gets the name of the plugin class.
        /// </summary>
        /// <value>The name of the plugin class.</value>
        public string PluginClassName { get; private set; }

        /// <summary>
        /// Gets a value indicating whether this plugin is loaded.
        /// </summary>
        /// <value><c>true</c> if this instance is loaded; otherwise, <c>false</c>.</value>
        public bool IsLoaded => LoadedPlugin != null;

        /// <summary>
        /// Gets the plugin information.
        /// </summary>
        /// <value>The plugin information.</value>
        public AimpPluginAttribute PluginInfo { get; private set; }

        /// <summary>
        /// Gets the loaded plugin.
        /// </summary>
        /// <value>The loaded plugin.</value>
        public AimpPlugin LoadedPlugin { get; private set; }

        /// <summary>
        /// Gets the plugin application domain information (null = current doamin).
        /// </summary>
        /// <value>The plugin application domain information.</value>
        public AppDomain PluginAppDomainInfo { get; private set; }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (IsLoaded)
            {
                Unload();
            }
        }

        /// <summary>
        /// Gets the new uniq plugin identifier.
        /// </summary>
        /// <returns>System.Int32.</returns>
        private static int GetNewUniqPluginId()
        {
            return Interlocked.Increment(ref _curUniquePluginId);
        }

        /// <summary>
        /// Occurs when [plugin load event].
        /// </summary>
        public event PluginLoadUnloadEvent PluginLoadEvent;

        /// <summary>
        /// Occurs when [plugin unload event].
        /// </summary>
        public event PluginLoadUnloadEvent PluginUnloadEvent;

        /// <summary>
        /// Loads this plugin.
        /// </summary>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        public bool Load()
        {
            if (!IsLoaded)
            {
                if (PluginInfo.RequireAppDomain) // need domain
                {
                    try
                    {
                        var dmnSetup = new AppDomainSetup
                        {
                            ApplicationName = PluginInfo.Name,
                            ApplicationBase = _inPathToAssembly.DirectoryName
                        };

                        PluginAppDomainInfo = AppDomain.CreateDomain(
                            PluginInfo.Name + "_domain" + Guid.NewGuid().ToString().GetHashCode().ToString("x"),
                            null, dmnSetup);

                        LoadedPlugin = (AimpPlugin) PluginAppDomainInfo.CreateInstanceFromAndUnwrap(_inPathToAssembly.FullName, PluginClassName);

                        PluginAppDomainInfo.AssemblyResolve += (sender, args) =>
                        {
                            var projectDir = Path.GetDirectoryName(_inPathToAssembly.DirectoryName);

                            var i = args.Name.IndexOf(',');
                            if (i != -1)
                            {
                                var shortAssemblyName = args.Name.Substring(0, args.Name.IndexOf(','));
                                var fileName = Path.Combine(projectDir, shortAssemblyName + ".dll");
                                
                                if (File.Exists(fileName))
                                {
                                    var result = Assembly.LoadFrom(fileName);
                                    return result;
                                }

                                var assemblyPath = Directory
                                    .EnumerateFiles(projectDir, shortAssemblyName + ".dll", SearchOption.AllDirectories)
                                    .FirstOrDefault();

                                if (assemblyPath != null)
                                {
                                    return Assembly.LoadFrom(assemblyPath);
                                }
                            }

                            return Assembly.GetExecutingAssembly().FullName == args.Name
                                ? Assembly.GetExecutingAssembly()
                                : null;
                        };
                    }
                    catch (Exception ex)
                    {
                        if (PluginAppDomainInfo != null)
                        {
                            AppDomain.Unload(PluginAppDomainInfo);
                            PluginAppDomainInfo = null;
                        }

                        LoadedPlugin = null;
                    }
                }
                else
                {
                    Assembly asm = null;
                    try
                    {
                        asm = AppDomain.CurrentDomain.GetAssemblies()
                            .FirstOrDefault(o => o.FullName == PluginAssemblyName);
                    }
                    catch (Exception ex)
                    {
                    }

                    if (asm == null)
                    {
                        try
                        {
                            asm = Assembly.LoadFrom(_inPathToAssembly.FullName);
                        }
                        catch (Exception ex)
                        {
                        }
                    }

                    if (asm != null)
                    {
                        try
                        {
                            var instType = asm.GetType(PluginClassName);
                            LoadedPlugin = (AimpPlugin) Activator.CreateInstance(instType);
                        }
                        catch (Exception ex)
                        {
                        }
                    }
                }

                if (IsLoaded)
                {
                    if (LoadedPlugin != null)
                    {
                        LoadedPlugin.PluginId = GetNewUniqPluginId();
                    }
                }

                if (IsLoaded && PluginLoadEvent != null)
                {
                    try
                    {
                        PluginLoadEvent(this);
                    }
                    catch (Exception e)
                    {
                        Debugger.Break();
                        Unload();
                    }
                }
            }

            return IsLoaded;
        }

        /// <summary>
        /// Unloads this plugin.
        /// </summary>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        public bool Unload()
        {
            if (IsLoaded)
            {
                try
                {
                    if (PluginUnloadEvent != null)
                    {
                        PluginUnloadEvent(this);
                    }

                    LoadedPlugin.OnDispose();

                    if (PluginAppDomainInfo != null)
                    {
                        AppDomain.Unload(PluginAppDomainInfo);
                    }

                    PluginAppDomainInfo = null;
                    LoadedPlugin = null;

                    GC.Collect();
                }
                catch (Exception ex)
                {
                }
            }

            return !IsLoaded;
        }

        /// <summary>
        /// Shows the setting dialog.
        /// </summary>
        /// <param name="parentWindow">The parent window.</param>
        public void ShowSettingDialog(IntPtr parentWindow)
        {
            var plugin = LoadedPlugin as IAimpExternalSettingsDialog;
            plugin?.Show(parentWindow);
        }

        /// <summary>
        /// Initializes the specified plugin.
        /// </summary>
        /// <param name="player">The player.</param>
        public void Initialize(IAimpPlayer player)
        {
            if (IsLoaded)
            {
                LoadedPlugin.OnInitialize(player, LoadedPlugin.PluginId);
            }
        }
    }
}
