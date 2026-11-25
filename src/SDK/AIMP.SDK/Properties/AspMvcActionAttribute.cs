using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// ASP.NET MVC attribute. If applied to a parameter, indicates that the parameter
    /// is an MVC action. If applied to a method, the MVC action name is calculated
    /// implicitly from the context. Use this attribute for custom wrappers similar to
    /// <c>System.Web.Mvc.Html.ChildActionExtensions.RenderAction(HtmlHelper, String)</c>
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Parameter | AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspMvcActionAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AspMvcActionAttribute" /> class.
        /// </summary>
        public AspMvcActionAttribute()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AspMvcActionAttribute" /> class.
        /// </summary>
        /// <param name="anonymousProperty">The anonymous property.</param>
        public AspMvcActionAttribute(string anonymousProperty)
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