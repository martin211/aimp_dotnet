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

using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

[TestFixture(Category = "ServicePlayerEqualizerPresets")]
public class AimpServicePlayerEqualizerPresetsTests : AimpIntegrationTest
{
    [Test]
    [Order(1)]
    public void Add_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.Add("IntegrationTest");
            AssertOKResult(result);
            AimpAssert.NotNull(result.Result);
        });
    }

    [Test]
    [Order(2)]
    public void FindByName_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.FindByName("IntegrationTest");
            AssertOKResult(result);
            AimpAssert.NotNull(result.Result);
        });
    }

    [Test]
    [Order(3)]
    public void Delete_Preset_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.FindByName("IntegrationTest");
            AssertOKResult(result);

            var res = Player.ServicePlayerEqualizerPresets.Delete(result.Result);
            AssertOKResult(res);
        });
    }

    [Test]
    public void Delete_ByIndex_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.Add("IntegrationTest");
            AssertOKResult(result);

            var res = Player.ServicePlayerEqualizerPresets.Delete(0);
            AssertOKResult(res);
        });
    }

    [Test]
    public void GetPreset_ByIndex_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.Add("IntegrationTest");
            AssertOKResult(result);

            var res = Player.ServicePlayerEqualizerPresets.GetPreset(1);
            AssertOKResult(res);
            AimpAssert.NotNull(res.Result);
        });
    }

    [Test]
    public void GetPresetCount_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizerPresets.GetPresetCount();
            AimpAssert.IsTrue(result > 0);
        });
    }
}
