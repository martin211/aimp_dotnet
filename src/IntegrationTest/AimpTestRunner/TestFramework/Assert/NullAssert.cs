using Aimp.TestRunner.UnitTests;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public class NullAssert : MemberAssert
    {
        public NullAssert(string name, object value, string message) : base(name, value, message)
        {
        }

        public override void Validate(AimpIntegrationTest testClass)
        {
            NUnit.Framework.Assert.Null(Value, FieldName);
            base.Validate(testClass);
        }
    }
}