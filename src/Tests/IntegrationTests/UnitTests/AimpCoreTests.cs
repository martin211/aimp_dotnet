//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Lyrics.Objects;
using AIMP.SDK.MenuManager.Objects;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests;

[TestFixture(Category = "Core")]
public class AimpCoreTests : AimpIntegrationTest
{
    [Test]
    public void CreateObject_IAimpStream_ShouldCreateAimpObject()
    {
        var result = Player.Core.CreateObject<IAimpStream>();
        AssertOKResult(result);
    }

    [Test]
    public void CreateObject_IAimpAction_ShouldCreateAimpObject()
    {
        var result = Player.Core.CreateObject<IAimpAction>();
        AssertOKResult(result);
    }

    [Test]
    public void CreateObject_IAimpMenuItem_ShouldCreateAimpObject()
    {
        var result = Player.Core.CreateObject<IAimpMenuItem>();
        AssertOKResult(result);
    }

    [Test]
    public void CreateObject_IAimpFileInfo_ShouldCreateAimpObject()
    {
        var result = Player.Core.CreateObject<IAimpFileInfo>();
        AssertOKResult(result);
    }

    [Test]
    public void CreateObject_IAimpLyrics_ShouldCreateAimpObject()
    {
        var result = Player.Core.CreateObject<IAimpLyrics>();
        AssertOKResult(result);
    }

    [Test]
    public void CreateObject_IAimpErrorInfo_ShouldCreateAimpObject()
    {
        var result = Player.Core.CreateObject<IAimpErrorInfo>();
        AssertOKResult(result);
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
        if (m == null) Assert.Fail($"Service {service} was not found at Player.");
        AimpAssert.IsTrue(((IAimpService)m.GetValue(Player)).IsExists);
    }
}
