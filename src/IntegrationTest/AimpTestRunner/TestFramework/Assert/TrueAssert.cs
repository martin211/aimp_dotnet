// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace Aimp.TestRunner.TestFramework.Assert;

public class TrueAssert : MemberAssert<bool>
{
    public TrueAssert(string name, bool value, string message)
        : base(name, value, message)
    {
    }

    public override void Validate()
    {
        Validate(() => NUnit.Framework.Assert.True(Value, $"Expected 'true' but was '{Value}'"));
    }
}
