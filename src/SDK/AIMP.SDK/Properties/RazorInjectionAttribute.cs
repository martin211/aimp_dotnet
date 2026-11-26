using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class RazorInjectionAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Assembly, AllowMultiple = true)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class RazorInjectionAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="RazorInjectionAttribute" /> class.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <param name="fieldName">Name of the field.</param>
        public RazorInjectionAttribute(string type, string fieldName)
        {
            Type = type;
            FieldName = fieldName;
        }

        /// <summary>
        /// Gets the type.
        /// </summary>
        /// <value>The type.</value>
        public string Type { get; }

        /// <summary>
        /// Gets the name of the field.
        /// </summary>
        /// <value>The name of the field.</value>
        public string FieldName { get; }
    }
}