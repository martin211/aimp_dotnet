using System;
using System.IO;
using System.Linq;
using System.Reflection;

namespace AIMP.SDK
{
    internal static class CustomAssemblyResolver
    {
        private static string curPath;
        private static bool isInited;
 
        /// <summary>
        /// Initializes the specified path.
        /// </summary>
        /// <param name="path">The path.</param>
        public static void Initialize(string path)
        {
            curPath = path +"\\";
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
            string shortAssemblyName = args.Name.Substring(0, args.Name.IndexOf(','));
            string fileName = Path.Combine(projectDir, shortAssemblyName + ".dll");
            if (File.Exists(fileName))
            {
                Assembly result = Assembly.LoadFrom(fileName);
                return result;
            }
            
            var assemblyPath = Directory.EnumerateFiles(projectDir, shortAssemblyName + ".dll", SearchOption.AllDirectories).FirstOrDefault();
            if (assemblyPath != null)
            {
                return Assembly.LoadFrom(assemblyPath);
            }

            return Assembly.GetExecutingAssembly().FullName == args.Name ? Assembly.GetExecutingAssembly() : null;
        }
    }
}
