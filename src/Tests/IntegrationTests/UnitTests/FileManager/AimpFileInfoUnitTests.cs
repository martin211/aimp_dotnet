//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager;

[TestFixture(Category = "FileInfoUnit")]
public class AimpFileInfoUnitTests : AimpIntegrationTest
{
    public override void SetUp()
    {
        base.SetUp();

        ExecuteInMainThread(() =>
        {
            var playlistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);

            if (playlistResult.ResultType == ActionResultType.OK)
                _playlist = playlistResult.Result;
            else
                TestContext.WriteLine($"Cannot create a playlist: {PlaylistPath}");
        });
    }

    public override void TearDown()
    {
        base.TearDown();
        if (_playlist != null)
            ExecuteInMainThread(() => { _playlist.Close(PlaylistCloseFlag.ForceRemove); });
    }

    private IAimpPlaylist _playlist;

    [Test]
    public void Clone_ShouldReturnObjectClone()
    {
        ExecuteInMainThread(() =>
        {
            var getItemResult = _playlist.GetItem(0);
            AimpAssert.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

            AimpAssert.NotNull(getItemResult.Result);
            AimpAssert.NotNull(getItemResult.Result.FileInfo);

            var original = getItemResult.Result.FileInfo;
            var clone = original.Clone();

            AimpAssert.NotNull(clone);

            AimpAssert.AreEqual(original.Album, clone.Album, "Album");
            AimpAssert.AreEqual(original.AlbumArtist, clone.AlbumArtist, "AlbumArtist");
            AimpAssert.AreEqual(original.AlbumGain, clone.AlbumGain, "AlbumGain");
            AimpAssert.AreEqual(original.AlbumPeak, clone.AlbumPeak, "AlbumPeak");
            AimpAssert.AreEqual(original.Artist, clone.Artist, "Artist");
            AimpAssert.AreEqual(original.BitRate, clone.BitRate, "BitRate");
            AimpAssert.AreEqual(original.BitDepth, clone.BitDepth, "BitDepth");
            AimpAssert.AreEqual(original.BPM, clone.BPM, "BPM");
            AimpAssert.AreEqual(original.Channels, clone.Channels, "Channels");
            AimpAssert.AreEqual(original.Codec, clone.Codec, "Codec");
            AimpAssert.AreEqual(original.Comment, clone.Comment, "Comment");
            AimpAssert.AreEqual(original.Composer, clone.Composer, "Composer");
            AimpAssert.AreEqual(original.CopyRight, clone.CopyRight, "CopyRight");
            AimpAssert.AreEqual(original.CUESheet, clone.CUESheet, "CUESheet");
            AimpAssert.AreEqual(original.Date, clone.Date, "Date");
            AimpAssert.AreEqual(original.DiskNumber, clone.DiskNumber, "DiskNumber");
            AimpAssert.AreEqual(original.DiskTotal, clone.DiskTotal, "DiskTotal");
            AimpAssert.AreEqual(original.Duration, clone.Duration, "Duration");
            AimpAssert.AreEqual(original.FileName, clone.FileName, "FileName");
            AimpAssert.AreEqual(original.FileSize, clone.FileSize, "FileSize");
            AimpAssert.AreEqual(original.Genre, clone.Genre, "Genre");
            AimpAssert.AreEqual(original.Lyrics, clone.Lyrics, "Lyrics");
            AimpAssert.AreEqual(original.Publisher, clone.Publisher, "Publisher");
            AimpAssert.AreEqual(original.SampleRate, clone.SampleRate, "SampleRate");
            AimpAssert.AreEqual(original.Title, clone.Title, "Title");
            AimpAssert.AreEqual(original.TrackGain, clone.TrackGain, "TrackGain");
            AimpAssert.AreEqual(original.TrackNumber, clone.TrackNumber, "TrackNumber");
            AimpAssert.AreEqual(original.TrackPeak, clone.TrackPeak, "TrackPeak");
            AimpAssert.AreEqual(original.TrackTotal, clone.TrackTotal, "TrackTotal");
            AimpAssert.AreEqual(original.URL, clone.URL, "URL");
            AimpAssert.AreEqual(original.AddedDate, clone.AddedDate, "AddedDate");
            AimpAssert.AreEqual(original.LastPlayedDate, clone.LastPlayedDate, "LastPlayedDate");
            AimpAssert.AreEqual(original.Conductor, clone.Conductor, "Conductor");
            AimpAssert.AreEqual(original.Mood, clone.Mood, "Mood");
            AimpAssert.AreEqual(original.Catalog, clone.Catalog, "Catalog");
            AimpAssert.AreEqual(original.Isrc, clone.Isrc, "Isrc");
            AimpAssert.AreEqual(original.Lyricist, clone.Lyricist, "Lyricist");
            AimpAssert.AreEqual(original.EncodedBy, clone.EncodedBy, "EncodedBy");
            AimpAssert.AreEqual(original.Rating, clone.Rating, "Rating");
        });
    }

    [Test]
    public void Assign_ShouldAssignDataToNewObject()
    {
        ExecuteInMainThread(() =>
        {
            var getItemResult = _playlist.GetItem(0);
            AimpAssert.AreEqual(ActionResultType.OK, getItemResult.ResultType, "Unable to get item from playlist");

            AimpAssert.NotNull(getItemResult.Result);
            AimpAssert.NotNull(getItemResult.Result.FileInfo);

            var original = getItemResult.Result.FileInfo;

            var newFileInfo = Player.Core.CreateAimpObject<IAimpFileInfo>();

            Assert.AreEqual(ActionResultType.OK, newFileInfo.ResultType);

            var clone = newFileInfo.Result;
            clone.Assign(original);

            AimpAssert.AreEqual(original.Album, clone.Album, "Album");
            AimpAssert.AreEqual(original.AlbumArtist, clone.AlbumArtist, "AlbumArtist");
            AimpAssert.AreEqual(original.AlbumGain, clone.AlbumGain, "AlbumGain");
            AimpAssert.AreEqual(original.AlbumPeak, clone.AlbumPeak, "AlbumPeak");
            AimpAssert.AreEqual(original.Artist, clone.Artist, "Artist");
            AimpAssert.AreEqual(original.BitRate, clone.BitRate, "BitRate");
            AimpAssert.AreEqual(original.BitDepth, clone.BitDepth, "BitDepth");
            AimpAssert.AreEqual(original.BPM, clone.BPM, "BPM");
            AimpAssert.AreEqual(original.Channels, clone.Channels, "Channels");
            AimpAssert.AreEqual(original.Codec, clone.Codec, "Codec");
            AimpAssert.AreEqual(original.Comment, clone.Comment, "Comment");
            AimpAssert.AreEqual(original.Composer, clone.Composer, "Composer");
            AimpAssert.AreEqual(original.CopyRight, clone.CopyRight, "CopyRight");
            AimpAssert.AreEqual(original.CUESheet, clone.CUESheet, "CUESheet");
            AimpAssert.AreEqual(original.Date, clone.Date, "Date");
            AimpAssert.AreEqual(original.DiskNumber, clone.DiskNumber, "DiskNumber");
            AimpAssert.AreEqual(original.DiskTotal, clone.DiskTotal, "DiskTotal");
            AimpAssert.AreEqual(original.Duration, clone.Duration, "Duration");
            AimpAssert.AreEqual(original.FileName, clone.FileName, "FileName");
            AimpAssert.AreEqual(original.FileSize, clone.FileSize, "FileSize");
            AimpAssert.AreEqual(original.Genre, clone.Genre, "Genre");
            AimpAssert.AreEqual(original.Lyrics, clone.Lyrics, "Lyrics");
            AimpAssert.AreEqual(original.Publisher, clone.Publisher, "Publisher");
            AimpAssert.AreEqual(original.SampleRate, clone.SampleRate, "SampleRate");
            AimpAssert.AreEqual(original.Title, clone.Title, "Title");
            AimpAssert.AreEqual(original.TrackGain, clone.TrackGain, "TrackGain");
            AimpAssert.AreEqual(original.TrackNumber, clone.TrackNumber, "TrackNumber");
            AimpAssert.AreEqual(original.TrackPeak, clone.TrackPeak, "TrackPeak");
            AimpAssert.AreEqual(original.TrackTotal, clone.TrackTotal, "TrackTotal");
            AimpAssert.AreEqual(original.URL, clone.URL, "URL");
            AimpAssert.AreEqual(original.AddedDate, clone.AddedDate, "AddedDate");
            AimpAssert.AreEqual(original.LastPlayedDate, clone.LastPlayedDate, "LastPlayedDate");
            AimpAssert.AreEqual(original.Conductor, clone.Conductor, "Conductor");
            AimpAssert.AreEqual(original.Mood, clone.Mood, "Mood");
            AimpAssert.AreEqual(original.Catalog, clone.Catalog, "Catalog");
            AimpAssert.AreEqual(original.Isrc, clone.Isrc, "Isrc");
            AimpAssert.AreEqual(original.Lyricist, clone.Lyricist, "Lyricist");
            AimpAssert.AreEqual(original.EncodedBy, clone.EncodedBy, "EncodedBy");
            AimpAssert.AreEqual(original.Rating, clone.Rating, "Rating");
        });
    }
}
