//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace Aimp.TestRunner.TestFramework.Assert;

public class NotEqualAssert : MemberAssert
{
    public NotEqualAssert(string name, object value, object expected, string message)
        : base(name, value, message)
    {
        Expected = expected;
    }

    public object Expected { get; }

    public override void Validate()
    {
        Validate(() =>
            NUnit.Framework.Assert.AreNotEqual(Expected, Value, Message ?? $"Expected '{Expected}' but was '{Value}'"));
    }
}
