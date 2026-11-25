using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates that collection or enumerable value can contain null elements
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(
        AttributeTargets.Method | AttributeTargets.Parameter | AttributeTargets.Property |
        AttributeTargets.Delegate | AttributeTargets.Field)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class ItemCanBeNullAttribute : Attribute
    {
    }
}