using Aimp.TestRunner.UnitTests;
using NUnit.Framework;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public class FalseAssert : MemberAssert<bool>
    {
        public FalseAssert(string name, bool value, string message)
            : base(name, value, message)
        {
        }

        public override void Validate(AimpIntegrationTest testClass)
        {
            try
            {
                NUnit.Framework.Assert.False(Value, $"Expected 'False' but was '{Value}'");
            }
            catch (AssertionException)
            {
                testClass.IsValid = false;
                throw;
            }
            finally
            {
                base.Validate(testClass);
            }
        }
    }
}