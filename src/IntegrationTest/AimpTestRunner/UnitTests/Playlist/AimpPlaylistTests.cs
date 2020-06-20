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
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result, false);

                if (pl != null)
                {
                    result = pl.Delete(-1).ResultType;
                    this.AreEqual(ActionResultType.InvalidArguments, result);
                }

                return result;
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
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    result = pl.DeleteAll().ResultType;
                    this.AreEqual(ActionResultType.OK, result, "result");

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        public void Delete_ByFilter_ShouldExecuteCallback()
        {
            ExecuteInMainThread(() =>
            {
                var executed = false;

                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    result = pl.Delete(PlaylistDeleteFlags.None, "track", (item, o) =>
                    {
                        executed = true;
                        return false;
                    }).ResultType;

                    this.True(executed);

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        public void GetFiles_All_ShouldAllFiles()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    var getFilesResult = pl.GetFiles(PlaylistGetFilesFlag.All);
                    result = getFilesResult.ResultType;
                    this.AreEqual(ActionResultType.OK, getFilesResult.ResultType, "result.ResultType");
                    this.NotNull(getFilesResult.Result);
                    this.AreEqual(4, getFilesResult.Result.Count);

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        public void GetItemCount_ShouldReturnItemCount()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {

                    var items = pl.GetItemCount();
                    this.AreEqual(4, items);

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
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
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    result = pl.Sort(sort).ResultType;
                    this.AreEqual(ActionResultType.OK, result);
                }

                return result;
            });
        }

        [Test]
        public void FocusedItem_ShouldReturnPlaylistItem()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    pl.FocusIndex = 1;
                    var item = pl.FocusedItem;
                    this.NotNull(item);

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test, Ignore("Need investigation")]
        public void FocusedGroup_ShouldReturnSelectedFocusedGroup()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);
                if (pl != null)
                {
                    pl.FocusIndex = 0;
                    var item = pl.FocusedGroup;

                    this.NotNull(item);

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        [Category("groups")]
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
        [Category("groups")]
        public void GetGroup_ShouldReturnGroup()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);
                if (pl != null)
                {
                    var group = GetGroup(pl, 0, ref result);

                    if (group != null)
                    {
                        this.True(group.Name.EndsWith(@"Plugins\AimpTestRunner\resources"));
                        this.AreEqual(0, group.Index);
                        this.AreEqual(4, group.Count);
                        this.False(group.Selected);
                        this.True(group.Expanded);
                    }

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        [Category("groups")]
        public void Group_Select_ShouldToggleSelect()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);
                if (pl != null)
                {
                    var getGroupResult = pl.GetGroup(0);

                    this.AreEqual(ActionResultType.OK, getGroupResult.ResultType);
                    this.NotNull(getGroupResult.Result);

                    this.False(getGroupResult.Result.Selected);
                    getGroupResult.Result.Selected = true;
                    this.True(getGroupResult.Result.Selected);

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        [Category("groups")]
        public void Group_Expanded_ShouldToggleGroup()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    var group = GetGroup(pl, 0, ref result);

                    if (group != null)
                    {
                        this.True(group.Expanded);
                        group.Expanded = !group.Expanded;
                        this.False(group.Expanded);
                    }

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        [Test]
        [Category("groups")]
        public void Group_GetItem()
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType result = ActionResultType.Fail;
                var pl = CreatePlaylistFromFile(ref result);

                if (pl != null)
                {
                    var group = GetGroup(pl, 0, ref result);

                    if (group != null)
                    {
                        var getItemResult = group.GetItem(0);
                        this.AreEqual(ActionResultType.OK, getItemResult.ResultType);
                        this.NotNull(getItemResult.Result);
                    }

                    pl.Close(PlaylistCloseFlag.ForceRemove);
                }

                return result;
            });
        }

        private IAimpPlaylist CreatePlaylistFromFile(ref ActionResultType result, bool isActive = true)
        {
            var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, isActive);

            this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            this.NotNull(playlistResult.Result, "playlistResult.Result");

            result = playlistResult.ResultType;

            return playlistResult.ResultType == ActionResultType.OK
                ? playlistResult.Result
                : default;
        }

        private IAimpPlaylistGroup GetGroup(IAimpPlaylist playlist, int index, ref ActionResultType result)
        {
            var getGroupResult = playlist.GetGroup(index);
            this.AreEqual(ActionResultType.OK, getGroupResult.ResultType);
            this.NotNull(getGroupResult.Result);

            result = getGroupResult.ResultType;

            return getGroupResult.ResultType == ActionResultType.OK
                ? getGroupResult.Result
                : default;
        }
    }
}