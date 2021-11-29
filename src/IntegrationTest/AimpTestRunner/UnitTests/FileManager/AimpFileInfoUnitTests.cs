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

using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.Playlist;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager
{
    [TestFixture]
    public class AimpFileInfoUnitTests : AimpIntegrationTest
    {
        private IAimpPlaylist _playlist;

        public override void SetUp()
        {
            base.SetUp();

            ExecuteInMainThread(() =>
            {
                var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);

                if (playlistResult.ResultType == ActionResultType.OK)
                {
                    _playlist = playlistResult.Result;
                }
                else
                {
                    TestContext.WriteLine($"Cannot create a playlist: {PlaylistPath}");
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
        public void Clone_ShouldReturnObjectClone()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

                this.NotNull(getItemResult.Result);
                this.NotNull(getItemResult.Result.FileInfo);

                var original = getItemResult.Result.FileInfo;
                var clone = original.Clone();

                this.NotNull(clone);

                this.AreEqual(original.Album, clone.Album, fieldName:"Album");
                this.AreEqual(original.AlbumArtist, clone.AlbumArtist, fieldName: "AlbumArtist");
                this.AreEqual(original.AlbumGain, clone.AlbumGain, fieldName: "AlbumGain");
                this.AreEqual(original.AlbumPeak, clone.AlbumPeak, fieldName: "AlbumPeak");
                this.AreEqual(original.Artist, clone.Artist, fieldName: "Artist");
                this.AreEqual(original.BitRate, clone.BitRate, fieldName: "BitRate");
                this.AreEqual(original.BitDepth, clone.BitDepth, fieldName: "BitDepth");
                this.AreEqual(original.BPM, clone.BPM, fieldName: "BPM");
                this.AreEqual(original.Channels, clone.Channels, fieldName: "Channels");
                this.AreEqual(original.Codec, clone.Codec, fieldName: "Codec");
                this.AreEqual(original.Comment, clone.Comment, fieldName: "Comment");
                this.AreEqual(original.Composer, clone.Composer, fieldName: "Composer");
                this.AreEqual(original.CopyRight, clone.CopyRight, fieldName: "CopyRight");
                this.AreEqual(original.CUESheet, clone.CUESheet, fieldName: "CUESheet");
                this.AreEqual(original.Date, clone.Date, fieldName: "Date");
                this.AreEqual(original.DiskNumber, clone.DiskNumber, fieldName: "DiskNumber");
                this.AreEqual(original.DiskTotal, clone.DiskTotal, fieldName: "DiskTotal");
                this.AreEqual(original.Duration, clone.Duration, fieldName: "Duration");
                this.AreEqual(original.FileName, clone.FileName, fieldName: "FileName");
                this.AreEqual(original.FileSize, clone.FileSize, fieldName: "FileSize");
                this.AreEqual(original.Genre, clone.Genre, fieldName: "Genre");
                this.AreEqual(original.Lyrics, clone.Lyrics, fieldName: "Lyrics");
                this.AreEqual(original.Publisher, clone.Publisher, fieldName: "Publisher");
                this.AreEqual(original.SampleRate, clone.SampleRate, fieldName: "SampleRate");
                this.AreEqual(original.Title, clone.Title, fieldName: "Title");
                this.AreEqual(original.TrackGain, clone.TrackGain, fieldName: "TrackGain");
                this.AreEqual(original.TrackNumber, clone.TrackNumber, fieldName: "TrackNumber");
                this.AreEqual(original.TrackPeak, clone.TrackPeak, fieldName: "TrackPeak");
                this.AreEqual(original.TrackTotal, clone.TrackTotal, fieldName: "TrackTotal");
                this.AreEqual(original.URL, clone.URL, fieldName: "URL");
                this.AreEqual(original.AddedDate, clone.AddedDate, fieldName: "AddedDate");
                this.AreEqual(original.LastPlayedDate, clone.LastPlayedDate, fieldName: "LastPlayedDate");
                this.AreEqual(original.Conductor, clone.Conductor, fieldName: "Conductor");
                this.AreEqual(original.Mood, clone.Mood, fieldName: "Mood");
                this.AreEqual(original.Catalog, clone.Catalog, fieldName: "Catalog");
                this.AreEqual(original.Isrc, clone.Isrc, fieldName: "Isrc");
                this.AreEqual(original.Lyricist, clone.Lyricist, fieldName: "Lyricist");
                this.AreEqual(original.EncodedBy, clone.EncodedBy, fieldName: "EncodedBy");
                this.AreEqual(original.Rating, clone.Rating, fieldName: "Rating");
            });
        }

        [Test]
        public void Assign_ShouldAssignDataToNewObject()
        {
            ExecuteInMainThread(() =>
            {
                var getItemResult = _playlist.GetItem(0);
                this.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

                this.NotNull(getItemResult.Result);
                this.NotNull(getItemResult.Result.FileInfo);

                var original = getItemResult.Result.FileInfo;

                var newFileInfo = Player.Core.CreateAimpObject<IAimpFileInfo>();

                Assert.AreEqual(ActionResultType.Handle, ActionResultType.OK);

                var clone = newFileInfo.Result;
                clone.Assign(original);

                this.AreEqual(original.Album, clone.Album, fieldName: "Album");
                this.AreEqual(original.AlbumArtist, clone.AlbumArtist, fieldName: "AlbumArtist");
                this.AreEqual(original.AlbumGain, clone.AlbumGain, fieldName: "AlbumGain");
                this.AreEqual(original.AlbumPeak, clone.AlbumPeak, fieldName: "AlbumPeak");
                this.AreEqual(original.Artist, clone.Artist, fieldName: "Artist");
                this.AreEqual(original.BitRate, clone.BitRate, fieldName: "BitRate");
                this.AreEqual(original.BitDepth, clone.BitDepth, fieldName: "BitDepth");
                this.AreEqual(original.BPM, clone.BPM, fieldName: "BPM");
                this.AreEqual(original.Channels, clone.Channels, fieldName: "Channels");
                this.AreEqual(original.Codec, clone.Codec, fieldName: "Codec");
                this.AreEqual(original.Comment, clone.Comment, fieldName: "Comment");
                this.AreEqual(original.Composer, clone.Composer, fieldName: "Composer");
                this.AreEqual(original.CopyRight, clone.CopyRight, fieldName: "CopyRight");
                this.AreEqual(original.CUESheet, clone.CUESheet, fieldName: "CUESheet");
                this.AreEqual(original.Date, clone.Date, fieldName: "Date");
                this.AreEqual(original.DiskNumber, clone.DiskNumber, fieldName: "DiskNumber");
                this.AreEqual(original.DiskTotal, clone.DiskTotal, fieldName: "DiskTotal");
                this.AreEqual(original.Duration, clone.Duration, fieldName: "Duration");
                this.AreEqual(original.FileName, clone.FileName, fieldName: "FileName");
                this.AreEqual(original.FileSize, clone.FileSize, fieldName: "FileSize");
                this.AreEqual(original.Genre, clone.Genre, fieldName: "Genre");
                this.AreEqual(original.Lyrics, clone.Lyrics, fieldName: "Lyrics");
                this.AreEqual(original.Publisher, clone.Publisher, fieldName: "Publisher");
                this.AreEqual(original.SampleRate, clone.SampleRate, fieldName: "SampleRate");
                this.AreEqual(original.Title, clone.Title, fieldName: "Title");
                this.AreEqual(original.TrackGain, clone.TrackGain, fieldName: "TrackGain");
                this.AreEqual(original.TrackNumber, clone.TrackNumber, fieldName: "TrackNumber");
                this.AreEqual(original.TrackPeak, clone.TrackPeak, fieldName: "TrackPeak");
                this.AreEqual(original.TrackTotal, clone.TrackTotal, fieldName: "TrackTotal");
                this.AreEqual(original.URL, clone.URL, fieldName: "URL");
                this.AreEqual(original.AddedDate, clone.AddedDate, fieldName: "AddedDate");
                this.AreEqual(original.LastPlayedDate, clone.LastPlayedDate, fieldName: "LastPlayedDate");
                this.AreEqual(original.Conductor, clone.Conductor, fieldName: "Conductor");
                this.AreEqual(original.Mood, clone.Mood, fieldName: "Mood");
                this.AreEqual(original.Catalog, clone.Catalog, fieldName: "Catalog");
                this.AreEqual(original.Isrc, clone.Isrc, fieldName: "Isrc");
                this.AreEqual(original.Lyricist, clone.Lyricist, fieldName: "Lyricist");
                this.AreEqual(original.EncodedBy, clone.EncodedBy, fieldName: "EncodedBy");
                this.AreEqual(original.Rating, clone.Rating, fieldName: "Rating");
            });
        }
    }
}
