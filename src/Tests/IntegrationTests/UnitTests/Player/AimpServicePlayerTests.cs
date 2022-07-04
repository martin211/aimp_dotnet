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

using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

[TestFixture(Category = "ServicePlayer")]
public class AimpServicePlayerTests : AimpIntegrationTest
{
    public override void RunBeforeAnyTests()
    {
        base.RunBeforeAnyTests();
        ExecuteInMainThread(() =>
        {
            var pl = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            _playlist = pl.Result;
            return pl;
        });
    }

    public override void AfterAllTests()
    {
        base.AfterAllTests();

        if (_playlist != null) _playlist.Close(PlaylistCloseFlag.ForceRemove);
    }

    private IAimpPlaylist _playlist;

    [Test]
    [Ignore("Not working in integration")]
    public void Volume_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.Volume = 20;
            AimpAssert.AreEqual(20, Player.ServicePlayer.Volume);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void IsMute_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.IsMute = true;
            AimpAssert.IsTrue(Player.ServicePlayer.IsMute);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void Position_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.Position = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.Position);
        });
    }

    [Test]
    public void AutoJumpToNextTrack_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.AutoJumpToNextTrack = true;
            AimpAssert.IsTrue(Player.ServicePlayer.AutoJumpToNextTrack);
        });
    }

    [Test]
    public void AutoSwitching_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.AutoSwitching = true;
            AimpAssert.IsTrue(Player.ServicePlayer.AutoSwitching);
        });
    }

    [Test]
    public void AutoSwitchingPauseBetweenTracks_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.AutoSwitchingPauseBetweenTracks = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.AutoSwitchingPauseBetweenTracks);
        });
    }

    [Test]
    public void AutoSwitchingCrossFade_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.AutoSwitchingCrossFade = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.AutoSwitchingCrossFade);
        });
    }

    [Test]
    public void AutoSwitchingFadeIn_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.AutoSwitchingFadeIn = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.AutoSwitchingFadeIn);
        });
    }

    [Test]
    public void AutoSwitchingFadeOut_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.AutoSwitchingFadeOut = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.AutoSwitchingFadeOut);
        });
    }

    [Test]
    public void ManualSwitching_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.ManualSwitching = true;
            AimpAssert.IsTrue(Player.ServicePlayer.ManualSwitching);
        });
    }

    [Test]
    public void ManualSwitchingCrossFade_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.ManualSwitchingCrossFade = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.ManualSwitchingCrossFade);
        });
    }

    [Test]
    public void ManualSwitchingFadeIn_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.ManualSwitchingFadeIn = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.ManualSwitchingFadeIn);
        });
    }

    [Test]
    public void ManualSwitchingFadeOut_OK()
    {
        ExecuteInMainThread(() =>
        {
            Player.ServicePlayer.ManualSwitchingFadeOut = 10;
            AimpAssert.AreEqual(10, Player.ServicePlayer.ManualSwitchingFadeOut);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void GoToNext_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.GoToNext();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void GoToPrev_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.GoToPrev();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void Pause_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.Pause();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void Resume_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.Resume();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void Stop_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.Stop();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void StopAfterTrack_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.StopAfterTrack();
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void Play_QueueItem_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");
        });
    }

    [Test]
    public void Play_PlaylistItem_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var item = _playlist.GetItem(1);

            var result = Player.ServicePlayer.Play(item.Result);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    public void Play_Playlist_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var result = Player.ServicePlayer.Play(_playlist);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [Test]
    [Ignore("Not working in integration")]
    public void Play_FileUri_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlayer.Play(PlaylistPath, PlayFlags.FromPlaylist);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            Player.ServicePlaylistManager.GetActivePlaylist().Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    [Ignore("TBD")]
    public void Play_QueueItem_Offset_OK()
    {
    }

    [Test]
    public void Play_PlaylistItem_Offset_OK()
    {
        ExecuteInMainThread(() =>
        {
            if (_playlist == null) Assert.Fail("Playlist not found");

            var item = _playlist.GetItem(1);
            var result = Player.ServicePlayer.Play(item.Result, 100, PlayFlags.FromPlaylist);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }
}
