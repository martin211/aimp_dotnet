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

        [Test]
        public void CreateObject_IAimpErrorInfo_ShouldCreateAimpObject()
        {
            var result = Player.Core.CreateObject<IAimpErrorInfo>();
            AssertResult(result);
        }

        [TestCase("ServiceMenuManager")]
        [TestCase("ServiceActionManager")]
        [TestCase("ServiceMui")]
        [TestCase("ServiceAlbumArt")]
        [TestCase("ServiceAlbumArtCache")]
        [TestCase("ServiceConfig")]
        [TestCase("ServicePlaylistManager")]
        [TestCase("ServicePlaybackQueue")]
        [TestCase("ServiceOptionsDialog")]
        [TestCase("ServiceMessageDispatcher")]
        [TestCase("ServiceSynchronizer")]
        [TestCase("ServiceThreadPool")]
        [TestCase("ServiceMusicLibrary")]
        [TestCase("ServiceMusicLibraryUi")]
        [TestCase("ServiceFileFormats")]
        [TestCase("ServiceFileInfo")]
        [TestCase("ServiceFileSystems")]
        [TestCase("ServiceFileStreaming")]
        [TestCase("ServiceFileInfoFormatter")]
        [TestCase("ServiceFileTagEditor")]
        [TestCase("ServiceLyrics")]
        public void Service_IsExists_AllServicesShouldExists(string service)
        {
            var t = Player.GetType();
            var m = t.GetProperty(service);
            if (m == null)
            {
                Assert.Fail($"Service {service} was not found at Player.");
            }
            this.IsTrue(((IAimpService)m.GetValue(Player)).IsExists).Validate(this);
        }

        private void AssertResult(AimpActionResult<IAimpObject> result)
        {
            this.AreEqual(ActionResultType.OK, result.ResultType).Validate(this);
            this.NotNull(result.Result).Validate(this);
        }
    }
}