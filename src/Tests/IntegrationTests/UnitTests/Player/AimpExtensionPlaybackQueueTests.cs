//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.Player.Extensions;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Playlist.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

public class AimpExtensionPlaybackQueueTests : AimpIntegrationTest
{
    public class AimpExtensionPlaybackQueue : IAimpExtensionPlaybackQueue
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
    }

    private AimpExtensionPlaybackQueue _target;

    [Test]
    [Order(1)]
    public void ShouldRegisterExtension()
    {
        ExecuteInMainThread(() =>
        {
            _target = new AimpExtensionPlaybackQueue();
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
        });
    }
}