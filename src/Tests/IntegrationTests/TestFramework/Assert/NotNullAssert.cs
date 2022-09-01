//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace Aimp.TestRunner.TestFramework.Assert;

public class NotNullAssert : MemberAssert
{
    public NotNullAssert(string name, object value, string message) : base(name, value, message)
    {
    }

    public override void Validate()
    {
        Validate(() => NUnit.Framework.Assert.NotNull(Value, FieldName));
    }
}
