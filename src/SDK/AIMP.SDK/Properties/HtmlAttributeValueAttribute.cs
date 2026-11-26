using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class HtmlAttributeValueAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(
        AttributeTargets.Parameter | AttributeTargets.Field | AttributeTargets.Property)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class HtmlAttributeValueAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="HtmlAttributeValueAttribute" /> class.
        /// </summary>
        /// <param name="name">The name.</param>
        public HtmlAttributeValueAttribute([NotNull] string name)
        {
            Name = name;
        }

        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <value>The name.</value>
        [NotNull]
        public string Name { get; }
    }
}