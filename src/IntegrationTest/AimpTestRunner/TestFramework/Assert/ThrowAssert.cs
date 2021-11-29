using System;
using NUnit.Framework;
using NUnit.Framework.Constraints;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public class ThrowAssert<TException> : MemberAssert where TException : Exception
    {
        public Exception CatchedException;

        public ThrowAssert(TestDelegate action) : base(string.Empty, string.Empty, string.Empty)
        {
            try
            {
                action();
            }
            catch (Exception e)
            {
                CatchedException = e;
            }
        }

        public override void Validate(AimpIntegrationTest testClass)
        {
            var expectedType = typeof(TException);
            NUnit.Framework.Assert.That(CatchedException, new ExceptionTypeConstraint(expectedType));
            base.Validate(testClass);
        }
    }
}
