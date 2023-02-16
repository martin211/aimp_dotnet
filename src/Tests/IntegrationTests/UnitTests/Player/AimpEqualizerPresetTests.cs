//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

[TestFixture(Category = "EqualizerPreset")]
public class AimpEqualizerPresetTests : AimpIntegrationTest
{
    public override void TearDown()
    {
    }

    [Test]
    public void GetName_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.Add("IntegrationTest");
            AssertOKResult(result);

            var result2 = result.Result.GetName();
            AssertOKResult(result2);

            AimpAssert.AreEqual("IntegrationTest", result2.Result.GetData());
        });
    }

    [Test]
    public void SetName_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.Add("IntegrationTest");
            AssertOKResult(result);

            var r = result.Result.GetName();
            AssertOKResult(r);
            AimpAssert.AreEqual("IntegrationTest", r.Result.GetData());

            var res = r.Result.Clone();
            var newString = res.Result;
            newString.SetData("EditedIntegrationTest", "EditedIntegrationTest".Length);
            var r2 = result.Result.SetName(newString);
            AssertOKResult(r2);

            r = result.Result.GetName();
            AssertOKResult(r);
            AimpAssert.AreEqual("EditedIntegrationTest", r.Result.GetData());
        });
    }
}
