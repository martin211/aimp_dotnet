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
            List<PluginShortInfoForLoad> resPlugInfolst = new List<PluginShortInfoForLoad>();
            DirectoryInfo dir = new DirectoryInfo(path);
            Type pluginDeriveType = typeof(IAimpPlugin);
            Type attribForPlugin = typeof(AimpPluginAttribute);

            if (dir.Exists)
            {
                foreach (var di in dir.GetDirectories())
                {
                    foreach (var fileInfo in ScanFiles(di, 0))
                    {
                        try
                        {
                            var curAsmbl = Assembly.LoadFrom(fileInfo.FullName);
                            if (curAsmbl.FullName != Assembly.GetExecutingAssembly().FullName && !curAsmbl.FullName.Equals("aimp_dotnet"))
                            {
                                foreach (var plgType in curAsmbl.GetTypes()
                                            .Where(
                                                o =>
                                                    pluginDeriveType.IsAssignableFrom(o) &&
                                                    o.GetCustomAttributes(attribForPlugin, false).Length == 1)
                                                    )
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
                        }
                        catch
                        {
                            System.Diagnostics.Debugger.Break();
                            // ignored
                        }
                    }
                }
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
