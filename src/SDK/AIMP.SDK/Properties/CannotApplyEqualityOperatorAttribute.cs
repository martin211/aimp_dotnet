using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates that the value of the marked type (or its derivatives)
    /// cannot be compared using '==' or '!=' operators and <c>Equals()</c>
    /// should be used instead. However, using '==' or '!=' for comparison
    /// with <c>null</c> is always permitted.
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    /// <example>
    ///   <code>
    /// [CannotApplyEqualityOperator]
    /// class NoEquality { }
    /// class UsesNoEquality {
    /// public void Test() {
    /// var ca1 = new NoEquality();
    /// var ca2 = new NoEquality();
    /// if (ca1 != null) { // OK
    /// bool condition = ca1 == ca2; // Warning
    /// }
    /// }
    /// }
    /// </code>
    /// </example>
    [AttributeUsage(
        AttributeTargets.Interface | AttributeTargets.Class | AttributeTargets.Struct)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class CannotApplyEqualityOperatorAttribute : Attribute
    {
    }
}