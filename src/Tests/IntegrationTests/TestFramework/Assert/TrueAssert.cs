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
    bool _val;
    public TrueAssert(string name, bool value, string message)
        : base(name, value, message)
    {
        _val = value;
    }

    public override void Validate()
    {
        Validate(() => NUnit.Framework.Assert.IsTrue(Value.ToString().Equals(true.ToString())));
    }
}
