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

namespace AIMP.SDK
{
    /// <summary>
    ///     Enum AimpPluginType
    /// </summary>
    public enum AimpPluginType
    {
        /// <summary>
        ///     The addons
        /// </summary>
        Addons = 0x1,

        /// <summary>
        ///     The decoders
        /// </summary>
        Decoders = 0x2,

        /// <summary>
        ///     The visuals
        /// </summary>
        Visuals = 0x4,

        /// <summary>
        ///     The DSP
        /// </summary>
        DSP = 0x8
    }

    /// <summary>
    ///     This attribute should mark plugin class
    ///     Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Class)]
    [Serializable]
    public sealed class AimpPluginAttribute : Attribute
    {
        /// <summary>
        ///     Mark AIMP plugin class
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
        ///     Plugin's author
        /// </summary>
        /// <value>The author.</value>
        public string Author { get; set; }

        /// <summary>
        ///     Plugin's name
        /// </summary>
        /// <value>The name.</value>
        public string Name { get; set; }

        /// <summary>
        ///     Short description
        /// </summary>
        /// <value>The description.</value>
        public string Description { get; set; }

        /// <summary>
        ///     Defined if plugin should run in separate AppDomain.
        /// </summary>
        /// <value><c>true</c> if [require application domain]; otherwise, <c>false</c>.</value>
        public bool RequireAppDomain { get; set; }

        /// <summary>
        ///     Version of plugin (format: x.xx)
        /// </summary>
        /// <value>The version.</value>
        public string Version { get; set; }

        /// <summary>
        ///     Gets or sets the full description.
        /// </summary>
        /// <value>The full description.</value>
        public string FullDescription { get; set; }

        /// <summary>
        ///     Gets or sets the type of the aimp plugin.
        /// </summary>
        /// <value>The type of the aimp plugin.</value>
        public AimpPluginType AimpPluginType { get; set; }

        /// <summary>
        ///     Gets or sets a value indicating whether this plugin is support external settings dialog.
        /// </summary>
        /// <value><c>true</c> if this instance is external settings dialog; otherwise, <c>false</c>.</value>
        public bool IsExternalSettingsDialog { get; set; }
    }
}