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
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

namespace AIMP.SDK
{
    /// <summary>
    /// Struct PluginShortInfoForLoad
    /// Implements the <see cref="System.IEquatable{AIMP.SDK.PluginShortInfoForLoad}" />
    /// </summary>
    /// <seealso cref="System.IEquatable{AIMP.SDK.PluginShortInfoForLoad}" />
    [Serializable]
    public struct PluginShortInfoForLoad : IEquatable<PluginShortInfoForLoad>
    {
        /// <summary>
        /// Gets or sets the name of the assembly file.
        /// </summary>
        /// <value>The name of the assembly file.</value>
        public string AssemblyFileName { get; set; }

        /// <summary>
        /// Gets or sets the full name of the assembly.
        /// </summary>
        /// <value>The full name of the assembly.</value>
        public string AssemblyFullName { get; set; }

        /// <summary>
        /// Gets or sets the name of the class.
        /// </summary>
        /// <value>The name of the class.</value>
        public string ClassName { get; set; }

        /// <summary>
        /// Gets or sets the plugin loc information.
        /// </summary>
        /// <value>The plugin loc information.</value>
        public AimpPluginAttribute PluginLocInfo { get; set; }

        /// <summary>
        /// Indicates whether the current object is equal to another object of the same type.
        /// </summary>
        /// <param name="other">An object to compare with this object.</param>
        /// <returns>true if the current object is equal to the <paramref name="other" /> parameter; otherwise, false.</returns>
        public bool Equals(PluginShortInfoForLoad other)
        {
            return AssemblyFileName == other.AssemblyFileName &&
                   AssemblyFullName == other.AssemblyFileName &&
                   ClassName == other.ClassName &&
                   PluginLocInfo.Equals(other.PluginLocInfo);
        }
    }

    /// <summary>
    /// Class PluginLoadingStrategy.
    /// Implements the <see cref="System.MarshalByRefObject" />
    /// </summary>
    /// <seealso cref="System.MarshalByRefObject" />
    public abstract class PluginLoadingStrategy : MarshalByRefObject
    {
        /// <summary>
        /// Loads the specified path.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>PluginShortInfoForLoad.</returns>
        public abstract PluginShortInfoForLoad Load(string path);
    }

    /// <summary>
    /// Class AssemblyScanPluginLoadStrategy.
    /// Implements the <see cref="AIMP.SDK.PluginLoadingStrategy" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.PluginLoadingStrategy" />
    public class AssemblyScanPluginLoadStrategy : PluginLoadingStrategy
    {
        /// <summary>
        /// Path to the plugin folder where additional dependencies will be searched for.
        /// </summary>
        private string _probePath;

        /// <summary>
        /// In case one of plugin dependencies is required during its load and cannot be found in GAC,
        /// this event handler gets executes by the .NET Framework.
        /// Then we try to look in the plugin's folder for the requeseted dll and load it manually.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="args">The <see cref="ResolveEventArgs" /> instance containing the event data.</param>
        /// <returns>Assembly.</returns>
        private Assembly AssemblyResolveOverride(object sender, ResolveEventArgs args)
        {
            var dllFileName = new AssemblyName(args.Name).Name + ".dll";

            var assemblyPath = Directory
                .EnumerateFiles(_probePath, dllFileName, SearchOption.TopDirectoryOnly)
                .FirstOrDefault();

            return assemblyPath != null ? Assembly.LoadFrom(assemblyPath) : null;
        }

        /// <summary>
        /// Scans the files.
        /// </summary>
        /// <param name="di">The di.</param>
        /// <param name="depth">The depth.</param>
        /// <returns>IEnumerable&lt;FileInfo&gt;.</returns>
        private IEnumerable<FileInfo> ScanFiles(DirectoryInfo di, int depth)
        {
            foreach (var fileInfo in di.GetFiles("*.dll"))
            {
                yield return fileInfo;
            }

            if (depth > 0)
            {
                foreach (var directoryInfo in di.GetDirectories())
                {
                    foreach (var fileInfo in ScanFiles(directoryInfo, depth - 1))
                    {
                        yield return fileInfo;
                    }
                }
            }
        }

        /// <summary>
        /// Loads the specified path.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>PluginShortInfoForLoad.</returns>
        public override PluginShortInfoForLoad Load(string path)
        {
            var dir = new DirectoryInfo(path);
            var resPlugInfolst = new PluginShortInfoForLoad();
            var pluginDeriveType = typeof(IAimpPlugin);
            var attribForPlugin = typeof(AimpPluginAttribute);
            //var extensionType = typeof(IAimpExtension);
            var externalSettingsDialog = typeof(IAimpExternalSettingsDialog);

            try
            {
                AppDomain.CurrentDomain.AssemblyResolve += AssemblyResolveOverride;

                foreach (var fileInfo in ScanFiles(dir, 0))
                {
                    try
                    {
                        var curAsmbl = Assembly.LoadFrom(fileInfo.FullName);
                        if (curAsmbl.FullName == Assembly.GetExecutingAssembly().FullName
                            || curAsmbl.FullName.Equals("aimp_dotnet"))
                        {
                            continue;
                        }

                        var assemblyTypes = curAsmbl.GetTypes();

                        var plgType = assemblyTypes.FirstOrDefault(o => pluginDeriveType.IsAssignableFrom(o)
                                                                        && o.GetCustomAttributes(attribForPlugin, false)
                                                                            .Length == 1);

                        if (plgType != null)
                        {
                            var curAttr = (AimpPluginAttribute) plgType.GetCustomAttributes(attribForPlugin, false)[0];
                            Debug.WriteLine("Load plugin: " + curAsmbl.FullName);
                            curAttr.IsExternalSettingsDialog = externalSettingsDialog.IsAssignableFrom(plgType);

                            resPlugInfolst = new PluginShortInfoForLoad
                            {
                                AssemblyFileName = fileInfo.FullName,
                                AssemblyFullName = curAsmbl.FullName,
                                ClassName = plgType.FullName,
                                PluginLocInfo = curAttr
                            };
                        }
                    }
                    catch
                    {
                        // ignored
                    }
                }
            }
            finally
            {
                AppDomain.CurrentDomain.AssemblyResolve -= AssemblyResolveOverride;
            }

            return resPlugInfolst;
        }
    }

    /// <summary>
    /// Class PluginInfoLoader.
    /// </summary>
    public static class PluginInfoLoader
    {
        /// <summary>
        /// The load strategy type
        /// </summary>
        public static Type LoadStrategyType = typeof(AssemblyScanPluginLoadStrategy);

        /// <summary>
        /// Loads the plugin.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <returns>AimpDotNetPlugin.</returns>
        public static AimpDotNetPlugin LoadPlugin(string path)
        {
            AppDomain loadDomain = null;

            try
            {
                var domainSet = new AppDomainSetup
                {
                    ApplicationBase = path
                };

                loadDomain = AppDomain.CreateDomain("PluginLoadDomain" + new Guid().ToString().GetHashCode().ToString("x"), null, domainSet);

                var strat = (PluginLoadingStrategy) loadDomain.CreateInstanceAndUnwrap(Assembly.GetExecutingAssembly().FullName, LoadStrategyType.FullName);

                var plugin = strat.Load(path);
                if (plugin.PluginLocInfo == null)
                {
                    return null;
                }

                return new AimpDotNetPlugin
                {
                    PluginInformation = new PluginInformation(plugin.AssemblyFileName, plugin.AssemblyFullName, plugin.ClassName, plugin.PluginLocInfo),
                    Author = plugin.PluginLocInfo.Author,
                    Description = plugin.PluginLocInfo.Description,
                    FullDescription = plugin.PluginLocInfo.FullDescription,
                    Name = plugin.PluginLocInfo.Name,
                    Version = plugin.PluginLocInfo.Version
                };
            }

            catch (Exception e)
            {
#if DEBUG
                MessageBox.Show(e.Message);
#endif
            }
            finally
            {
                if (loadDomain != null)
                {
                    AppDomain.Unload(loadDomain);
                }
            }

            return null;
        }
    }
}
