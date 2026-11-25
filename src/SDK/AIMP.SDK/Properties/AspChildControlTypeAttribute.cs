using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Class AspChildControlTypeAttribute. This class cannot be inherited.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AspChildControlTypeAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AspChildControlTypeAttribute" /> class.
        /// </summary>
        /// <param name="tagName">Name of the tag.</param>
        /// <param name="controlType">Type of the control.</param>
        public AspChildControlTypeAttribute(string tagName, Type controlType)
        {
            TagName = tagName;
            ControlType = controlType;
        }

        /// <summary>
        /// Gets the name of the tag.
        /// </summary>
        /// <value>The name of the tag.</value>
        public string TagName { get; }

        /// <summary>
        /// Gets the type of the control.
        /// </summary>
        /// <value>The type of the control.</value>
        public Type ControlType { get; }
    }
}