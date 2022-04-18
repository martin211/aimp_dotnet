// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Linq.Expressions;
using Aimp.TestRunner.TestFramework.Assert;
using NUnit.Framework;
using NUnit.Framework.Internal;

namespace Aimp.TestRunner.TestFramework;

public static class AimpAssert
{
    private static readonly TestExecutionContext TestExecutionContext = TestExecutionContext.CurrentContext;

    public static void AreEqual<TResult>(object expected, Expression<Func<TResult>> current, string message = null)
    {
        new EqualAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), expected, message)
            .Validate();
    }

    public static void AreEqual(object expected, object current, string fieldName = null, string message = null)
    {
        new EqualAssert(fieldName, current, expected, message).Validate();
    }

    public static void NotNull<TResult>(Expression<Func<TResult>> current, string message = null)
    {
        new NotNullAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), message).Validate();
    }

    public static void NotNull(object current, string fieldName = null, string message = null)
    {
        new NotNullAssert(fieldName, current, message).Validate();
    }

    public static void AreNotEqual(object expected, object current, string fieldName = null, string message = null)
    {
        new NotEqualAssert(fieldName, current, expected, message).Validate();
    }

    public static void IsTrue(bool value, string message = "")
    {
        new TrueAssert(null, value, message).Validate();
    }

    public static void IsFalse(bool value)
    {
        new FalseAssert(null, value, null).Validate();
    }

    public static TException Throw<TException>(TestDelegate action)
        where TException : Exception
    {
        var assert = new ThrowAssert<TException>(action);
        return (TException)assert.CatchedException;
    }

    public static void Null<TResult>(Expression<Func<TResult>> current)
    {
        new NullAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), null).Validate();
    }

    private static string GetExpressionMemberName<TResult>(this Expression<Func<TResult>> expression)
    {
        var memberName = string.Empty;

        if (expression is MemberExpression memberExpression)
        {
            memberName = memberExpression.Member.Name;
        }
        else if (expression is LambdaExpression lambdaExpression)
        {
            if (lambdaExpression.Body is MemberExpression me)
                memberName = me.Member.Name;
            else
                throw new ArgumentException(
                    $"Expression '{expression}' refers to a method, not a property.");
            memberName = lambdaExpression.Name;
        }

        return memberName;
    }

    private static object GetExpressionValue<TResult>(this Expression<Func<TResult>> expression)
    {
        var valueGetter = expression.Compile();
        try
        {
            return valueGetter();
        }
        catch (Exception ex)
        {
            TestContext.Error.WriteLine(ex.ToString());
            return default;
        }
    }

    private static void AddAssertion(AimpIntegrationTest testClass, IMemberAssert assertion)
    {
        if (TestExecutionContext.CurrentResult.FailCount == 0 || testClass.IsValid)
            testClass.Asserts.Add(assertion);
    }
}
