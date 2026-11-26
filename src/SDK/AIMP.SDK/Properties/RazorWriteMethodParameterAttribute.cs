using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class RazorWriteMethodParameterAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Parameter)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class RazorWriteMethodParameterAttribute : Attribute
    {
    }
}