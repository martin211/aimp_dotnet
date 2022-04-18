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

using System.IO;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager
{
    [TestFixture(
        Description = "Issue #19. FileInfo rating issue",
        Category = "Issues"
        )]
    [Ignore("Can be run only locally with correct media DB")]
    public class Issue_19 : AimpIntegrationTest
    {
        private IAimpPlaylist _playlist;

        public override void SetUp()
        {
            base.SetUp();

            ExecuteInMainThread(() =>
            {
                var playlistPath = Path.Combine(RootPath, "resources", "issue_19.aimppl4");
                var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(playlistPath, true);

                if (playlistResult.ResultType == ActionResultType.OK)
                {
                    _playlist = playlistResult.Result;
                }
                else
                {
                    TestContext.WriteLine($"Cannot create a playlist: {playlistPath}");
                }
            });
        }

        public override void TearDown()
        {
            base.TearDown();
            if (_playlist != null)
            {
                ExecuteInMainThread(() =>
                {
                    _playlist.Close(PlaylistCloseFlag.ForceRemove);
                });
            }
        }

        [Test]
        [Order(1)]

        public void NoRating_ShouldReturnZero()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(1);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

                this.NotNull(getItemResult.Result);

                this.NotNull(getItemResult.Result.FileInfo);
                var statMark = getItemResult.Result.FileInfo.StatMark;
                var statRating = getItemResult.Result.FileInfo.StatRating;
                var rating = getItemResult.Result.FileInfo.Rating;
                this.AreEqual(0, statMark);
                this.AreEqual(0, statRating);
                this.AreEqual(0, rating);
            });
        }

        public void StatMark_Set_ShouldReturnCorrectValue()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

                this.NotNull(getItemResult.Result);

                this.NotNull(getItemResult.Result.FileInfo);
                getItemResult.Result.FileInfo.StatMark = 1;
                var statMark = getItemResult.Result.FileInfo.StatMark;
                this.AreEqual(1, statMark);
            });
        }
        
        [Test]
        [Order(3)]
        public void Rating_Set_ShouldReturnCorrectValue()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

                this.NotNull(getItemResult.Result);

                this.NotNull(getItemResult.Result.FileInfo);
                getItemResult.Result.FileInfo.Rating = 1;
                var rating = getItemResult.Result.FileInfo.Rating;
                this.AreEqual(1, rating);
            });
        }
    }
}
