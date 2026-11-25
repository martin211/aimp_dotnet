using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class AspRequiredAttributeAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspRequiredAttributeAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AspRequiredAttributeAttribute" /> class.
        /// </summary>
        /// <param name="attribute">The attribute.</param>
        public AspRequiredAttributeAttribute([NotNull] string attribute)
        {
            Attribute = attribute;
        }

        /// <summary>
        /// Gets the attribute.
        /// </summary>
        /// <value>The attribute.</value>
        public string Attribute { get; }
    }
}