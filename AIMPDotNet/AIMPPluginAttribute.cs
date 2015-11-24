using System;

namespace AIMP.SDK
{
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

        public string FullDescription { get; set; }
    }
}
