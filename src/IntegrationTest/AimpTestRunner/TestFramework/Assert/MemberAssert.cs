using System;
using Aimp.TestRunner.UnitTests;

namespace Aimp.TestRunner.TestFramework.Assert
{
    public abstract class MemberAssert : MemberAssert<object>
    {
        protected MemberAssert(string name, object value, string message)
            : base(name, value, message)
        {
            FieldName = name;
            Value = value;
            Message = message;
        }
    }

    public abstract class MemberAssert<TValue> : IMemberAssert
    {
        public Action AfterAssertion { get; internal set; }

        public string FieldName { get; set; }

        public TValue Value { get; set; }

        public string Message { get; set; }

        protected MemberAssert(string name, TValue value, string message)
        {
            FieldName = name ?? "Field";
            Value = value;
            Message = message;
        }

        public virtual void Validate(AimpIntegrationTest testClass)
        {
            AfterAssertion?.Invoke();
        }
    }

    public interface IMemberAssert
    {
        Action AfterAssertion { get; }

        void Validate(AimpIntegrationTest testClass);
    }
}
