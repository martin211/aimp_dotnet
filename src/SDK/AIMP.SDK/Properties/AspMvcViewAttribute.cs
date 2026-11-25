using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// ASP.NET MVC attribute. If applied to a parameter, indicates that the parameter
    /// is an MVC view. If applied to a method, the MVC view name is calculated implicitly
    /// from the context. Use this attribute for custom wrappers similar to
    /// <c>System.Web.Mvc.Controller.View(Object)</c>
    /// Implements the <see cref="PathReferenceAttribute" />
    /// </summary>
    /// <seealso cref="PathReferenceAttribute" />
    [AttributeUsage(AttributeTargets.Parameter | AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspMvcViewAttribute : PathReferenceAttribute
    {
    }
}