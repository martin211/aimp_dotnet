using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class AspTypePropertyAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Property)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspTypePropertyAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AspTypePropertyAttribute" /> class.
        /// </summary>
        /// <param name="createConstructorReferences">if set to <c>true</c> [create constructor references].</param>
        public AspTypePropertyAttribute(bool createConstructorReferences)
        {
            CreateConstructorReferences = createConstructorReferences;
        }

        /// <summary>
        /// Gets a value indicating whether [create constructor references].
        /// </summary>
        /// <value><c>true</c> if [create constructor references]; otherwise, <c>false</c>.</value>
        public bool CreateConstructorReferences { get; }
    }
}