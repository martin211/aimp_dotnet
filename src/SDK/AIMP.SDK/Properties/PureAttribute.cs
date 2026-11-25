using System;
using System.Diagnostics;

namespace AIMP.Properties
{
    /// <summary>
    /// Indicates that a method does not make any observable state changes.
    /// The same as <c>System.Diagnostics.Contracts.PureAttribute</c>
    /// Implements the <see cref="System.Attribute" />
    /// </summary>
    /// <seealso cref="System.Attribute" />
    /// <example>
    ///   <code>
    /// [Pure] private int Multiply(int x, int y) { return x * y; }
    /// public void Foo() {
    /// const int a = 2, b = 2;
    /// Multiply(a, b); // Waring: Return value of pure method is not used
    /// }
    /// </code>
    /// </example>
    [AttributeUsage(AttributeTargets.Method)]
    [Conditional("JETBRAINS_ANNOTATIONS")]
    public sealed class PureAttribute : Attribute
    {
    }
}