namespace AIMP.SDK
{
    /// <summary>
    /// DotNet plugin settings.
    /// </summary>
    public class AimpDotNetPlugin
    {
        public PluginInformation PluginInformation { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is debug mode.
        /// </summary>
        public bool IsDebugMode { get; set; }

        /// <summary>
        /// Gets or sets the plugins collection.
        /// </summary>
        public DotNetPluginInfo AimpPlugin { get; set; }

        /// <summary>
        /// Plugin's author
        /// </summary>
        public string Author { get; set; }

        /// <summary>
        /// Plugin's name
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Short description
        /// </summary>
        public string Description { get; set; }

        ///<summary>
        /// Version of plugin (format: x.xx)
        ///</summary>
        public string Version { get; set; }

        public string FullDescription { get; set; }
    }
}