﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

[TestFixture(Category = "Player")]
public class AimpPlayerTests : AimpIntegrationTest
{
    //[Test, Order(1)]
    //[Ignore("Not working in integration mode")]
    public void Play_PlayList_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var playlist = Player.ServicePlaylistManager.GetActivePlaylist();
            AimpAssert.AreEqual(ActionResultType.OK, playlist.ResultType);
            AimpAssert.NotNull(playlist.Result);

            var result = Player.ServicePlayer.Play(playlist.Result);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });

        AimpAssert.AreEqual(AimpPlayerState.Playing, Player.ServicePlayer.State);
    }

    //[Test, Order(2)]
    public void Pause_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayer.Pause();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });

        AimpAssert.AreEqual(AimpPlayerState.Pause, Player.ServicePlayer.State);
    }

    //[Test, Order(3)]
    public void Resume_ShouldReturnOK()
    {
        ExecuteInThread(() =>
        {
            var result = Player.ServicePlayer.Resume();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            return new AimpActionResult(result.ResultType);
        });

        AimpAssert.AreEqual(AimpPlayerState.Playing, Player.ServicePlayer.State);
    }

    //[Test, Order(4)]
    public void Stop_ShouldReturnOK()
    {
        ExecuteInThread(() =>
        {
            var result = Player.ServicePlayer.Stop();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            return new AimpActionResult(result.ResultType);
        });

        AimpAssert.AreEqual(AimpPlayerState.Stopped, Player.ServicePlayer.State);
    }

    //[Test]
    public void StopAfterTrack_ShouldReturnOK()
    {
        var result = Player.ServicePlayer.StopAfterTrack();
        AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
    }
}
