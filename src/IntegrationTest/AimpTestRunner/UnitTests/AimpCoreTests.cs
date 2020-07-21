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

using AIMP.SDK;
using AIMP.SDK.ActionManager;
using AIMP.SDK.FileManager;
using AIMP.SDK.Lyrics;
using AIMP.SDK.MenuManager;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests
{
    public class AimpCoreTests : AimpIntegrationTest
    {
        [Test]
        public void CreateObject_IAimpStream_ShouldCreateAimpObject()
        {
            var result = Player.Core.CreateObject<IAimpStream>();
            AssertResult(result);
        }

        [Test]
        public void CreateObject_IAimpAction_ShouldCreateAimpObject()
        {
            var result = Player.Core.CreateObject<IAimpAction>();
            AssertResult(result);
        }

        [Test]
        public void CreateObject_IAimpMenuItem_ShouldCreateAimpObject()
        {
            var result = Player.Core.CreateObject<IAimpMenuItem>();
            AssertResult(result);
        }

        [Test]
        public void CreateObject_IAimpFileInfo_ShouldCreateAimpObject()
        {
            var result = Player.Core.CreateObject<IAimpFileInfo>();
            AssertResult(result);
        }

        [Test]
        public void CreateObject_IAimpLyrics_ShouldCreateAimpObject()
        {
            var result = Player.Core.CreateObject<IAimpLyrics>();
            AssertResult(result);
        }

        private void AssertResult(AimpActionResult<IAimpObject> result)
        {
            this.AreEqual(ActionResultType.OK, result.ResultType).Validate();
            this.NotNull(result.Result).Validate();
        }
    }
}