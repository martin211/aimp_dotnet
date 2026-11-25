using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// For a parameter that is expected to be one of the limited set of values.
    /// Specify fields of which type should be used as values for this parameter.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Parameter | AttributeTargets.Property | AttributeTargets.Field)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class ValueProviderAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ValueProviderAttribute" /> class.
        /// </summary>
        /// <param name="name">The name.</param>
        public ValueProviderAttribute(string name)
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