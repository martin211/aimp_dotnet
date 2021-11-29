using Aimp.TestRunner.UnitTests;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public class NotNullAssert : MemberAssert
    {
        public NotNullAssert(string name, object value, string message) : base(name, value, message)
        {
        }

        public override void Validate(AimpIntegrationTest testClass)
        {
            NUnit.Framework.Assert.NotNull(Value, FieldName);
            base.Validate(testClass);
        }
    }
}