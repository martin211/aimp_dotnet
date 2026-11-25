using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class RazorHelperCommonAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class RazorHelperCommonAttribute : Attribute
    {
    }
}