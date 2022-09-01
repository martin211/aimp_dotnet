//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using AIMP.SDK;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.AlbumArtManager;

[TestFixture(Category = "ServiceAlbumArtCache")]
public class AimpServiceAlbumArtCacheTests : AimpIntegrationTest
{
    [Test(Description = "Create and put image to cache")]
    [Order(1)]
    public void Put_OK()
    {
        ExecuteInMainThread(() =>
        {
            var imageContainer = Player.Core.CreateAimpObject<IAimpImageContainer>();

            var img = new Bitmap(ImagePath1);
            using (var stream = new MemoryStream())
            {
                img.Save(stream, ImageFormat.Jpeg);
                imageContainer.Result.SetDataSize(stream.Length);
                var containerData = imageContainer.Result.GetData();
                stream.Read(containerData.Result, 0, (int)stream.Length);
            }

            // TODO: For some reason CreateImage always return unexpected result. Need to contact with AIMP team.
            //var image = imageContainer.Result.CreateImage();
            //var res = image.Result.LoadFromFile(ImagePath1);
            //AimpAssert.AreEqual(ActionResultType.OK, res.ResultType, "Unable to load image to container");

            var putResult = Player.ServiceAlbumArtCache.Put("key1", imageContainer.Result);
            AimpAssert.AreEqual(ActionResultType.OK, putResult.ResultType);
        });
    }

    [Test(Description = "Get cached image")]
    [Order(2)]
    public void Get_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.ServiceAlbumArtCache.Get("key1");
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType, "Unable to get image from cache");
            AimpAssert.NotNull(res.Result);
            AimpAssert.IsTrue(res.Result.GetDataSize() > 0);
        });
    }

    [Test(Description = "Gte cache statistic")]
    [Order(3)]
    public void Stat_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.ServiceAlbumArtCache.Stat();
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType, "Unable to get image from cache");
            AimpAssert.NotNull(res.Result);
            AimpAssert.IsTrue(res.Result.Item1 > 0);
            AimpAssert.IsTrue(res.Result.Item2 > 0);
        });
    }

    [Test(Description = "Remove item from cache by key")]
    [Order(4)]
    public void Remove_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.ServiceAlbumArtCache.Get("key1");
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType, "Unable to get image from cache");
            
            var removeResult = Player.ServiceAlbumArtCache.Remove("key1");
            AimpAssert.AreEqual(ActionResultType.OK, removeResult.ResultType);
        });
    }

    [Test]
    [Order(5)]
    public void Flush_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.ServiceAlbumArtCache.Flush();
            AssertOKResult(res);
        });
    }
}
