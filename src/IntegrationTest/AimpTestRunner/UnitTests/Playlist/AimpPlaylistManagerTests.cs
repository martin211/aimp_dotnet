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
using System.Threading;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playlist
{
    [TestFixture]
    public class AimpPlaylistManagerTests : AimpIntegrationTest
    {
        [Test]
        public void CreatePlaylist_EmptyName_ShouldGenerateName()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.PlaylistManager.CreatePlaylist(null, false);

                this.AreEqual(ActionResultType.OK, res.ResultType);

                this.NotNull(res.Result);
                this.AreNotEqual(string.Empty, () => res.Result.Name);
                this.AreNotEqual(string.Empty, () => res.Result.Id);

                res.Result.Close(PlaylistCloseFlag.ForceRemove);
                return res.ResultType;
            });
        }

        [Test]
        public void CreatePlaylist_IsActive_ShouldSetAsActive()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.PlaylistManager.CreatePlaylist("Active", true);

                this.AreEqual(ActionResultType.OK, res.ResultType);
                this.NotNull(res.Result);
                this.AreEqual("Active", res.Result.Name);

                if (res.ResultType != ActionResultType.OK)
                {
                    return res.ResultType;
                }

                var active = Player.PlaylistManager.GetActivePlaylist();

                this.AreEqual(ActionResultType.OK, active.ResultType);
                this.NotNull(active.Result);
                this.AreEqual(active.Result.Id, res.Result.Id);

                res.Result.Close(PlaylistCloseFlag.ForceRemove);

                return res.ResultType;
            });
        }

        [Test]
        public void CreatePlaylist_NotIsActive_ShouldNoBeActive()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.PlaylistManager.CreatePlaylist("NotActive", false);

                this.AreEqual(ActionResultType.OK, res.ResultType);
                this.NotNull(res.Result);
                this.AreEqual("NotActive", res.Result.Name);

                if (res.ResultType != ActionResultType.OK)
                {
                    return res.ResultType;
                }

                var active = Player.PlaylistManager.GetActivePlaylist();

                this.AreEqual(ActionResultType.OK, res.ResultType);
                this.NotNull(active.Result);
                this.AreNotEqual(active.Result.Id, res.Result.Id);

                res.Result.Close(PlaylistCloseFlag.ForceRemove);

                return res.ResultType;
            });
        }

        [Test(Description = "Should throw exception if path to playlist file is empty.")]
        public void CreatePlaylistFromFile_EmptyFileName_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                this.Throw<ArgumentNullException>(() => Player.PlaylistManager.CreatePlaylistFromFile("", false));

                return ActionResultType.InvalidArguments;
            });
        }

        [Test(Description = "Should create a playlist from file. It should not be active.")]
        public void CreatePlaylistFromFile_FileNameNotEmptyAndNotActive_ShouldCreatePlaylist()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, false);

                this.AreEqual(ActionResultType.OK, res.ResultType);
                this.NotNull(res.Result);
                this.AreNotEqual(string.Empty, res.Result.Name);
                this.AreNotEqual(string.Empty, res.Result.Id);

                if (res.ResultType != ActionResultType.OK)
                {
                    return res.ResultType;
                }

                var active = Player.PlaylistManager.GetActivePlaylist();
                this.AreEqual(ActionResultType.OK, res.ResultType);
                this.NotNull(active.Result);
                this.AreNotEqual(active.Result.Id, res.Result.Id);

                res.Result.Close(PlaylistCloseFlag.ForceRemove);

                return res.ResultType;
            });
        }

        [Test(Description = "Should create a playlist from file. It should be active.")]
        public void CreatePlaylistFromFile_FileNameNotEmptyAndIsActive_ShouldBeActive()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);

                if (result.ResultType != ActionResultType.OK)
                {
                    return result.ResultType;
                }

                var active = Player.PlaylistManager.GetActivePlaylist();
                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(active.Result);
                this.AreEqual(active.Result.Id, result.Result.Id);

                result.Result.Close(PlaylistCloseFlag.ForceRemove);


                return result.ResultType;
            });
        }

        [Test(Description = "Should set a playlist as a active.")]
        public void SetActivePlaylist_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.CreatePlaylist("New playlist", false);

                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);
                this.AreNotEqual(string.Empty, result.Result.Name);
                this.AreNotEqual(string.Empty, result.Result.Id);

                var result2 = Player.PlaylistManager.SetActivePlaylist(result.Result);
                this.AreEqual(ActionResultType.OK, result2);

                var activePlaylist = Player.PlaylistManager.GetActivePlaylist();
                this.AreEqual(ActionResultType.OK, activePlaylist.ResultType);
                this.AreEqual(activePlaylist.Result.Id, result.Result.Id);

                result.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test(Description = "Create a new playlist and check current count value.")]
        public void GetLoadedPlaylistCount_ShouldReturnCount()
        {
            ExecuteInMainThread(() =>
            {
                var oldCount = Player.PlaylistManager.GetLoadedPlaylistCount();
                var result = Player.PlaylistManager.CreatePlaylist("New playlist", false);

                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);

                var count = Player.PlaylistManager.GetLoadedPlaylistCount();
                this.AreEqual(oldCount + 1, count);

                result.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test]
        public void GetPlayablePlaylist_ShouldReturnPlaylist()
        {
            IAimpPlaylist playlist = null;

            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType);
                playlist = playlistResult.Result;

                return playlistResult.ResultType;
            });

            Thread.Sleep(1000);

            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.GetPlayablePlaylist();

                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);

                playlist.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test]
        public void GetLoadedPlaylist_ShouldReturnPlaylist()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.GetLoadedPlaylist(0);
                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);

                return result.ResultType;
            });
        }

        [Test(Description = "Should return InvalidArgument result")]
        public void GetLoadedPlaylist_WrongIndex_InvalidArgument()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.GetLoadedPlaylist(100);
                this.AreEqual(ActionResultType.InvalidArguments, () => result.ResultType);
                this.Null(() => result.Result);

                return result.ResultType;
            });
        }

        [Test(Description = "Create a new playlist and get it by id.")]
        public void GetLoadedPlaylistById_ShouldReturnPlaylist()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.CreatePlaylist(null, false);
                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);

                var getResult = Player.PlaylistManager.GetLoadedPlaylistById(result.Result.Id);
                this.AreEqual(ActionResultType.OK, getResult.ResultType);
                this.NotNull(getResult.Result);
                this.AreEqual(result.Result.Id, getResult.Result.Id);

                result.Result.Close(PlaylistCloseFlag.ForceRemove);

                return getResult.ResultType;
            });
        }

        [Test(Description = "Create a new playlist and get it by name")]
        public void GetLoadedPlaylistByName_ShouldReturnPlaylist()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.CreatePlaylist("Get by name", false);
                this.AreEqual(ActionResultType.OK, () => result.ResultType);
                this.NotNull(result.Result);

                var getResult = Player.PlaylistManager.GetLoadedPlaylistByName("Get by name");
                this.AreEqual(ActionResultType.OK, () => getResult.ResultType);
                this.NotNull(getResult.Result);
                this.AreEqual(result.Result.Name, () => getResult.Result.Name);

                result.Result.Close(PlaylistCloseFlag.ForceRemove);

                return getResult.ResultType;
            });
        }
    }
}