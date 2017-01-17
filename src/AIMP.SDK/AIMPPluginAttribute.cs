using System;

namespace AIMP.SDK
{
    public enum AimpPluginType
    {
        Addons = 0x1,
        Decoders = 0x2,
        Visuals = 0x4,
        DSP = 0x8
    }

    /// <summary>
    /// This attribute should mark plugin class
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    [Serializable]
    public class AimpPluginAttribute: Attribute
    {
        /// <summary>
        /// Mark AIMP plugin class
        /// </summary>
        /// <param name="name">Plugin's name</param>
        /// <param name="author">Plugin's author</param>
        /// <param name="version">Plugin's version (format: x.xx)</param>
        public AimpPluginAttribute(string name, string author, string version)
        {
            Name = name;
            Author = author;
            Version = version;
        }

        /// <summary>
        /// Plugin's author
        /// </summary>
        public string Author { get;  set; }

        /// <summary>
        /// Plugin's name
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Short description
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// Defined if plugin should run in separate AppDomain.
        /// </summary>
        public bool RequireAppDomain { get; set; }

        ///<summary>
        /// Version of plugin (format: x.xx)
        ///</summary>
        public string Version { get; set; }

        /// <summary>
        /// Gets or sets the full description.
        /// </summary>
        public string FullDescription { get; set; }

        /// <summary>
        /// Gets or sets the type of the aimp plugin.
        /// </summary>
        public AimpPluginType AimpPluginType { get; set; }

        public bool IsExternalSettingsDialog { get; set; }
    }
}
