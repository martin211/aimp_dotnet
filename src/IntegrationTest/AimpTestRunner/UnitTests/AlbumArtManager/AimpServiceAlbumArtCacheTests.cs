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
                this.IsTrue(ex.Message.Contains("Parameter album cannot be empty"));
            });
        }

        [Test]
        public void Flush_EmptyArtist_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = this.Throw<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush("album", string.Empty));
                this.IsTrue(ex.Message.Contains("Parameter artist cannot be empty"));
            });
        }

        [Test]
        public void Flush_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.Flush("album", "artist");
                this.AreEqual(ActionResultType.OK, res.ResultType);
            });
        }

        [Test]
        public void Flush2_EmptyUri_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                var ex = this.Throw<ArgumentNullException>(() => Player.ServiceAlbumArtCache.Flush2(string.Empty));
                this.IsTrue(ex.Message.Contains("Parameter fileUri cannot be empty"));
            });
        }

        [Test]
        public void Flush2_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.Flush2("some_uri");
                this.AreEqual(ActionResultType.OK, res.ResultType);
            });
        }

        [Test]
        public void FlushAll_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.ServiceAlbumArtCache.FlushAll();
                this.AreEqual(ActionResultType.OK, res.ResultType);
            });
        }
    }
}