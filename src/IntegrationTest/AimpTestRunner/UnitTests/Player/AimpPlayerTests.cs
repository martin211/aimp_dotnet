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
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player
{
    //[TestFixture]
    public class AimpPlayerTests : AimpIntegrationTest
    {
        [Test, Order(1)]
        [Ignore("Not working in integration mode")]
        public void Play_PlayList_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var playlist = Player.PlaylistManager.GetActivePlaylist();
                this.AreEqual(ActionResultType.OK, playlist.ResultType);
                this.NotNull(playlist.Result);

                var result = Player.Play(playlist.Result);
                this.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });

            Assert.AreEqual(AimpPlayerState.Playing, Player.State);
        }

        //[Test, Order(2)]
        public void Pause_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.Pause();
                this.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });

            this.AreEqual(AimpPlayerState.Pause, Player.State);
        }

        //[Test, Order(3)]
        public void Resume_ShouldReturnOK()
        {
            ExecuteInThread(() =>
            {
                var result = Player.Resume();
                Assert.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });

            Assert.AreEqual(AimpPlayerState.Playing, Player.State);
        }

        //[Test, Order(4)]
        public void Stop_ShouldReturnOK()
        {
            ExecuteInThread(() =>
            {
                var result = Player.Stop();
                Assert.AreEqual(ActionResultType.OK, result.ResultType);
                return result.ResultType;
            });

            Assert.AreEqual(AimpPlayerState.Stopped, Player.State);
        }

        //[Test]
        public void StopAfterTrack_ShouldReturnOK()
        {
            var result = Player.StopAfterTrack();
            Assert.AreEqual(ActionResultType.OK, result.ResultType);
        }
    }
}