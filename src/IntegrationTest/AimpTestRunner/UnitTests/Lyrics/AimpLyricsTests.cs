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
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Lyrics
{
    [TestFixture]
    public class AimpLyricsTests : AimpIntegrationTest
    {
        //[Test]
        public void Assign_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                IAimpLyrics lyricsInstance = null;

                Player.ServiceLyrics.LyricsReceive += (lyrics, data) =>
                {
                    lyricsInstance = lyrics;
                };

                var createPlaylistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
                var file1 = createPlaylistResult.Result.GetItem(0);
                var result = Player.ServiceLyrics.Get(file1.Result.FileInfo, LyricsFlags.WaitFor, "UserData");

                this.AreEqual(ActionResultType.OK, result.ResultType, "Unable to get lyric data for file");

                var newLyrics = Player.Core.CreateObject<IAimpLyrics>();

                var r = ((IAimpLyrics)newLyrics.Result).Assign(lyricsInstance);
                this.AreEqual(ActionResultType.OK, r.ResultType, "ResultType", "Cannot assign lyric");
            });
        }
    }
}