using System;
using System.Linq.Expressions;
using NUnit.Framework;

namespace Aimp.TestRunner.TestFramework;

/// <summary>
/// Thin wrapper over NUnit assertions used by the integration tests.
///
/// It keeps the historical v1 call signatures, but delegates all checks to
/// <see cref="NUnit.Framework.Assert"/>, so NUnit produces the actual/expected
/// diff and the messages are not lost.
/// </summary>
public static class AimpAssert
{
    public static void AreEqual(object expected, object actual, string message = null)
    {
        NUnit.Framework.Assert.That(actual, Is.EqualTo(expected), BuildMessage(message));
    }

    public static void AreEqual(object expected, object actual, string fieldName, string message)
    {
        NUnit.Framework.Assert.That(actual, Is.EqualTo(expected), BuildMessage(fieldName, message));
    }

    public static void AreEqual<TResult>(object expected, Expression<Func<TResult>> actual, string message = null)
    {
        var value = Evaluate(actual);
        NUnit.Framework.Assert.That(value, Is.EqualTo(expected),
            BuildMessage(GetMemberName(actual), message));
    }

    public static void AreNotEqual(object expected, object actual, string message = null)
    {
        NUnit.Framework.Assert.That(actual, Is.Not.EqualTo(expected), BuildMessage(message));
    }

    public static void AreNotEqual(object expected, object actual, string fieldName, string message)
    {
        NUnit.Framework.Assert.That(actual, Is.Not.EqualTo(expected), BuildMessage(fieldName, message));
    }

    public static void AreNotEqual<TResult>(object expected, Expression<Func<TResult>> actual, string message = null)
    {
        var value = Evaluate(actual);
        NUnit.Framework.Assert.That(value, Is.Not.EqualTo(expected),
            BuildMessage(GetMemberName(actual), message));
    }

    public static void NotNull(object actual, string message = null)
    {
        NUnit.Framework.Assert.That(actual, Is.Not.Null, BuildMessage(message));
    }

    public static void NotNull(object actual, string fieldName, string message)
    {
        NUnit.Framework.Assert.That(actual, Is.Not.Null, BuildMessage(fieldName, message));
    }

    public static void NotNull<TResult>(Expression<Func<TResult>> actual, string message = null)
    {
        var value = Evaluate(actual);
        NUnit.Framework.Assert.That(value, Is.Not.Null, BuildMessage(GetMemberName(actual), message));
    }

    public static void Null(object actual, string message = null)
    {
        NUnit.Framework.Assert.That(actual, Is.Null, BuildMessage(message));
    }

    public static void Null<TResult>(Expression<Func<TResult>> actual, string message = null)
    {
        var value = Evaluate(actual);
        NUnit.Framework.Assert.That(value, Is.Null, BuildMessage(GetMemberName(actual), message));
    }

    public static void IsTrue(bool value, string message = null)
    {
        NUnit.Framework.Assert.That(value, Is.True, BuildMessage(message));
    }

    public static void IsFalse(bool value, string message = null)
    {
        NUnit.Framework.Assert.That(value, Is.False, BuildMessage(message));
    }

    public static TException Throw<TException>(TestDelegate action) where TException : Exception
    {
        return NUnit.Framework.Assert.Throws<TException>(action);
    }

    public static void Fail(string message)
    {
        NUnit.Framework.Assert.Fail(message);
    }

    private static TResult Evaluate<TResult>(Expression<Func<TResult>> expression)
    {
        if (expression == null)
        {
            throw new ArgumentNullException(nameof(expression));
        }

        // Let assertion failures and property getter exceptions surface as-is.
        return expression.Compile()();
    }

    private static string GetMemberName(LambdaExpression expression)
    {
        var body = expression.Body;

        // Unwrap the Convert node that the compiler inserts for boxed
        // value types (e.g. () => (object)item.Count).
        while (body is UnaryExpression unary &&
               (unary.NodeType == ExpressionType.Convert ||
                unary.NodeType == ExpressionType.ConvertChecked))
        {
            body = unary.Operand;
        }

        return body is MemberExpression member
            ? member.Member.Name
            : expression.ToString();
    }

    private static string BuildMessage(string message)
    {
        return string.IsNullOrWhiteSpace(message) ? null : message;
    }

    private static string BuildMessage(string fieldName, string message)
    {
        if (string.IsNullOrWhiteSpace(fieldName))
        {
            return BuildMessage(message);
        }

        return string.IsNullOrWhiteSpace(message)
            ? fieldName
            : fieldName + ": " + message;
    }
}
