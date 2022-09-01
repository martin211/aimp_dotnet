//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

[Ignore("WIP")]
[TestFixture(Category = "ServicePlayerEqualizer")]
public class AimpServicePlayerEqualizerTests : AimpIntegrationTest
{
    [Test]
    [Order(1)]
    public void SetActive_True_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.SetActive(true);
            AimpAssert.AreEqual(ActionResultType.OK, result);

            var state = Player.ServicePlayerEqualizer.GetActive();
            AimpAssert.IsTrue(state);
        });
    }

    [Test]
    [Order(2)]
    public void SetActive_False_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.SetActive(false);
            AimpAssert.AreEqual(ActionResultType.OK, result);

            var state = Player.ServicePlayerEqualizer.GetActive();
            AimpAssert.IsFalse(state);
        });
    }

    [TestCase(-20)]
    [TestCase(20)]
    public void SetPreamp_ShouldThrowError(double preamp)
    {
        ExecuteInMainThread(() =>
        {
            var exception =
                AimpAssert.Throw<ArgumentOutOfRangeException>(() =>
                    Player.ServicePlayerEqualizer.SetPreamp(preamp));
            AimpAssert.IsTrue(exception.Message.Contains("Preamp value should be between -15 and +15"));
        });
    }

    [TestCase(-15)]
    [TestCase(0)]
    [TestCase(15)]
    public void SetPreamp_OK(double preamp)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.SetPreamp(preamp);
            AimpAssert.AreEqual(ActionResultType.OK, result);
        });
    }

    [Test]
    public void GetPreamp_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.SetPreamp(5);
            AimpAssert.AreEqual(ActionResultType.OK, result);

            var res = Player.ServicePlayerEqualizer.GetPreamp();
            AimpAssert.AreEqual(ActionResultType.OK, result);
            AimpAssert.AreEqual(5, res.Result);
        });
    }

    [Test]
    public void GetPreamp_EnabledEqualizer_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.SetActive(true);
            AimpAssert.AreEqual(ActionResultType.OK, result);

            var res = Player.ServicePlayerEqualizer.GetPreamp();
            AimpAssert.AreEqual(ActionResultType.OK, result);
        });
    }

    [Test]
    public void GetPreset_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.GetPreset();
            AimpAssert.AreEqual(ActionResultType.OK, result);

            AimpAssert.NotNull(result.Result);
        });
    }

    [Test]
    public void SetPreset_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.GetPreset();
            AssertOKResult(result);
            //AimpAssert.NotNull(result.Result).AfterAssertion = () =>
            //{
            //    var res = Player.ServicePlayerEqualizer.SetPreset(result.Result);
            //    AssertOKResult(res);
            //};
        });
    }

    [Test]
    public void GetBandCount_OK()
    {
        ExecuteInMainThread(() =>
        {
            var count = Player.ServicePlayerEqualizer.GetBandCount();
            AimpAssert.IsTrue(count > 0);
        });
    }

    [Test]
    public void GetBandFrequency_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.GetBandFrequency(1);
            AssertOKResult(result);
            AimpAssert.IsTrue(result.Result > 0 || result.Result < 0);
        });
    }

    [Test]
    public void GetBandGain_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.GetBandGain(1);
            AssertOKResult(result);
            AimpAssert.IsTrue(result.Result > 0 || result.Result < 0);
        });
    }

    [Test]
    public void SetBandGain_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayerEqualizer.SetBandGain(1, 10.2);
            //AimpAssert.AreEqual(ActionResultType.OK, result.ResultType).AfterAssertion = () =>
            //{

            //};
        });
    }
}
