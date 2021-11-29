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

using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playlist
{
    [TestFixture]
    public class AimpPlaylistQueueTests : AimpIntegrationTest
    {
        private IAimpPlaylist _playlist;
        private IAimpPlaylistQueue PlaylistQueue => Player.ServicePlaylistManager.PlaylistQueue;

        public override void SetUp()
        {
            base.SetUp();

            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");
                _playlist = playlistResult.Result;
            });
        }

        public override void TearDown()
        {
            base.TearDown();

            ExecuteInMainThread(() =>
            {
                _playlist?.Close(PlaylistCloseFlag.ForceRemove);
            });
        }

        [Test]
        [Order(2)]
        public void Delete_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Failed. Get playlist item");

                var result = PlaylistQueue.Add(getItemResult.Result, true).ResultType;
                this.AreEqual(ActionResultType.OK, result, "Failed. Add item to PlaylistQueue");

                var oldCount = PlaylistQueue.GetItemCount();

                result = PlaylistQueue.Delete(getItemResult.Result).ResultType;
                this.AreEqual(ActionResultType.OK, result, "Failed. Delete item from PlaylistQueue");

                var count = PlaylistQueue.GetItemCount();
                this.AreEqual(oldCount - 1, count);
            });
        }

        [Test]
        public void Add_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);

                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Failed. Get playlist item");

                var oldCount = PlaylistQueue.GetItemCount();

                var result = PlaylistQueue.Add(getItemResult.Result, true).ResultType;

                this.AreEqual(ActionResultType.OK, result, "Failed. Add item to PlaylistQueue");
                var count = PlaylistQueue.GetItemCount();
                this.AreEqual(oldCount + 1, count, "Failed. Get play queue count");

                result = PlaylistQueue.Delete(getItemResult.Result).ResultType;
                this.AreEqual(ActionResultType.OK, result, "Failed. Remove item from queue");
            });
        }

        [Test]
        public void AddList_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var getItemsResult1 = _playlist.GetItem(0);
                var getItemsResult2 = _playlist.GetItem(1);

                var oldCount = PlaylistQueue.GetItemCount();

                var result = PlaylistQueue.AddList(new List<IAimpPlaylistItem>
                {
                    getItemsResult1.Result,
                    getItemsResult2.Result
                }, true);

                this.AreEqual(ActionResultType.OK, result.ResultType);
                var count = PlaylistQueue.GetItemCount();
                this.AreEqual(oldCount + 2, count);
            });
        }

        [Test]
        [Category("Events")]
        public void Suspend_ShouldRaiseEvent()
        {
            ExecuteInMainThread(() =>
            {
                var stateChanged = false;

                PlaylistQueue.StateChanged += queue =>
                {
                    stateChanged = true;
                };

                var getItemResult = _playlist.GetItem(0);
                PlaylistQueue.Add(getItemResult.Result, true);
                PlaylistQueue.IsSuspended = !PlaylistQueue.IsSuspended;
                this.IsTrue(stateChanged);
            });
        }

        [Test]
        [Category("Events")]
        public void ContentChanged_ShouldRaiseEvent()
        {
            ExecuteInMainThread(() =>
            {
                var changed = false;

                PlaylistQueue.ContentChanged += queue =>
                {
                    changed = true;
                };

                var getItemResult = _playlist.GetItem(0);
                var result = PlaylistQueue.Add(getItemResult.Result, true).ResultType;

                this.IsTrue(changed);
            });
        }

        [Test]
        public void Move_PlayListItem_ShouldMoveItemToNewPosition()
        {
            ExecuteInMainThread(() =>
            {
                var getItemsResult1 = _playlist.GetItem(0);
                var getItemsResult2 = _playlist.GetItem(1);

                PlaylistQueue.AddList(new List<IAimpPlaylistItem>
                {
                    getItemsResult1.Result,
                    getItemsResult2.Result
                }, true);

                var result = PlaylistQueue.Move(getItemsResult2.Result, 0).ResultType;
                this.AreEqual(ActionResultType.OK, result, "Failed. Cannot move item");
                var getItemResult = PlaylistQueue.GetItem(0);

                this.AreEqual(getItemsResult2.Result.FileName, getItemResult.Result.FileName);

                PlaylistQueue.Delete(getItemsResult1.Result);
                PlaylistQueue.Delete(getItemsResult2.Result);
            });
        }

        [Test]
        public void Move_FromPositionToPosition_ShouldMoveItemToNewPosition()
        {
            ExecuteInMainThread(() =>
            {
                var getItemsResult1 = _playlist.GetItem(0);
                var getItemsResult2 = _playlist.GetItem(1);

                PlaylistQueue.AddList(new List<IAimpPlaylistItem>
                {
                    getItemsResult1.Result,
                    getItemsResult2.Result
                }, true);

                var result = PlaylistQueue.Move(1, 0).ResultType;
                var getItemResult = PlaylistQueue.GetItem(0);

                this.AreEqual(getItemsResult2.Result.FileName, getItemResult.Result.FileName);

                PlaylistQueue.Delete(getItemsResult1.Result);
                PlaylistQueue.Delete(getItemsResult2.Result);
            });
        }

        [Test]
        public void Move_InvalidIndex_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var getItemsResult1 = _playlist.GetItem(0);
                var getItemsResult2 = _playlist.GetItem(1);

                PlaylistQueue.AddList(new List<IAimpPlaylistItem>
                {
                    getItemsResult1.Result,
                    getItemsResult2.Result
                }, true);

                var result = PlaylistQueue.Move(-1, 0);
                this.AreEqual(ActionResultType.InvalidArguments, result.ResultType);
            });
        }

        [Test]
        public void Move_InvalidTarget_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var getItemsResult1 = _playlist.GetItem(0);
                var getItemsResult2 = _playlist.GetItem(1);

                PlaylistQueue.AddList(new List<IAimpPlaylistItem>
                {
                    getItemsResult1.Result,
                    getItemsResult2.Result
                }, true);

                var result = PlaylistQueue.Move(1, -10);
                this.AreEqual(ActionResultType.InvalidArguments, result.ResultType);
            });
        }
    }
}