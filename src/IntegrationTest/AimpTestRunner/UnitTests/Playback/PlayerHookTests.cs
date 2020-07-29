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

using System;
using System.Threading;
using AIMP.SDK;
using AIMP.SDK.Playback;
using AIMP.SDK.Playlist;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Playback
{
    [TestFixture]
    public class PlayerHookTests : AimpIntegrationTest
    {
        private class AimpExtensionPlayerHook : IAimpExtensionPlayerHook
        {
            private Func<string, bool> _assertAction;

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
            public bool GetNext(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
            {
                return true;
            }

            public bool GetPrev(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
            {
                return true;
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
                var extension = new AimpExtensionPlayerHook(s =>
                {
                    return true;
                });

                var result = Player.Core.RegisterExtension(extension);
                AssertOKResult(result.ResultType, "Unable to register a AimpExtensionPlayerHook");

                result = Player.Core.UnregisterExtension(extension);
                AssertOKResult(result.ResultType, "Unable to unregister a AimpExtensionPlayerHook");
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
                    this.AreEqual(TrackUrl1, s, "fileUrl", "Source file url and hooked url do not match");
                    return true;
                });

                var result = Player.Core.RegisterExtension(extension);
                AssertOKResult(result.ResultType, "Unable to register a AimpExtensionPlayerHook");

                var createPlaylistResult = Player.PlaylistManager.CreatePlaylist("AimpExtensionPlayerHook", true);
                AssertOKResult(createPlaylistResult.ResultType, "Cannot create a playlist from file");
                createPlaylistResult.Result.Add(TrackUrl1, PlaylistFlags.NoCheckFormat, PlaylistFilePosition.CurrentPosition);

                if (createPlaylistResult.ResultType == ActionResultType.OK)
                {
                    playList = createPlaylistResult.Result;
                    var r = Player.Play(createPlaylistResult.Result);
                }
            });

            ExecuteAndWait(() =>
            {
                Thread.Sleep(25000);
            });

            ExecuteInMainThread(() =>
            {
                playList?.Close(PlaylistCloseFlag.ForceRemove);
            });
        }

        [Test]
        public void RegisterUnregister_IAimpExtensionPlaybackQueue_OK()
        {
            ExecuteInMainThread(() =>
            {
                var extension = new AimpExtensionPlaybackQueue();
                var result = Player.Core.RegisterExtension(extension);
                AssertOKResult(result.ResultType, "Unable to register a AimpExtensionPlaybackQueue");

                result = Player.Core.UnregisterExtension(extension);
                AssertOKResult(result.ResultType, "Unable to unregister a AimpExtensionPlaybackQueue");
            });
        }
    }
}