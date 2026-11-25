using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using AIMP.Internal;
using AIMP.SDK;

namespace AIMP.Loader
{
    /// <summary>
    /// Discovers and instantiates the v1-style managed plugin
    /// (<see cref="AimpPlugin"/> + <see cref="AimpPluginAttribute"/>) that lives
    /// next to the host.
    /// </summary>
    internal static class PluginHost
    {
        /// <summary>
        /// Loaded plugin together with the descriptor from its attribute.
        /// </summary>
        internal sealed class LoadedPlugin
        {
            public AimpPlugin Plugin;
            public AimpPluginAttribute Attribute;
        }

        public static LoadedPlugin Load(string hostDirectory)
        {
            var candidates = new List<Type>();

            // The v1 convention: the AIMP facing DLL is named after the plugin
            // and the managed assembly has the "_plugin" suffix. Prefer that
            // file when the folder contains more than one managed assembly.
            foreach (var file in Directory.GetFiles(hostDirectory, "*.dll")
                         .OrderBy(path => path.EndsWith("_plugin.dll", StringComparison.OrdinalIgnoreCase)
                             ? 0
                             : 1))
            {
                if (!IsManagedAssembly(file))
                {
                    continue;
                }

                foreach (var type in GetLoadableTypes(file))
                {
                    if (type.IsAbstract || type.IsInterface)
                    {
                        continue;
                    }

                    if (!typeof(AimpPlugin).IsAssignableFrom(type))
                    {
                        continue;
                    }

                    if (type.GetConstructor(Type.EmptyTypes) == null)
                    {
                        AimpLog.Write($"Skip '{type.FullName}': no public parameterless constructor.");
                        continue;
                    }

                    candidates.Add(type);
                }
            }

            if (candidates.Count == 0)
            {
                throw new InvalidOperationException($"No AimpPlugin implementation was found in '{hostDirectory}'.");
            }

            // Prefer a class decorated with [AimpPlugin]; that is the v1 contract.
            Type selected = null;
            AimpPluginAttribute attribute = null;

            foreach (var candidate in candidates)
            {
                var descriptor = (AimpPluginAttribute)Attribute.GetCustomAttribute(
                    candidate,
                    typeof(AimpPluginAttribute),
                    false);

                if (descriptor == null)
                {
                    continue;
                }

                if (selected != null)
                {
                    AimpLog.Write($"More than one [AimpPlugin] class was found, using '{selected.FullName}'.");
                    break;
                }

                selected = candidate;
                attribute = descriptor;
            }

            if (selected == null)
            {
                selected = candidates[0];
                AimpLog.Write($"'{selected.FullName}' has no [AimpPlugin] attribute; using default metadata.");
            }

            if (candidates.Count > 1)
            {
                AimpLog.Write($"More than one AimpPlugin was found, using '{selected.FullName}'.");
            }

            var plugin = (AimpPlugin)Activator.CreateInstance(selected);
            AimpLog.Write($"Loaded managed plugin '{selected.FullName}' from '{selected.Assembly.Location}'.");

            return new LoadedPlugin
            {
                Plugin = plugin,
                Attribute = attribute ?? new AimpPluginAttribute(selected.Name, string.Empty, string.Empty)
            };
        }

        private static bool IsManagedAssembly(string assemblyPath)
        {
            try
            {
                var name = AssemblyName.GetAssemblyName(assemblyPath);

                // The SDK itself never contains a plugin.
                if (string.Equals(name.Name, "AIMP.SDK", StringComparison.OrdinalIgnoreCase))
                {
                    return false;
                }

                return true;
            }
            catch (Exception)
            {
                // Native DLL (for example the shim itself) - not our business.
                return false;
            }
        }

        private static IEnumerable<Type> GetLoadableTypes(string assemblyPath)
        {
            Assembly assembly;

            try
            {
                assembly = Assembly.LoadFrom(assemblyPath);
            }
            catch (Exception exception)
            {
                AimpLog.Write($"Skip '{assemblyPath}': {exception.Message}");
                return Array.Empty<Type>();
            }

            try
            {
                return assembly.GetTypes();
            }
            catch (ReflectionTypeLoadException exception)
            {
                return [.. exception.Types.Where(type => type != null)];
            }
        }
    }
}