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

using System;
using System.Threading;
using AIMP.SDK;
using AIMP.SDK.AlbumArtManager;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.AlbumArtManager;

public class AimpServiceAlbumArtTests : AimpIntegrationTest
{
    [Test]
    public void Get_EmptyFileUri_ShouldThrowException()
    {
        var ex = Assert.Throws<ArgumentNullException>(() =>
        {
            Player.ServiceAlbumArt.Get(string.Empty, string.Empty, string.Empty,
                AimpFindCovertArtType.AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE |
                AimpFindCovertArtType.AIMP_SERVICE_ALBUMART_FLAGS_WAITFOR, "userData");
        });
        Assert.IsTrue(ex.Message.Contains("Parameter fileUrl cannot be empty"));
    }

    [Test]
    public void Get_ShouldReturnTaskId()
    {
        var completed = false;
        Player.ServiceAlbumArt.Completed += (sender, args) => { completed = true; };
        var result = Player.ServiceAlbumArt.Get("url", string.Empty, string.Empty,
            AimpFindCovertArtType.AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE, "userData");

        Assert.AreEqual(ActionResultType.OK, result.ResultType);
        Assert.IsTrue(result.Result > 0);
        Thread.Sleep(1000);
        //Assert.IsTrue(completed);
    }

    [Test]
    [Ignore("Fix it")]
    public void Get2_ShouldReturnTaskId()
    {
        var completed = false;
        Player.ServiceAlbumArt.Completed += (sender, args) => { completed = true; };

        ExecuteInMainThread(() =>
        {
            var createResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            Player.ServicePlayer.Play(createResult.Result);
        });


        var fi = Player.ServicePlayer.CurrentFileInfo;
        Assert.NotNull(fi);
        var result = Player.ServiceAlbumArt.Get2(fi, AimpFindCovertArtType.AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE,
            "userData");

        Assert.AreEqual(ActionResultType.OK, result.ResultType);
        Assert.IsTrue(result.Result > 0);
        Thread.Sleep(1000);
        Assert.IsTrue(completed);
    }

    [Test]
    public void Cancel_ShouldCancelGetTask()
    {
        var result = Player.ServiceAlbumArt.Get("url", string.Empty, string.Empty,
            AimpFindCovertArtType.AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE, "userData");

        Assert.AreEqual(ActionResultType.OK, result.ResultType);
        Assert.IsTrue(result.Result > 0);
        var result2 = Player.ServiceAlbumArt.Cancel(result.Result,
            AimpFindCovertArtType.AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE);
        Assert.AreEqual(ActionResultType.OK, result2.ResultType);
    }
}
