using System;
using System.Linq;
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
                var ex = this.Throw<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush(string.Empty, string.Empty));
                this.True(ex.Message.Contains("Parameter album cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush_EmptyArtist_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = this.Throw<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush("album", string.Empty));
                this.True(ex.Message.Contains("Parameter artist cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.Flush("album", "artist");
                this.AreEqual(ActionResultType.OK, res.ResultType);
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush2_EmptyUri_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = this.Throw<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush2(string.Empty));
                this.True(ex.Message.Contains("Parameter fileUri cannot be empty"));
                return ActionResultType.OK;
            });
        }

        [Test]
        public void Flush2_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.Flush2("some_uri");
                this.AreEqual(ActionResultType.OK, res.ResultType);
                return res.ResultType;
            });
        }

        [Test]
        public void FlushAll_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.FlushAll();
                this.AreEqual(ActionResultType.OK, res.ResultType);
                return res.ResultType;
            });
        }
    }
}