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
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playlist;

public class AimpPlaylistTests : AimpIntegrationTest
{
    public override void TearDown()
    {
        if (_playlist != null)
            ExecuteInMainThread(() =>
            {
                _playlist.Close(PlaylistCloseFlag.ForceRemove);
                _playlist.Dispose();
            });

        base.TearDown();
    }

    private IAimpPlaylist _playlist;

    [Test]
    public void Add_EmptyFileUri_ShouldThrowException()
    {
        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylist(null, false);
            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

            AimpAssert.Throw<ArgumentNullException>(() =>
                playlistResult.Result.Add(string.Empty, PlaylistFlags.NoAsync, PlaylistFilePosition.EndPosition));

            playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
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
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylist(null, false);
            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

            var result = playlistResult.Result.Add(TrackPath1, playlistFlags, position);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

            playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    public void AddList_EmptyStringList_ShouldThrowException()
    {
        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylist(null, false);
            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

            AimpAssert.Throw<ArgumentNullException>(() =>
                playlistResult.Result.AddList(new List<string>(), PlaylistFlags.NoAsync,
                    PlaylistFilePosition.EndPosition));

            playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
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
    public void AddList_NotEmptyStringList_ShouldAddFiles(PlaylistFlags playlistFlags,
        PlaylistFilePosition position)
    {
        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylist(null, false);
            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

            var result = playlistResult.Result.AddList(
                new List<string> { TrackPath1 },
                playlistFlags,
                position);

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

            playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    public void Delete_IncorrectIndex_IncorrectArgument()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile(false);
            var result = pl.Result.Delete(-1).ResultType;
            AimpAssert.AreEqual(ActionResultType.InvalidArguments, result);
        });
    }

    [Test]
    public void Delete_PlayListItem_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile(false);
            var getItemResult = pl.Result.GetItem(0);
            AimpAssert.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");
            AimpAssert.NotNull(getItemResult.Result);

            var result = pl.Result.Delete(getItemResult.Result);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType,
                "Unable delete playlist item from playlist");
        });
    }

    [Test]
    public void Delete_OK()
    {
        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);

            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

            var result = playlistResult.Result.Delete(0);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "result.ResultType");

            playlistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
            playlistResult.Result.Dispose();
        });
    }

    [Test]
    public void DeleteAll_OK()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();

            var result = pl.Result.DeleteAll().ResultType;
            AimpAssert.AreEqual(ActionResultType.OK, result, "result");

            pl.Result.Close(PlaylistCloseFlag.ForceRemove);
            pl.Result.Dispose();
        });
    }

    [Test]
    public void Delete_ByFilter_ShouldExecuteCallback()
    {
        ExecuteInMainThread(() =>
        {
            var executed = false;

            var pl = CreatePlaylistFromFile();
            var result = pl.Result.Delete(PlaylistDeleteFlags.None, "track", (item, o) =>
            {
                executed = true;
                return false;
            }).ResultType;

            AimpAssert.AreEqual(ActionResultType.OK, result);
            AimpAssert.IsTrue(executed);

            pl.Result.Close(PlaylistCloseFlag.ForceRemove);
            pl.Result.Dispose();
        });
    }

    [Test]
    public void GetFiles_All_ShouldAllFiles()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();

            var getFilesResult = pl.Result.GetFiles(PlaylistGetFilesFlag.All);
            AimpAssert.AreEqual(ActionResultType.OK, getFilesResult.ResultType, "result.ResultType");
            AimpAssert.NotNull(getFilesResult.Result);
            AimpAssert.AreEqual(4, getFilesResult.Result.Count);

            pl.Result.Close(PlaylistCloseFlag.ForceRemove);
            pl.Result.Dispose();
        });
    }

    [Test]
    public void GetItemCount_ShouldReturnItemCount()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();
            var items = pl.Result.GetItemCount();
            AimpAssert.AreEqual(4, items);

            pl.Result.Close(PlaylistCloseFlag.ForceRemove);
            pl.Result.Dispose();
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
            var pl = CreatePlaylistFromFile();
            var result = pl.Result.Sort(sort).ResultType;
            AimpAssert.AreEqual(ActionResultType.OK, result);
        });
    }

    [Test]
    public void FocusedItem_ShouldReturnPlaylistItem()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();

            pl.Result.FocusIndex = 1;
            var item = pl.Result.FocusedItem;
            AimpAssert.NotNull(item);
        });
    }

    [Test]
    [Ignore("Need investigation")]
    public void FocusedGroup_ShouldReturnSelectedFocusedGroup()
    {
        ExecuteInMainThread(() =>
        {
            var result = ActionResultType.Fail;
            var pl = CreatePlaylistFromFile();
            pl.Result.FocusIndex = 0;
            var item = pl.Result.FocusedGroup;
            AimpAssert.NotNull(item);
        });
    }

    [Test]
    [Category("groups")]
    public void GetGroupCount_ShouldReturnGroupsCount()
    {
        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
            AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

            var count = playlistResult.Result.GetGroupCount();

            AimpAssert.AreEqual(1, count);
        });
    }

    [Test]
    [Category("groups")]
    public void GetGroup_ShouldReturnGroup()
    {
        ExecuteInMainThread(() =>
        {
            var result = ActionResultType.Fail;
            var pl = CreatePlaylistFromFile();
            var group = GetGroup(pl.Result, 0);

            AimpAssert.IsTrue(group.Result.Name.EndsWith(@"Plugins\AimpTestRunner\resources"));
            AimpAssert.AreEqual(0, group.Result.Index);
            AimpAssert.AreEqual(4, group.Result.Count);
            AimpAssert.IsFalse(group.Result.Selected);
            AimpAssert.IsTrue(group.Result.Expanded);
        });
    }

    [Test]
    [Category("groups")]
    public void Group_Select_ShouldToggleSelect()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();
            var getGroupResult = pl.Result.GetGroup(0);

            AimpAssert.AreEqual(ActionResultType.OK, getGroupResult.ResultType);
            AimpAssert.NotNull(getGroupResult.Result);

            AimpAssert.IsFalse(getGroupResult.Result.Selected);
            getGroupResult.Result.Selected = true;
            AimpAssert.IsTrue(getGroupResult.Result.Selected);
        });
    }

    [Test]
    [Category("groups")]
    public void Group_Expanded_ShouldToggleGroup()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();
            var group = GetGroup(pl.Result, 0);

            AimpAssert.IsTrue(group.Result.Expanded);
            group.Result.Expanded = !group.Result.Expanded;
            AimpAssert.IsFalse(group.Result.Expanded);
        });
    }

    [Test]
    [Category("groups")]
    public void Group_GetItem()
    {
        ExecuteInMainThread(() =>
        {
            var pl = CreatePlaylistFromFile();
            var group = GetGroup(pl.Result, 0);

            var getItemResult = group.Result.GetItem(0);
            AssertOKResult(getItemResult);
        });
    }

    private AimpActionResult<IAimpPlaylist> CreatePlaylistFromFile(bool isActive = true)
    {
        var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, isActive);

        AimpAssert.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
        AimpAssert.NotNull(playlistResult.Result, "playlistResult.Result");

        return playlistResult;
    }

    private AimpActionResult<IAimpPlaylistGroup> GetGroup(IAimpPlaylist playlist, int index)
    {
        var result = playlist.GetGroup(index);
        AssertOKResult(result);
        return result;
    }
}
