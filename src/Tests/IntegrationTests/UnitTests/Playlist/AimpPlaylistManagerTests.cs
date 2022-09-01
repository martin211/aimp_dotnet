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
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playlist;

[TestFixture(Category = "PlaylistManager")]
public class AimpPlaylistManagerTests : AimpIntegrationTest
{
    public override void RunBeforeAnyTests()
    {
        base.SetUp();
        ExecuteInMainThread(() =>
        {
            var count = Player.ServicePlaylistManager.GetLoadedPlaylistCount();
            for (var i = count - 1; i >= 0; i--)
            {
                var pl = Player.ServicePlaylistManager.GetLoadedPlaylist(i);
                pl.Result.Close(PlaylistCloseFlag.ForceRemove);
            }
        });
    }

    [Test]
    public void CreatePlaylist_EmptyName_ShouldGenerateName()
    {
        ExecuteInMainThreadAndWait(() =>
        {
            var res = Player.ServicePlaylistManager.CreatePlaylist(null, false);
            AssertOKResult(res);

            AimpAssert.AreNotEqual(string.Empty, () => res.Result.Name);
            AimpAssert.AreNotEqual(string.Empty, () => res.Result.Id);

            res.Result.Close(PlaylistCloseFlag.ForceRemove);
            res.Result.Dispose();
        });
    }

    [Test]
    public void CreatePlaylist_IsActive_ShouldSetAsActive()
    {
        ExecuteInMainThreadAndWait(() =>
        {
            var res = Player.ServicePlaylistManager.CreatePlaylist("Active", true);
            AssertOKResult(res);

            AimpAssert.AreEqual("Active", res.Result.Name);

            var active = Player.ServicePlaylistManager.GetActivePlaylist();

            AssertOKResult(active);
            AimpAssert.AreEqual(active.Result.Id, res.Result.Id);

            res.Result.Close(PlaylistCloseFlag.ForceRemove);
            res.Result.Dispose();
        });
    }

    [Test]
    public void CreatePlaylist_NotIsActive_ShouldNoBeActive()
    {
        ExecuteInMainThreadAndWait(() =>
        {
            var res = Player.ServicePlaylistManager.CreatePlaylist("NotActive", false);
            AssertOKResult(res);

            AimpAssert.AreEqual("NotActive", res.Result.Name);

            var active = Player.ServicePlaylistManager.GetActivePlaylist();
            AssertOKResult(active);

            AimpAssert.AreNotEqual(active.Result.Id, res.Result.Id);

            res.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test(Description = "Should throw exception if path to playlist file is empty.")]
    public void CreatePlaylistFromFile_EmptyFileName_ShouldThrowException()
    {
        ExecuteInMainThread(() =>
        {
            AimpAssert.Throw<ArgumentNullException>(() =>
                Player.ServicePlaylistManager.CreatePlaylistFromFile("", false));
            return new AimpActionResult(ActionResultType.OK);
        });
    }

    [Test(Description = "Should create a playlist from file. It should not be active.")]
    public void CreatePlaylistFromFile_FileNameNotEmptyAndNotActive_ShouldCreatePlaylist()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, false);
            AssertOKResult(res);

            AimpAssert.AreNotEqual(string.Empty, res.Result.Name);
            AimpAssert.AreNotEqual(string.Empty, res.Result.Id);

            var active = Player.ServicePlaylistManager.GetActivePlaylist();
            AssertOKResult(active);

            AimpAssert.AreNotEqual(active.Result.Id, res.Result.Id);

            res.Result.Close(PlaylistCloseFlag.ForceRemove);
            res.Result.Dispose();
        });
    }

    [Test(Description = "Should create a playlist from file. It should be active.")]
    public void CreatePlaylistFromFile_FileNameNotEmptyAndIsActive_ShouldBeActive()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            AssertOKResult(result);

            var active = Player.ServicePlaylistManager.GetActivePlaylist();
            AssertOKResult(active);
            AimpAssert.AreEqual(active.Result.Id, result.Result.Id);

            result.Result.Close(PlaylistCloseFlag.ForceRemove);
            result.Result.Dispose();
        });
    }

    [Test(Description = "Should set a playlist as a active.")]
    public void SetActivePlaylist_ShouldBeOK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.CreatePlaylist("New playlist", false);
            AssertOKResult(result);

            AimpAssert.AreNotEqual(string.Empty, result.Result.Name);
            AimpAssert.AreNotEqual(string.Empty, result.Result.Id);

            var result2 = Player.ServicePlaylistManager.SetActivePlaylist(result.Result);
            AimpAssert.AreEqual(ActionResultType.OK, result2.ResultType);

            var activePlaylist = Player.ServicePlaylistManager.GetActivePlaylist();
            AimpAssert.AreEqual(ActionResultType.OK, activePlaylist.ResultType);
            AimpAssert.AreEqual(activePlaylist.Result.Id, result.Result.Id);

            result.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test(Description = "Create a new playlist and check current count value.")]
    public void GetLoadedPlaylistCount_ShouldReturnCount()
    {
        ExecuteInMainThread(() =>
        {
            var oldCount = Player.ServicePlaylistManager.GetLoadedPlaylistCount();
            var result = Player.ServicePlaylistManager.CreatePlaylist("New playlist", false);

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.NotNull(result.Result);

            var count = Player.ServicePlaylistManager.GetLoadedPlaylistCount();
            AimpAssert.AreEqual(oldCount + 1, count);

            result.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    //[Ignore("Not working in integration mode")]
    public void GetPlayablePlaylist_ShouldReturnPlaylist()
    {
        IAimpPlaylist playlist = null;

        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType);
            playlist = playlistResult.Result;
            Player.ServicePlayer.Play(playlist);
        });

        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.GetPlayingPlaylist();

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.NotNull(result.Result);

            return playlist.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    public void GetLoadedPlaylist_ShouldReturnPlaylist()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.GetLoadedPlaylist(0);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.NotNull(result.Result);
        });
    }

    [Test(Description = "Should return InvalidArgument result")]
    public void GetLoadedPlaylist_WrongIndex_InvalidArgument()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.GetLoadedPlaylist(100);
            AimpAssert.AreEqual(ActionResultType.InvalidArguments, () => result.ResultType);
            AimpAssert.Null(() => result.Result);
        });
    }

    [Test(Description = "Create a new playlist and get it by id.")]
    public void GetLoadedPlaylistById_ShouldReturnPlaylist()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.CreatePlaylist(null, false);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.NotNull(result.Result);

            var getResult = Player.ServicePlaylistManager.GetLoadedPlaylistById(result.Result.Id);
            AimpAssert.AreEqual(ActionResultType.OK, getResult.ResultType);
            AimpAssert.NotNull(getResult.Result);
            AimpAssert.AreEqual(result.Result.Id, getResult.Result.Id);

            result.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test(Description = "Create a new playlist and get it by name")]
    public void GetLoadedPlaylistByName_ShouldReturnPlaylist()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServicePlaylistManager.CreatePlaylist("Get by name", false);
            AimpAssert.AreEqual(ActionResultType.OK, () => result.ResultType);
            AimpAssert.NotNull(result.Result);

            var getResult = Player.ServicePlaylistManager.GetLoadedPlaylistByName("Get by name");
            AimpAssert.AreEqual(ActionResultType.OK, () => getResult.ResultType);
            AimpAssert.NotNull(getResult.Result);
            AimpAssert.AreEqual(result.Result.Name, () => getResult.Result.Name);

            result.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }
}
