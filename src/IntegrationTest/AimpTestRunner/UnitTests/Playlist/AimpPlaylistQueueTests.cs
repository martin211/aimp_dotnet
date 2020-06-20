using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playlist
{
    [TestFixture]
    public class AimpPlaylistQueueTests : AimpIntegrationTest
    {
        private IAimpPlaylist _playlist;

        public override void SetUp()
        {
            base.SetUp();

            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.PlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                this.AreEqual(ActionResultType.OK, playlistResult.ResultType, "playlistResult.ResultType");
                this.NotNull(playlistResult.Result, "playlistResult.Result");
                _playlist = playlistResult.Result;

                return playlistResult.ResultType;
            });
        }

        [Test]
        public void GetItemCount_ShouldBeZero()
        {
            ExecuteInMainThread(() =>
            {
                var count = Player.PlaylistManager.PlaylistQueue.GetItemCount();
                this.AreEqual(0, count);

                //_playlist.Close(PlaylistCloseFlag.ForceRemove);

                return ActionResultType.OK;
            });
        }

        [Test]
        public void Delete_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Get playlist item");

                var result = Player.PlaylistManager.PlaylistQueue.Add(getItemResult.Result, true).ResultType;
                this.AreEqual(ActionResultType.OK, result, "Add item to PlaylistQueue");

                result = Player.PlaylistManager.PlaylistQueue.Delete(getItemResult.Result).ResultType;
                this.AreEqual(ActionResultType.OK, result, "Delete item from PlaylistQueue");

                return result;
            });
        }

        [Test]
        public void Add_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);

                this.AreEqual(ActionResultType.OK, getItemResult.ResultType);

                var result = Player.PlaylistManager.PlaylistQueue.Add(getItemResult.Result, true).ResultType;

                this.AreEqual(ActionResultType.OK, result);
                var count = Player.PlaylistManager.PlaylistQueue.GetItemCount();
                this.AreEqual(1, count);

                return result;
            });
        }

        [Test]
        public void AddList_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var getItemsResult1 = _playlist.GetItem(0);
                var getItemsResult2 = _playlist.GetItem(1);

                var result = Player.PlaylistManager.PlaylistQueue.AddList(new List<IAimpPlaylistItem>
                {
                    getItemsResult1.Result,
                    getItemsResult2.Result
                }, true);

                this.AreEqual(ActionResultType.OK, result);
                var count = Player.PlaylistManager.PlaylistQueue.GetItemCount();
                this.AreEqual(2, count);

                return result.ResultType;
            });
        }
    }
}