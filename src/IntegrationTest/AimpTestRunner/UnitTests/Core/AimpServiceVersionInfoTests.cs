// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK.Core;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Core
{
    [TestFixture]
    public class AimpServiceVersionInfoTests : AimpIntegrationTest
    {
        [Test]
        public void FormatInfo_ShouldReturnCorrectInformation()
        {
            var currentVersion = Player.ServiceVersionInfo.FormatInfo;
            this.NotNull(currentVersion);
            this.IsFalse(string.IsNullOrWhiteSpace(currentVersion));
            TestContext.WriteLine($"Current version: {currentVersion}");
        }

        [Test]
        public void BuildDate_ShouldNotBeMinValue()
        {
            var date = Player.ServiceVersionInfo.BuildDate;
            TestContext.WriteLine($"Build date: {date}");
            this.IsTrue(date != DateTime.MaxValue);
        }

        [Test]
        public void BuildState_ShouldReturnCorrectValue()
        {
            var build = Player.ServiceVersionInfo.BuildState;
            TestContext.WriteLine($"Build state: {build}");
            this.AreEqual(BuildStateType.Relese, build);
        }

        [Test]
        public void BuildNumber_ShouldReturnCorrectValue()
        {
            var number = Player.ServiceVersionInfo.BuildNumber;
            TestContext.WriteLine($"Build number: {number}");
            this.IsTrue(number > 0);
        }

        [Test]
        public void VersionId_ShouldReturnCorrectValue()
        {
            var versionId = Player.ServiceVersionInfo.VersionId;
            TestContext.WriteLine($"Version Id: {versionId}");
            this.IsTrue(versionId > 0);
        }
    }
}
