using System;
using AIMP.SDK;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.AlbumArtManager
{
    [TestFixture]
    public class AimpServiceAlbumArtCacheTests : AimpIntegrationTest
    {
        [Test]
        public void Flush_EmptyAlbum_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = Assert.Throws<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush(string.Empty, string.Empty));
                Assert.True(ex.Message.Contains("Parameter album cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush_EmptyArtist_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = Assert.Throws<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush("album", string.Empty));
                Assert.True(ex.Message.Contains("Parameter artist cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.Flush("album", "artist");
                Assert.AreEqual(ActionResultType.OK, res.ResultType);
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush2_EmptyUri_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = Assert.Throws<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush2(string.Empty));
                Assert.True(ex.Message.Contains("Parameter fileUri cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush2_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.Flush2("some_uri");
                Assert.AreEqual(ActionResultType.OK, res.ResultType);
                return ActionResultType.OK;
            });
        }

        [Test]
        public void FlushAll_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.FlushAll();
                Assert.AreEqual(ActionResultType.OK, res.ResultType);
                return ActionResultType.OK;
            });
        }
    }
}