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

using AIMP.SDK;
using AIMP.SDK.Lyrics;
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Lyrics;

[TestFixture(Category = "ServiceLyrics")]
public class AimpServiceLyricsTests : AimpIntegrationTest
{
    [Test]
    public void Get_ShouldRaiseEvent()
    {
        ExecuteInMainThread(() =>
        {
            var lyricsReceive = false;
            var callBackUserData = string.Empty;

            Player.ServiceLyrics.LyricsReceive += (lyrics, data) =>
            {
                lyricsReceive = true;
                callBackUserData = data;
            };

            var createPlaylistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            var file1 = createPlaylistResult.Result.GetItem(0);
            var result = Player.ServiceLyrics.Get(file1.Result.FileInfo, LyricsFlags.Nocache | LyricsFlags.WaitFor,
                "UserData");

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Unable to get lyric data for file");
            AimpAssert.IsTrue(lyricsReceive);
            AimpAssert.AreEqual("UserData", callBackUserData);

            createPlaylistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    public void Cancel_ShouldCancelTask()
    {
        ExecuteInMainThread(() =>
        {
            var createPlaylistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            var file1 = createPlaylistResult.Result.GetItem(0);
            var result = Player.ServiceLyrics.Get(file1.Result.FileInfo, LyricsFlags.Nocache | LyricsFlags.WaitFor,
                "UserData");

            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType, "Unable to get lyric data for file");

            var r = Player.ServiceLyrics.Cancel(result.Result, LyricsFlags.None);

            AimpAssert.AreEqual(ActionResultType.OK, r.ResultType, "Unable to cancel lyric task");

            createPlaylistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }
}
