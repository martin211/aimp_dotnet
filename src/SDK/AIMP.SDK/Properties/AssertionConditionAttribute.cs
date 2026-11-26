using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates the condition parameter of the assertion method. The method itself should be
    /// marked by <see cref="AssertionMethodAttribute" /> attribute. The mandatory argument of
    /// the attribute is the assertion type.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Parameter)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AssertionConditionAttribute : Attribute
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AssertionConditionAttribute" /> class.
        /// </summary>
        /// <param name="conditionType">Type of the condition.</param>
        public AssertionConditionAttribute(AssertionConditionType conditionType)
        {
            ConditionType = conditionType;
        }

        /// <summary>
        /// Gets the type of the condition.
        /// </summary>
        /// <value>The type of the condition.</value>
        public AssertionConditionType ConditionType { get; }
    }
}