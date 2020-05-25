using System;
using System.IO;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
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
            var pathToFile = Path.Combine(Player.Core.GetPath(AimpCorePathType.AIMP_CORE_PATH_PLUGINS), "AimpTestRunner", "TestPlaylist.aimppl4");

            ExecuteInMainThread(() =>
            {
                var res = Player.PlaylistManager.CreatePlaylistFromFile(pathToFile, false);

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
            var pathToFile = Path.Combine(Player.Core.GetPath(AimpCorePathType.AIMP_CORE_PATH_PLUGINS), "AimpTestRunner", "TestPlaylist.aimppl4");

            ExecuteInMainThread(() =>
            {
                var result = Player.PlaylistManager.CreatePlaylistFromFile(pathToFile, true);

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
                var result = Player.PlaylistManager.CreatePlaylist("New playlist", false);

                this.AreEqual(ActionResultType.OK, result.ResultType);
                this.NotNull(result.Result);

                var count = Player.PlaylistManager.GetLoadedPlaylistCount();
                this.AreEqual(2, count);

                result.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }
    }
}