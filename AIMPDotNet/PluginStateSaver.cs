namespace AIMP.SDK
{
    using System.Linq;

    using Services.ConfigurationManager;

    /// <summary>
    /// Plugins state saver class.
    /// </summary>
    internal sealed class PluginStateSaver
    {
        public const string ConfigSectionName = "AimpDotNet";

        private readonly IAimpConfigurationManager _configurationManager;

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.Object"/> class.
        /// </summary>
        public PluginStateSaver(IAimpConfigurationManager configurationManager)
        {
            _configurationManager = configurationManager;
        }

        /// <summary>
        /// Saves the specified settings.
        /// </summary>
        /// <param name="settings">The settings.</param>
        public void Save(PluginSettings settings)
        {
            _configurationManager.Delete(ConfigSectionName);

            foreach (PluginInformation plugin in settings.PluginsCollection.Where(plugin => plugin.IsLoaded))
            {
                _configurationManager.SetValueAsInt32(GetKey(GetPluginNameID(plugin)), 1);
            }

            _configurationManager.SetValueAsInt32(GetKey("Settings\\DebugMode"), settings.IsDebugMode ? 1 : 0);
        }

        /// <summary>
        /// Loads the specified settings.
        /// </summary>
        /// <param name="settings">The settings.</param>
        public void Load(PluginSettings settings)
        {
            foreach (var plugin in settings.PluginsCollection)
            {
                if (_configurationManager.GetValueAsInt32(GetKey(GetPluginNameID(plugin))) == 1)
                {
                    plugin.Load();
                }
                else
                {
                    plugin.Unload();
                }
            }
        }

        /// <summary>
        /// Gets the key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns></returns>
        private string GetKey(string key)
        {
            return string.Format("{0}\\{1}", ConfigSectionName, key);
        }

        /// <summary>
        /// Gets the plugin name identifier.
        /// </summary>
        /// <param name="pluginInformation">The pluginInformation.</param>
        /// <returns></returns>
        private string GetPluginNameID(PluginInformation pluginInformation)
        {
            string asm = pluginInformation.PluginAssemblyName;
            int prtId = asm.IndexOf(',');
            if (prtId > 0)
                asm = asm.Substring(0, prtId);
            string clsNm = pluginInformation.PluginClassName.Replace('.', '_');
            return asm + "_" + clsNm;
        }
    }
}