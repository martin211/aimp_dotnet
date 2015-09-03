using System;
using System.IO;
using System.Linq;
using AIMP.SDK.Interfaces;
using AIMP.SDK.Services.Player;

namespace AIMP.SDK
{
    /// <summary>
    /// 
    /// </summary>
    /// <param name="sender">The sender.</param>
    public delegate void PluginLoadUnloadEvent(PluginInformation sender);

    /// <summary>
    /// Information about plugin.
    /// </summary>
    public class PluginInformation : IDisposable
    {
        private static int _curUniquePluginId = 100;

        private static int GetNewUniqPluginId()
        {   
            return System.Threading.Interlocked.Increment(ref _curUniquePluginId);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="PluginInformation" /> class.
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
        /// Initializes a new instance of the <see cref="PluginInformation"/> class.
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

        private readonly FileInfo _inPathToAssembly;


        /// <summary>
        /// Gets the name of the assembly file.
        /// </summary>
        public string AssemblyFileName
        {
            get
            {
                return _inPathToAssembly.Name;
            }
        }

        /// <summary>
        /// Gets the name of the plugin assembly.
        /// </summary>
        public string PluginAssemblyName
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the name of the plugin class.
        /// </summary>
        public string PluginClassName
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets a value indicating whether this plugin has setting dialog.
        /// </summary>
        public bool HasSettingDialog
        {
            get
            {
                return IsLoaded && LoadedPlugin.HasSettingDialog;
            }
        }


        /// <summary>
        /// Gets a value indicating whether this plugin is loaded.
        /// </summary>
        public bool IsLoaded
        {
            get
            {
                return LoadedPlugin != null;
            }
        }

        /// <summary>
        /// Gets the plugin information.
        /// </summary>
        public AimpPluginAttribute PluginInfo
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the loaded plugin.
        /// </summary>
        public AimpPluginBase LoadedPlugin
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the plugin application domain information (null = current doamin).
        /// </summary>
        public AppDomain PluginAppDomainInfo
        {
            get;
            private set;
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
        /// <returns></returns>
        public bool Load()
        {
            if (!IsLoaded)
            {
                if (PluginInfo.RequireAppDomain) // need domain
                { 
                    try
                    {
                        AppDomainSetup dmnSetup = new AppDomainSetup
                        {
                            ApplicationName = PluginInfo.Name, 
                            ApplicationBase = _inPathToAssembly.DirectoryName
                        };

                        PluginAppDomainInfo = AppDomain.CreateDomain(PluginInfo.Name + "_domain" + Guid.NewGuid().ToString().GetHashCode().ToString("x"), null, dmnSetup);
                        LoadedPlugin = (AimpPluginBase)PluginAppDomainInfo.CreateInstanceFromAndUnwrap(_inPathToAssembly.FullName, PluginClassName);
                    }
                    catch (Exception ex)
                    {
                        if (PluginAppDomainInfo != null)
                        {
                            AppDomain.Unload(PluginAppDomainInfo);
                            PluginAppDomainInfo = null;
                        }

                        LoadedPlugin = null;
#if DEBUG
                        System.Windows.Forms.MessageBox.Show(ex.Message);
#endif
                    }
                }
                else
                {  
                    System.Reflection.Assembly asm = null;
                    try
                    { 
                        asm = AppDomain.CurrentDomain.GetAssemblies().FirstOrDefault(o => o.FullName == PluginAssemblyName);
                    }
                    catch (Exception ex)
                    {
#if DEBUG
                        System.Windows.Forms.MessageBox.Show(ex.Message);
#endif
                    }

                    if (asm == null)
                    {
                        try
                        {  
                            asm = System.Reflection.Assembly.LoadFrom(_inPathToAssembly.FullName);
                        }
                        catch (Exception ex)
                        {
#if DEBUG
                            System.Windows.Forms.MessageBox.Show(ex.Message);
#endif
                        }
                    }

                    if (asm != null)
                    {
                        try
                        {  
                            Type instType = asm.GetType(PluginClassName);
                            LoadedPlugin = (AimpPluginBase)Activator.CreateInstance(instType);
                        }
                        catch (Exception ex)
                        {
#if DEBUG
                            System.Windows.Forms.MessageBox.Show(ex.Message);
#endif
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
                    catch
                    {
                        System.Diagnostics.Debugger.Break();
                        Unload();
                    }
                }
            }
            return IsLoaded;
        }

        /// <summary>
        /// Unloads this plugin.
        /// </summary>
        public bool Unload()
        {
            if (IsLoaded)
            {
                try
                {
                    if (PluginUnloadEvent != null)
                        PluginUnloadEvent(this);

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
#if DEBUG
                    System.Windows.Forms.MessageBox.Show(ex.Message);
#endif
                }
            }
            return !IsLoaded;
        }

        /// <summary>
        /// Shows the setting dialog.
        /// </summary>
        /// <param name="parentWindow">The parent window.</param>
        public void ShowSettingDialog(System.Windows.Forms.IWin32Window parentWindow)
        {
            if (IsLoaded)
            {
                LoadedPlugin.ShowSettingDialog(parentWindow);
            }
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
    }
}
