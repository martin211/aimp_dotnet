using System;
using System.Linq.Expressions;
using AIMP.SDK;
using AIMP.SDK.Annotations;
using Aimp.TestRunner.TestFramework.Assert;
using NUnit.Framework;
using NUnit.Framework.Internal;

namespace Aimp.TestRunner.TestFramework
{
    public static class IntegrationTestExtension
    {
        private static TestExecutionContext _testExecutionContext = TestExecutionContext.CurrentContext;

        public static EqualAssert AreEqual<TResult>(this AimpIntegrationTest testClass, object expected, Expression<Func<TResult>> current, string message = null)
        {
            var assert = new EqualAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), expected,
                message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static EqualAssert AreEqual(this AimpIntegrationTest testClass,
            object expected,
            object current,
            string fieldName = null,
            string message = null)
        {
            var assert = new EqualAssert(fieldName, current, expected, message);
            try
            {
                AddAssertion(testClass, assert);
                return assert;
            }
            finally
            {
                if (testClass.IsValid)
                {
                    assert.Validate(testClass);
                }
            }
        }

        public static EqualAssert AreEqual(this AimpIntegrationTest testClass,
            object expected,
            object current,
            string message)
        {
            return testClass.AreEqual(expected, current, string.Empty, message);
        }

        public static NotNullAssert NotNull<TResult>(this AimpIntegrationTest testClass, Expression<Func<TResult>> current, string message = null)
        {
            var assert = new NotNullAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static NotNullAssert NotNull(this AimpIntegrationTest testClass, object current, string fieldName = null,
            string message = null)
        {
            var assert = new NotNullAssert(fieldName, current, message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static NotEqualAssert AreNotEqual(this AimpIntegrationTest testClass, object expected,
            object current,
            string fieldName = null,
            string message = null)
        {
            var assert = new NotEqualAssert(fieldName, current, expected, message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static NotEqualAssert AreNotEqual<TResult>(this AimpIntegrationTest testClass, object expected,
            Expression<Func<TResult>> current, string message = null)
        {
            var assert = new NotEqualAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), expected,
                message);
            testClass.Asserts.Add(assert);
            return assert;
        }

        public static TrueAssert IsTrue(this AimpIntegrationTest testClass, bool value, string message = "")
        {
            var assert = new TrueAssert(null, value, message);
            try
            {
                AddAssertion(testClass, assert);
                return assert;
            }
            finally
            {
                assert.Validate(testClass);
            }
        }

        public static FalseAssert IsFalse(this AimpIntegrationTest testClass, bool value)
        {
            var assert = new FalseAssert(null, value, null);
            try
            {
                AddAssertion(testClass, assert);
                return assert;
            }
            finally
            {
                assert.Validate(testClass);
            }
        }

        public static TException Throw<TException>(this AimpIntegrationTest testClass, TestDelegate action)
            where TException : Exception
        {
            var assert = new ThrowAssert<TException>(action);
            testClass.Asserts.Add(assert);
            return (TException) assert.CatchedException;
        }

        public static AimpActionResult Result(this AimpIntegrationTest testClass, ActionResultType result)
        {
            return new AimpActionResult(result);
        }

        public static AimpActionResult Result(this ActionResultType res)
        {
            return new AimpActionResult(res);
        }

        public static void Null<TResult>(this AimpIntegrationTest testClass, Expression<Func<TResult>> current)
        {
            testClass.Asserts.Add(new NullAssert(current.GetExpressionMemberName(), current.GetExpressionValue(), null));
        }

        public static IMemberAssert Finally(this MemberAssert assert, [NotNull] Action finallyAction)
        {
            assert.AfterAssertion = finallyAction;
            return assert;
        }

        private static string GetExpressionMemberName<TResult>(this Expression<Func<TResult>> expression)
        {
            string memberName = string.Empty;

            if (expression is MemberExpression memberExpression)
            {
                memberName = memberExpression.Member.Name;
            }
            else if (expression is LambdaExpression lambdaExpression)
            {
                if (lambdaExpression.Body is MemberExpression me)
                {
                    memberName = me.Member.Name;
                }
                else
                {
                    throw new ArgumentException(
                        $"Expression '{expression}' refers to a method, not a property.");
                }
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
            if (_testExecutionContext.CurrentResult.FailCount == 0 || testClass.IsValid)
            {
                testClass.Asserts.Add(assertion);
            }
        }
    }
}