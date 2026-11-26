using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// ASP.NET MVC attribute. Indicates that a parameter is an MVC area.
    /// Use this attribute for custom wrappers similar to
    /// <c>System.Web.Mvc.Html.ChildActionExtensions.RenderAction(HtmlHelper, String)</c>
    /// Implements the <see cref="PathReferenceAttribute" />
    /// </summary>
    /// <seealso cref="PathReferenceAttribute" />
    [AttributeUsage(AttributeTargets.Parameter)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspMvcAreaAttribute : PathReferenceAttribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AspMvcAreaAttribute" /> class.
        /// </summary>
        public AspMvcAreaAttribute()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AspMvcAreaAttribute" /> class.
        /// </summary>
        /// <param name="anonymousProperty">The anonymous property.</param>
        public AspMvcAreaAttribute(string anonymousProperty)
        {
            AnonymousProperty = anonymousProperty;
        }

        /// <summary>
        /// Gets the anonymous property.
        /// </summary>
        /// <value>The anonymous property.</value>
        public string AnonymousProperty { get; }
    }
}