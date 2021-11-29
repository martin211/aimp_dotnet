using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Playlist;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player
{
    public class AimpServicePlayerTests : AimpIntegrationTest
    {
        private IAimpPlaylist _playlist;

        public override void RunBeforeAnyTests()
        {
            base.RunBeforeAnyTests();

            var pl = Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            _playlist = pl.Result;
        }

        public override void AfterAllTests()
        {
            base.AfterAllTests();

            if (_playlist != null)
            {
                _playlist.Close(PlaylistCloseFlag.ForceRemove);
            }
        }

        [Test]
        public void Volume_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.Volume = 20;
                this.AreEqual(20, Player.ServicePlayer.Volume);
            });
        }

        [Test]
        public void IsMute_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.IsMute = true;
                this.IsTrue(Player.ServicePlayer.IsMute);
            });
        }

        [Test]
        public void Position_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.Position = 10;
                this.AreEqual(10, Player.ServicePlayer.Position);
            });
        }

        [Test]
        public void AutoJumpToNextTrack_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.AutoJumpToNextTrack = true;
                this.IsTrue(Player.ServicePlayer.AutoJumpToNextTrack);
            });
        }

        [Test]
        public void AutoSwitching_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.AutoSwitching = true;
                this.IsTrue(Player.ServicePlayer.AutoSwitching);
            });
        }

        [Test]
        public void AutoSwitchingPauseBetweenTracks_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.AutoSwitchingPauseBetweenTracks = 10;
                this.AreEqual(10, Player.ServicePlayer.AutoSwitchingPauseBetweenTracks);
            });
        }

        [Test]
        public void AutoSwitchingCrossFade_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.AutoSwitchingCrossFade = 10;
                this.AreEqual(10, Player.ServicePlayer.AutoSwitchingCrossFade);
            });
        }

        [Test]
        public void AutoSwitchingFadeIn_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.AutoSwitchingFadeIn = 10;
                this.AreEqual(10, Player.ServicePlayer.AutoSwitchingFadeIn);
            });
        }

        [Test]
        public void AutoSwitchingFadeOut_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.AutoSwitchingFadeOut = 10;
                this.AreEqual(10, Player.ServicePlayer.AutoSwitchingFadeOut);
            });
        }

        [Test]
        public void ManualSwitching_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.ManualSwitching = true;
                this.IsTrue(Player.ServicePlayer.ManualSwitching);
            });
        }

        [Test]
        public void ManualSwitchingCrossFade_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.ManualSwitchingCrossFade = 10;
                this.AreEqual(10, Player.ServicePlayer.ManualSwitchingCrossFade);
            });
        }

        [Test]
        public void ManualSwitchingFadeIn_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.ManualSwitchingFadeIn = 10;
                this.AreEqual(10, Player.ServicePlayer.ManualSwitchingFadeIn);
            });
        }
        
        [Test]
        public void ManualSwitchingFadeOut_OK()
        {
            ExecuteInMainThread(() =>
            {
                Player.ServicePlayer.ManualSwitchingFadeOut = 10;
                this.AreEqual(10, Player.ServicePlayer.ManualSwitchingFadeOut);
            });
        }

        [Test]
        public void GoToNext_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.GoToNext();
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        [Test]
        public void GoToPrev_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.GoToPrev();
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        [Test]
        public void Pause_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.Pause();
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        [Test]
        public void Resume_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.Resume();
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }
        
        [Test]
        public void Stop_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.Stop();
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        [Test]
        public void StopAfterTrack_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.StopAfterTrack();
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        #region Play

        [Test, Ignore("TBD")]
        public void Play_QueueItem_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }
            });
        }

        [Test]
        public void Play_PlaylistItem_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var item = _playlist.GetItem(1);
                
                var result = Player.ServicePlayer.Play(item.Result);
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        [Test]
        public void Play_Playlist_OK()
        {
            ExecuteInMainThreadAndWait(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var result = Player.ServicePlayer.Play(_playlist);
                this.AreEqual(ActionResultType.OK, result.ResultType);
                return new AimpActionResult(result.ResultType);
            });
        }

        [Test]
        public void Play_FileUri_OK()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServicePlayer.Play(PlaylistPath, PlayFlags.FromPlaylist);
                this.AreEqual(ActionResultType.OK, result.ResultType)
                    .Finally(() =>
                    {
                        Player.ServicePlaylistManager.GetActivePlaylist().Result.Close(PlaylistCloseFlag.ForceRemove);
                    });
                return new AimpActionResult(result.ResultType);
            });
        }

        [Test, Ignore("TBD")]
        public void Play_QueueItem_Offset_OK()
        {

        }

        [Test]
        public void Play_PlaylistItem_Offset_OK()
        {
            ExecuteInMainThread(() =>
            {
                if (_playlist == null)
                {
                    Assert.Fail("Playlist not found");
                }

                var item = _playlist.GetItem(1);
                var result = Player.ServicePlayer.Play(item.Result, 100, PlayFlags.FromPlaylist);
                this.AreEqual(ActionResultType.OK, result.ResultType);
            });
        }

        #endregion
    }
}
