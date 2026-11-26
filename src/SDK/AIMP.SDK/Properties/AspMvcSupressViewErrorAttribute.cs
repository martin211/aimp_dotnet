using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// ASP.NET MVC attribute. Allows disabling inspections for MVC views within a class or a method
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspMvcSupressViewErrorAttribute : Attribute
    {
    }
}