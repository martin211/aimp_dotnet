// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;

namespace AIMP.Loader;

/// <summary>
/// Struct PluginShortInfoForLoad
/// Implements the <see cref="System.IEquatable{AIMP.SDK.PluginShortInfoForLoad}" />
/// </summary>
/// <seealso cref="System.IEquatable{AIMP.SDK.PluginShortInfoForLoad}" />
[Serializable]
public struct PluginShortInfoForLoad : IEquatable<PluginShortInfoForLoad>
{
    /// <summary>
    /// Gets or sets the name of the assembly file.
    /// </summary>
    /// <value>The name of the assembly file.</value>
    public string AssemblyFileName { get; set; }

    /// <summary>
    /// Gets or sets the full name of the assembly.
    /// </summary>
    /// <value>The full name of the assembly.</value>
    public string AssemblyFullName { get; set; }

    /// <summary>
    /// Gets or sets the name of the class.
    /// </summary>
    /// <value>The name of the class.</value>
    public string ClassName { get; set; }

    /// <summary>
    /// Gets or sets the plugin loc information.
    /// </summary>
    /// <value>The plugin loc information.</value>
    public AimpPluginAttribute PluginLocInfo { get; set; }

    /// <summary>
    /// Indicates whether the current object is equal to another object of the same type.
    /// </summary>
    /// <param name="other">An object to compare with this object.</param>
    /// <returns>true if the current object is equal to the <paramref name="other" /> parameter; otherwise, false.</returns>
    public bool Equals(PluginShortInfoForLoad other)
    {
        return AssemblyFileName == other.AssemblyFileName &&
               AssemblyFullName == other.AssemblyFileName &&
               ClassName == other.ClassName &&
               PluginLocInfo.Equals(other.PluginLocInfo);
    }
}
