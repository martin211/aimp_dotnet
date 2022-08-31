using AIMP.SDK;
using AIMP.SDK.Player.Extensions;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

public class AimpExtensionPlaybackQueue2Tests : AimpIntegrationTest
{
    public class AimpExtensionPlaybackQueue2 : IAimpExtensionPlaybackQueue2
    {
        public AimpActionResult GetNext(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult GetPrev(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public void OnSelect(IAimpPlaylistItem item, IAimpPlaybackQueueItem queueItem)
        {
            
        }

        public AimpActionResult<PlaybackQueueInfo> GetInfo(IAimpPlaylistItem item)
        {
            return new AimpActionResult<PlaybackQueueInfo>(ActionResultType.Fail);
        }
    }

    private AimpExtensionPlaybackQueue2 _target;

    [Test]
    [Order(1)]
    public void ShouldRegisterExtension()
    {
        ExecuteInMainThread(() =>
        {
            _target = new AimpExtensionPlaybackQueue2();
            var res = Player.Core.RegisterExtension(_target);

            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
        });
    }

    [Test]
    public void ShouldUnregisterExtension()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.UnregisterExtension(_target);
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
            _target = null;
        });
    }
}