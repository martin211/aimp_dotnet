using System;
using Aimp.TestRunner.UnitTests;
using NUnit.Framework;
using NUnit.Framework.Internal;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public class EqualAssert : MemberAssert
    {
        public object Expected { get; }

        public EqualAssert(string name, object value, object expected, string message)
            : base(name, value, message)
        {
            Expected = expected;
        }

        public override void Validate(AimpIntegrationTest testClass)
        {
            try
            {
                NUnit.Framework.Assert.AreEqual(Expected, Value, Message ?? $"Expected '{Expected}' but was '{Value}'");
            }
            catch (Exception)
            {
                var result = TestExecutionContext.CurrentContext.CurrentResult;

                if (result.FailCount == 1)
                {
                    TestContext.WriteLine(result.Message);
                    TestContext.WriteLine(result.StackTrace);
                    TestContext.Out.WriteLine(result.Message);
                    TestContext.Out.WriteLine(result.StackTrace);
                }
            }

            base.Validate(testClass);
        }
    }
}