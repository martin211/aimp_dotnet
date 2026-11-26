using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class RazorImportNamespaceAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Assembly, AllowMultiple = true)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class RazorImportNamespaceAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="RazorImportNamespaceAttribute" /> class.
        /// </summary>
        /// <param name="name">The name.</param>
        public RazorImportNamespaceAttribute(string name)
        {
            Name = name;
        }

        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <value>The name.</value>
        public string Name { get; }
    }
}