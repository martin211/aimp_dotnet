using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class AspMvcAreaMasterLocationFormatAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Assembly, AllowMultiple = true)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspMvcAreaMasterLocationFormatAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AspMvcAreaMasterLocationFormatAttribute" /> class.
        /// </summary>
        /// <param name="format">The format.</param>
        public AspMvcAreaMasterLocationFormatAttribute(string format)
        {
            Format = format;
        }

        /// <summary>
        /// Gets the format.
        /// </summary>
        /// <value>The format.</value>
        public string Format { get; }
    }
}