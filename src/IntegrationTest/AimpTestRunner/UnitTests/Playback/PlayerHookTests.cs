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

using System;
using System.Threading;
using AIMP.SDK;
using AIMP.SDK.Playback;
using AIMP.SDK.Playlist;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playback;

public class PlayerHookTests : AimpIntegrationTest
{
    private class AimpExtensionPlayerHook : IAimpExtensionPlayerHook
    {
        private readonly Func<string, bool> _assertAction;

        public AimpExtensionPlayerHook(Func<string, bool> assertAction)
        {
            _assertAction = assertAction;
        }

        public bool OnCheckURL(ref string url)
        {
            return _assertAction(url);
        }
    }

    private class AimpExtensionPlaybackQueue : IAimpExtensionPlaybackQueue
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

    [Test]
    public void RegisterUnregister_IAimpExtensionPlayerHook_OK()
    {
        ExecuteInMainThread(() =>
        {
            var extension = new AimpExtensionPlayerHook(s => { return true; });

            var result = Player.Core.RegisterExtension(extension);
            AssertOKResult(result, "Unable to register a AimpExtensionPlayerHook");

            result = Player.Core.UnregisterExtension(extension);
            AssertOKResult(result, "Unable to unregister a AimpExtensionPlayerHook");
        });
    }

    [Test]
    [Ignore("")]
    public void CheckHook_IAimpExtensionPlayerHook_OK()
    {
        IAimpPlaylist playList = null;
        ExecuteInMainThread(() =>
        {
            var executed = false;
            var extension = new AimpExtensionPlayerHook(s =>
            {
                executed = true;
                AimpAssert.AreEqual(TrackUrl1, s, "fileUrl", "Source file url and hooked url do not match");
                return true;
            });

            var result = Player.Core.RegisterExtension(extension);
            AssertOKResult(result, "Unable to register a AimpExtensionPlayerHook");

            var createPlaylistResult =
                Player.ServicePlaylistManager.CreatePlaylist("AimpExtensionPlayerHook", true);
            AssertOKResult(createPlaylistResult, "Cannot create a playlist from file");
            createPlaylistResult.Result.Add(TrackUrl1, PlaylistFlags.NoCheckFormat,
                PlaylistFilePosition.CurrentPosition);

            if (createPlaylistResult.ResultType == ActionResultType.OK)
            {
                playList = createPlaylistResult.Result;
                var r = Player.ServicePlayer.Play(createPlaylistResult.Result);
            }
        });

        ExecuteAndWait(() =>
        {
            Thread.Sleep(25000);
            return new AimpActionResult(ActionResultType.OK);
        });

        ExecuteInMainThread(() => { playList?.Close(PlaylistCloseFlag.ForceRemove); });
    }

    [Test]
    public void RegisterUnregister_IAimpExtensionPlaybackQueue_OK()
    {
        ExecuteInMainThread(() =>
        {
            var extension = new AimpExtensionPlaybackQueue();
            var result = Player.Core.RegisterExtension(extension);
            AssertOKResult(result, "Unable to register a AimpExtensionPlaybackQueue");

            result = Player.Core.UnregisterExtension(extension);
            AssertOKResult(result, "Unable to unregister a AimpExtensionPlaybackQueue");
        });
    }
}
