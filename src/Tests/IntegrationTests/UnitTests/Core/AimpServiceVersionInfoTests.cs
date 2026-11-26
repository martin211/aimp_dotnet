using System;
using AIMP.SDK;
using AIMP.SDK.Core;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Core;

[TestFixture(Category = "ServiceVersionInfo")]
public class AimpServiceVersionInfoTests : AimpIntegrationTest
{
    [Test]
    public void FormatInfo_ShouldReturnCorrectInformation()
    {
        var version = Player.Version;
        TestContext.WriteLine($"Current version: {version}");
        AimpAssert.IsTrue(version.IsKnown);
        AimpAssert.IsFalse(string.IsNullOrWhiteSpace(version.ToString()));
    }

    [Test]
    public void BuildDate_ShouldNotBeMinValue()
    {
        var date = Player.Version.BuildDate;
        TestContext.WriteLine($"Build date: {date}");
        AimpAssert.IsTrue(date != DateTime.MinValue);
    }

    [Test]
    public void BuildState_ShouldReturnCorrectValue()
    {
        var build = Player.Version.BuildState;
        TestContext.WriteLine($"Build state: {build}");
        AimpAssert.AreEqual(BuildStateType.Relese, build);
    }

    [Test]
    public void BuildNumber_ShouldReturnCorrectValue()
    {
        var number = Player.Version.Build;
        TestContext.WriteLine($"Build number: {number}");
        AimpAssert.IsTrue(number > 0);
    }

    [Test]
    public void VersionId_ShouldReturnCorrectValue()
    {
        var versionId = Player.Version.VersionId;
        TestContext.WriteLine($"Version Id: {versionId}");
        AimpAssert.IsTrue(versionId > 0);
    }
}
