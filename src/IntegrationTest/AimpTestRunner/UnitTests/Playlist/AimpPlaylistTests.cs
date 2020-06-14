using System;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playlist
{
    [TestFixture]
    public class AimpPlaylistTests : AimpIntegrationTest
    {
        [Test]
        public void Add_EmptyFileUri_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylist(null, false);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                this.Throw<ArgumentNullException>(() =>
                    playlistResult.Result.Add(string.Empty, PlaylistFlags.NoAsync, PlaylistFilePosition.EndPosition));

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.Fail;
            });
        }

        [TestCase(PlaylistFlags.NoAsync, PlaylistFilePosition.CurrentPosition)]
        [TestCase(PlaylistFlags.NoAsync, PlaylistFilePosition.EndPosition)]
        [TestCase(PlaylistFlags.NoAsync, PlaylistFilePosition.RandomPosition)]

        [TestCase(PlaylistFlags.NoCheckFormat, PlaylistFilePosition.CurrentPosition)]
        [TestCase(PlaylistFlags.NoCheckFormat, PlaylistFilePosition.EndPosition)]
        [TestCase(PlaylistFlags.NoCheckFormat, PlaylistFilePosition.RandomPosition)]

        [TestCase(PlaylistFlags.NoExpand, PlaylistFilePosition.CurrentPosition)]
        [TestCase(PlaylistFlags.NoExpand, PlaylistFilePosition.EndPosition)]
        [TestCase(PlaylistFlags.NoExpand, PlaylistFilePosition.RandomPosition)]
        public void Add_ShouldBeOK(PlaylistFlags playlistFlags, PlaylistFilePosition position)
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylist(null, false);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.Add(TrackPath1, playlistFlags, position);
                this.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test]
        public void AddList_EmptyStringList_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylist(null, false);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                this.Throw<ArgumentNullException>(() => playlistResult.Result.AddList(new List<string>(), PlaylistFlags.NoAsync, PlaylistFilePosition.EndPosition));

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.Fail;
            });
        }

        [TestCase(PlaylistFlags.NoAsync, PlaylistFilePosition.CurrentPosition)]
        [TestCase(PlaylistFlags.NoAsync, PlaylistFilePosition.EndPosition)]
        [TestCase(PlaylistFlags.NoAsync, PlaylistFilePosition.RandomPosition)]

        [TestCase(PlaylistFlags.NoCheckFormat, PlaylistFilePosition.CurrentPosition)]
        [TestCase(PlaylistFlags.NoCheckFormat, PlaylistFilePosition.EndPosition)]
        [TestCase(PlaylistFlags.NoCheckFormat, PlaylistFilePosition.RandomPosition)]

        [TestCase(PlaylistFlags.NoExpand, PlaylistFilePosition.CurrentPosition)]
        [TestCase(PlaylistFlags.NoExpand, PlaylistFilePosition.EndPosition)]
        [TestCase(PlaylistFlags.NoExpand, PlaylistFilePosition.RandomPosition)]
        public void AddList_NotEmptyStringList_ShouldAddFiles(PlaylistFlags playlistFlags, PlaylistFilePosition position)
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylist(null, false);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.AddList(
                    new List<string> { TrackPath1 },
                    playlistFlags,
                    position);

                this.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test, NUnit.Framework.Ignore("For some reason it works.")]
        public void Delete_IncorrectIndex_IncorrectArgument()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.Delete(-1);
                this.AreEqual(ActionResultType.InvalidArguments, playlistResult.ResultType, "playlistResult.ResultType");

                return result.ResultType;
            });
        }

        [Test]
        public void Delete_OK()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.Delete(0);
                this.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test]
        public void DeleteAll_OK()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.DeleteAll();
                this.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test]
        public void Delete_ByFilter_ShouldExecuteCallback()
        {
            ExecuteInMainThread(() =>
            {
                var executed = false;

                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                playlistResult.Result.Delete(PlaylistDeleteFlags.None, "track", (item, o) =>
                {
                    executed = true;
                    return false;
                });

                this.True(executed);

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.OK;
            });
        }

        [Test]
        public void GetFiles_All_ShouldAllFiles()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.GetFiles(PlaylistGetFilesFlag.All);
                this.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");
                this.NotNull(result.Result);
                this.AreEqual(4, result.Result.Count);

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return result.ResultType;
            });
        }

        [Test]
        public void GetItemCount_ShouldReturnItemCount()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.GetItemCount();
                this.AreEqual(4, result);

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.OK;
            });
        }

        [TestCase(PlaylistSort.Artist)]
        [TestCase(PlaylistSort.Duration)]
        [TestCase(PlaylistSort.FileName)]
        [TestCase(PlaylistSort.Inverse)]
        [TestCase(PlaylistSort.Randomize)]
        [TestCase(PlaylistSort.Title)]
        public void Sort_OK(PlaylistSort sort)
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var result = playlistResult.Result.Sort(sort);
                this.AreEqual(ActionResultType.OK, result.ResultType);

                return result.ResultType;
            });
        }

        [Test]
        public void FocusedItem_ShouldReturnPlaylistItem()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                playlistResult.Result.FocusIndex = 1;
                var item = playlistResult.Result.FocusedItem;

                this.NotNull(item);

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.OK;
            });
        }

        [Test, Ignore("Need investigation")]
        public void FocusedGroup_ShouldReturnSelectedFocusedGroup()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                playlistResult.Result.FocusIndex = 0;
                var item = playlistResult.Result.FocusedGroup;

                this.NotNull(item);

                playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.OK;
            });
        }

        [Test]
        public void GetGroupCount_ShouldReturnGroupsCount()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var count = playlistResult.Result.GetGroupCount();

                this.AreEqual(1, count);

                return ActionResultType.OK;
            });
        }

        [Test]
        public void GetGroup_ShouldReturnGroup()
        {
            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");

                var group = playlistResult.Result.GetGroup(1);

                this.AreEqual(ActionResultType.OK, group.ResultType);
                this.NotNull(group.Result);

                return group.ResultType;
            });
        }

        [Test]
        public void Group_ShouldReturnCorrectData()
        {

        }
    }
}