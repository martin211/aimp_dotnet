//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.IO;
using System.Linq;
using System.Reflection;

namespace AIMP.Loader
{
    /// <summary>
    /// Class CustomAssemblyResolver.
    /// </summary>
    public static class CustomAssemblyResolver
    {
        /// <summary>
        /// The current path
        /// </summary>
        private static string curPath;

        /// <summary>
        /// The is inited
        /// </summary>
        private static bool isInited;

        /// <summary>
        /// Initializes the specified path.
        /// </summary>
        /// <param name="path">The path.</param>
        public static void Initialize(string path)
        {
            curPath = path + "\\";
            if (!isInited)
            {
                AppDomain.CurrentDomain.AssemblyResolve += CurrentDomainAssemblyResolve;
                isInited = true;
            }
        }

        /// <summary>
        /// Deinitializes this instance.
        /// </summary>
        public static void Deinitialize()
        {
            AppDomain.CurrentDomain.AssemblyResolve -= CurrentDomainAssemblyResolve;
            isInited = false;
        }

        /// <summary>
        /// Currents the domain assembly resolve.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="args">The <see cref="ResolveEventArgs" /> instance containing the event data.</param>
        /// <returns>Assembly.</returns>
        public static Assembly CurrentDomainAssemblyResolve(object sender, ResolveEventArgs args)
        {
            System.Diagnostics.Debugger.Launch();
            var projectDir = Path.GetDirectoryName(curPath);

            var i = args.Name.IndexOf(',');
            if (i != -1)
            {
                var shortAssemblyName = args.Name.Substring(0, args.Name.IndexOf(','));

                if (shortAssemblyName == "aimp_dotnet")
                {
                    var file = Path.Combine(projectDir, Path.GetFileName(projectDir) + ".dll");

                    if (File.Exists(file))
                    {
                        return Assembly.LoadFrom(file);
                    }
                }


                var fileName = Path.Combine(projectDir, shortAssemblyName + ".dll");
                if (File.Exists(fileName))
                {
                    var result = Assembly.LoadFrom(fileName);
                    return result;
                }

                var assemblyPath = Directory.EnumerateFiles(projectDir, shortAssemblyName + ".dll",
                        SearchOption.AllDirectories)
                    .FirstOrDefault();
                if (assemblyPath != null)
                {
                    return Assembly.LoadFrom(assemblyPath);
                }
            }

            return Assembly.GetExecutingAssembly().FullName == args.Name ? Assembly.GetExecutingAssembly() : null;
        }
    }
}
