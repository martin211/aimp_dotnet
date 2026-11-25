using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class AspMethodPropertyAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Property)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspMethodPropertyAttribute : Attribute
    {
    }
}