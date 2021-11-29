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
using AIMP.SDK.Lyrics;
using AIMP.SDK.Playlist;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Lyrics
{
    [TestFixture]
    public class AimpServiceLyricsTests : AimpIntegrationTest
    {
        [Test]
        public void Get_ShouldRaiseEvent()
        {
            ExecuteInMainThread(() =>
            {
                var lyricsReceive = false;

                Player.ServiceLyrics.LyricsReceive += (lyrics, data) =>
                {
                    lyricsReceive = true;
                };

                var createPlaylistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                var file1 = createPlaylistResult.Result.GetItem(0);
                var result = Player.ServiceLyrics.Get(file1.Result.FileInfo, LyricsFlags.Nocache | LyricsFlags.WaitFor, "UserData");

                this.AreEqual(ActionResultType.OK, result.ResultType, "Unable to get lyric data for file");
                this.IsTrue(lyricsReceive);

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
                var result = Player.ServiceLyrics.Get(file1.Result.FileInfo, LyricsFlags.Nocache | LyricsFlags.WaitFor, "UserData");

                this.AreEqual(ActionResultType.OK, result.ResultType, "Unable to get lyric data for file");

                var r = Player.ServiceLyrics.Cancel(result.Result, LyricsFlags.None);

                this.AreEqual(ActionResultType.OK, r.ResultType, "Unable to cancel lyric task");

                createPlaylistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
            });
        }
    }
}