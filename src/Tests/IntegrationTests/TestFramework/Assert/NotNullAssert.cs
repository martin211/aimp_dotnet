//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using NUnit.Framework;

namespace Aimp.TestRunner.TestFramework.Assert;

public class NotNullAssert : MemberAssert
{
    public NotNullAssert(string name, object value, string message) : base(name, value, message)
    {
    }

    public override void Validate()
    {
        Validate(() => NUnit.Framework.Assert.That(Value, Is.Not.Null));
    }
}
