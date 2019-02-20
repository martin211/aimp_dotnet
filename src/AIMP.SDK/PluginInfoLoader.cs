// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace AIMP.SDK
{
    [Serializable]
    public struct PluginShortInfoForLoad : IEquatable<PluginShortInfoForLoad>
    {
        /// <summary>
        /// Gets or sets the name of the assembly file.
        /// </summary>
        public string AssemblyFileName { get; set; }

        /// <summary>
        /// Gets or sets the full name of the assembly.
        /// </summary>
        public string AssemblyFullName { get; set; }

        /// <summary>
        /// Gets or sets the name of the class.
        /// </summary>
        public string ClassName { get; set; }

        /// <summary>
        /// Gets or sets the plugin loc information.
        /// </summary>
        public AimpPluginAttribute PluginLocInfo { get; set; }

        public bool Equals(PluginShortInfoForLoad other)
        {
            return AssemblyFileName == other.AssemblyFileName &&
                   AssemblyFullName == other.AssemblyFileName &&
                   ClassName == other.ClassName &&
                   PluginLocInfo.Equals(other.PluginLocInfo);
        }
    }

    public abstract class PluginLoadingStrategy : MarshalByRefObject
    {
        public abstract PluginShortInfoForLoad Load(string path);
    }

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
        private Assembly AssemblyResolveOverride(object sender, ResolveEventArgs args)
        {
            string dllFileName = new AssemblyName(args.Name).Name + ".dll";

            string assemblyPath = Directory
                .EnumerateFiles(_probePath, dllFileName, SearchOption.TopDirectoryOnly)
                .FirstOrDefault();

            return assemblyPath != null ? Assembly.LoadFrom(assemblyPath) : null;
        }

        private IEnumerable<FileInfo> ScanFiles(DirectoryInfo di, int depth)
        {
            foreach (FileInfo fileInfo in di.GetFiles("*.dll"))
                yield return fileInfo;

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

        public override PluginShortInfoForLoad Load(string path)
        {
            DirectoryInfo dir = new DirectoryInfo(path);
            PluginShortInfoForLoad resPlugInfolst = new PluginShortInfoForLoad();
            Type pluginDeriveType = typeof(IAimpPlugin);
            Type attribForPlugin = typeof(AimpPluginAttribute);
            //var extensionType = typeof(IAimpExtension);
            Type externalSettingsDialog = typeof(IAimpExternalSettingsDialog);

            try
            {
                AppDomain.CurrentDomain.AssemblyResolve += AssemblyResolveOverride;

                foreach (FileInfo fileInfo in ScanFiles(dir, 0))
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
                                                              && o.GetCustomAttributes(attribForPlugin, false).Length == 1);

                        if (plgType != null)
                        {
                            var curAttr = (AimpPluginAttribute)plgType.GetCustomAttributes(attribForPlugin, false)[0];
                            System.Diagnostics.Debug.WriteLine("Load plugin: " + curAsmbl.FullName);
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

    public static class PluginInfoLoader
    {
        public static Type LoadStrategyType = typeof(AssemblyScanPluginLoadStrategy);

        public static AimpDotNetPlugin LoadPlugin(string path)
        {
            AppDomain loadDomain = null;

            try
            {
                AppDomainSetup domainSet = new AppDomainSetup {ApplicationBase = path};
                loadDomain = AppDomain.CreateDomain(
                    "PluginLoadDomain" + new Guid().ToString().GetHashCode().ToString("x"), null, domainSet);

                PluginLoadingStrategy strat =
                    (PluginLoadingStrategy) loadDomain.CreateInstanceAndUnwrap(Assembly.GetExecutingAssembly().FullName,
                        LoadStrategyType.FullName);

                var plugin = strat.Load(path);
                if (plugin.PluginLocInfo == null)
                {
                    return null;
                }

                return new AimpDotNetPlugin
                {
                    PluginInformation = new PluginInformation(plugin.AssemblyFileName, plugin.AssemblyFullName,
                        plugin.ClassName, plugin.PluginLocInfo),
                    Author = plugin.PluginLocInfo.Author,
                    Description = plugin.PluginLocInfo.Description,
                    FullDescription = plugin.PluginLocInfo.FullDescription,
                    Name = plugin.PluginLocInfo.Name,
                    Version = plugin.PluginLocInfo.Version
                };
            }
#if DEBUG
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }
#endif
            finally
            {
                if (loadDomain != null)
                    AppDomain.Unload(loadDomain);
            }

            return null;
        }
    }
}