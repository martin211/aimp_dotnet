using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Prevents the Member Reordering feature from tossing members of the marked class.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    /// <remarks>The attribute must be mentioned in your member reordering patterns.</remarks>
    [AttributeUsage(AttributeTargets.All)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class NoReorder : Attribute
    {
    }
}