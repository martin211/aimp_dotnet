// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
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
using AIMP.SDK;

namespace AIMP.Loader;

/// <summary>
/// Class AssemblyScanPluginLoadStrategy.
/// Implements the <see cref="PluginLoadingStrategy" />
/// </summary>
/// <seealso cref="PluginLoadingStrategy" />
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
        _probePath = path;
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
                    if (curAsmbl.FullName == Assembly.GetExecutingAssembly().FullName || curAsmbl.FullName.Equals("aimp_dotnet"))
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
                catch (Exception e)
                {
                    AimpInternalLogger.Instance.LogMessage(e.ToString());
#if DEBUG
                    MessageBox.Show(e.Message);
#endif
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
