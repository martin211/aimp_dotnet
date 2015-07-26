using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace AIMP.SDK
{
    [Serializable]
    internal struct PluginShortInfoForLoad
    {
        public string AssemblyFileName;
        public string AssemblyFullName;
        public string ClassName;
        public AimpPluginAttribute PluginLocInfo;
    }

    interface IPluginLoadingStrategy
    {
        PluginShortInfoForLoad[] Load(string path);
    }

    internal abstract class PluginLoadingStrategy : MarshalByRefObject//, IPluginLoadingStrategy
    {
        public abstract PluginShortInfoForLoad[] Load(string path);
    }

    internal class AssemblyScanPluginLoadStrategy : PluginLoadingStrategy
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

        public override PluginShortInfoForLoad[] Load(string path)
        {
            DirectoryInfo dir = new DirectoryInfo(path);
            if (!dir.Exists)
            {
                return new PluginShortInfoForLoad[0];
            }
            
            List<PluginShortInfoForLoad> resPlugInfolst = new List<PluginShortInfoForLoad>();
            Type pluginDeriveType = typeof(IAimpPlugin);
            Type attribForPlugin = typeof(AimpPluginAttribute);
            try
            {
                AppDomain.CurrentDomain.AssemblyResolve += AssemblyResolveOverride;

                foreach (DirectoryInfo di in dir.GetDirectories())
                {
                    _probePath = di.FullName;

                    foreach (FileInfo fileInfo in ScanFiles(di, 0))
                    {
                        try
                        {
                            var curAsmbl = Assembly.LoadFrom(fileInfo.FullName);
                            if (curAsmbl.FullName == Assembly.GetExecutingAssembly().FullName
                                || curAsmbl.FullName.Equals("aimp_dotnet"))
                            {
                                continue;
                            }

                            foreach (var plgType in curAsmbl
                                .GetTypes()
                                .Where(o => pluginDeriveType.IsAssignableFrom(o)
                                    && o.GetCustomAttributes(attribForPlugin, false).Length == 1))
                            {
                                var curAttr = (AimpPluginAttribute)plgType.GetCustomAttributes(attribForPlugin, false)[0];
                                System.Diagnostics.Debug.WriteLine("Load plugin: " + curAsmbl.FullName);
                                resPlugInfolst.Add(new PluginShortInfoForLoad
                                {
                                    AssemblyFileName = fileInfo.FullName,
                                    AssemblyFullName = curAsmbl.FullName,
                                    ClassName = plgType.FullName,
                                    PluginLocInfo = curAttr
                                });
                            }
                        }
                        catch
                        {
                            System.Diagnostics.Debugger.Break();
                            // ignored
                        }
                    }
                }
            }
            finally
            {
                AppDomain.CurrentDomain.AssemblyResolve -= AssemblyResolveOverride;
            }

            return resPlugInfolst.ToArray();
        }
    }
    
    internal static class PluginInfoLoader
    {
        public static Type LoadStrategyType = typeof(AssemblyScanPluginLoadStrategy);

        public static void LoadPlugins(string path, PluginInfoCollection plgCol)
        {
            AppDomain loadDomain = null;

            try
            {
                AppDomainSetup domainSet = new AppDomainSetup { ApplicationBase = path };
                loadDomain = AppDomain.CreateDomain("PluginLoadDomain" + new Guid().ToString().GetHashCode().ToString("x"), null, domainSet);

                PluginLoadingStrategy strat = (PluginLoadingStrategy)loadDomain.CreateInstanceAndUnwrap(Assembly.GetExecutingAssembly().FullName, LoadStrategyType.FullName);

                PluginShortInfoForLoad[] res = strat.Load(path);
                foreach (PluginShortInfoForLoad cInf in res)
                {
                    plgCol.Add(new PluginInformation(cInf.AssemblyFileName, cInf.AssemblyFullName, cInf.ClassName, cInf.PluginLocInfo));
                }
            }
#if DEBUG
            catch(Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }
#endif
            finally
            {
                if (loadDomain != null)
                    AppDomain.Unload(loadDomain);
            }
        }

        public static PluginInfoCollection LoadPlugins(string path)
        {
            PluginInfoCollection plgCol = new PluginInfoCollection();
            LoadPlugins(path, plgCol);
            return plgCol;
        }


    }
}
