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
using System.IO;
using System.Linq;
using System.Reflection;

namespace AIMP.SDK
{
    public static class CustomAssemblyResolver
    {
        private static string curPath;
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

        private static Assembly CurrentDomainAssemblyResolve(object sender, ResolveEventArgs args)
        {
            string projectDir = Path.GetDirectoryName(curPath);

            var i = args.Name.IndexOf(',');
            if (i != -1)
            {
                string shortAssemblyName = args.Name.Substring(0, args.Name.IndexOf(','));
                string fileName = Path.Combine(projectDir, shortAssemblyName + ".dll");
                if (File.Exists(fileName))
                {
                    Assembly result = Assembly.LoadFrom(fileName);
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