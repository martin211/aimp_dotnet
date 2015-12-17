using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// This attribute should mark plugin class
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, AllowMultiple=false)]
    [Serializable]
    public class AIMPPluginAttribute: Attribute
    {
        /// <summary>
        /// Mark AIMP plugin class
        /// </summary>
        /// <param name="name">Plugin's name</param>
        /// <param name="author">Plugin's author</param>
        /// <param name="version">Plugin's version (format: x.xx)</param>
        public AIMPPluginAttribute(string name, string author, int version)
        {
            Name = name;
            Author = author;
            Version = version;
            RequireAppDomain = false;
            Description = "";
        }
        /// <summary>
        /// Plugin's author
        /// </summary>
        public string Author
        {
            get; 
            set;
        }
        /// <summary>
        /// Plugin's name
        /// </summary>
        public string Name
        {
            get;
            set;
        }
        /// <summary>
        /// Short description
        /// </summary>
        public string Description
        {
            get;
            set;
        }
        /// <summary>
        /// Defined if plugin should run in separate AppDomain.
        /// </summary>
        public bool RequireAppDomain
        {
            get;
            set;
        }
        /// <summary>
        /// Version of plugin (format: x.xx)
        /// </summary>
        public int Version
        {
            get;
            set;
        }
    }
}
