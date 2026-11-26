using AIMP.SDK.PlayList.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playback;

[TestFixture(Category = "PlaybackQueueService")]
public class AimpPlaybackQueueServiceTests : AimpIntegrationTest
{
    [Test]
    public void GetNextTrack_ReturnItem()
    {
        ExecuteInMainThread(() =>
        {
            var createPlaylistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            var item = Player.ServicePlaybackQueue.GetNextTrack();
            AssertOKResult(item, "Cannot get next track from playback queue");
            AimpAssert.NotNull(item.Result);

            createPlaylistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }

    [Test]
    [Ignore("IAIMPServicePlaybackQueue.GetPrevTrack returns E_NOTIMPL in AIMP 5.40.")]
    public void GetPrevTrack_ReturnItem()
    {
        ExecuteInMainThread(() =>
        {
            var createPlaylistResult = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            Player.ServicePlaybackQueue.GetNextTrack();
            Player.ServicePlaybackQueue.GetNextTrack();
            var item = Player.ServicePlaybackQueue.GetPrevTrack();
            AssertOKResult(item, "Cannot get prev track from playback queue");
            AimpAssert.NotNull(item.Result);

            createPlaylistResult.Result.Close(PlaylistCloseFlag.ForceRemove);
        });
    }
}
