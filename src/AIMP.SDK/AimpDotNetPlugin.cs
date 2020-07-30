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

namespace AIMP.SDK
{
    /// <summary>
    /// DotNet plugin information.
    /// </summary>
    public class AimpDotNetPlugin
    {
        /// <summary>
        /// Gets or sets the plugin information.
        /// </summary>
        /// <value>The plugin information.</value>
        public PluginInformation PluginInformation { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is debug mode.
        /// </summary>
        /// <value><c>true</c> if this instance is debug mode; otherwise, <c>false</c>.</value>
        public bool IsDebugMode { get; set; }

        /// <summary>
        /// Gets or sets the plugins collection.
        /// </summary>
        /// <value>The aimp plugin.</value>
        public DotNetPluginInfo AimpPlugin { get; set; }

        /// <summary>
        /// Plugin's author
        /// </summary>
        /// <value>The author.</value>
        public string Author { get; set; }

        /// <summary>
        /// Plugin's name
        /// </summary>
        /// <value>The name.</value>
        public string Name { get; set; }

        /// <summary>
        /// Short description
        /// </summary>
        /// <value>The description.</value>
        public string Description { get; set; }

        /// <summary>
        /// Version of plugin (format: x.xx)
        /// </summary>
        /// <value>The version.</value>
        public string Version { get; set; }

        /// <summary>
        /// Gets or sets the full description.
        /// </summary>
        /// <value>The full description.</value>
        public string FullDescription { get; set; }
    }
}