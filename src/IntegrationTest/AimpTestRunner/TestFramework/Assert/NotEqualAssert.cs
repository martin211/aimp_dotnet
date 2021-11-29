using Aimp.TestRunner.UnitTests;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public class NotEqualAssert : MemberAssert
    {
        public object Expected { get; }

        public NotEqualAssert(string name, object value, object expected, string message)
            : base(name, value, message)
        {
            Expected = expected;
        }

        public override void Validate(AimpIntegrationTest testClass)
        {
            NUnit.Framework.Assert.AreNotEqual(Expected, Value, Message ?? $"Expected '{Expected}' but was '{Value}'");
            base.Validate(testClass);
        }
    }
}