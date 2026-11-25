using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates that the marked method is assertion method, i.e. it halts control flow if
    /// one of the conditions is satisfied. To set the condition, mark one of the parameters with
    /// <see cref="AssertionConditionAttribute" /> attribute
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    [AttributeUsage(AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class AssertionMethodAttribute : Attribute
    {
    }
}