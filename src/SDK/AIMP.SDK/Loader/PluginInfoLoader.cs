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
using System.Reflection;
using System.Windows.Forms;
using AIMP.SDK;

namespace AIMP.Loader
{
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
                AimpInternalLogger.Instance.LogMessage(e.ToString());
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
