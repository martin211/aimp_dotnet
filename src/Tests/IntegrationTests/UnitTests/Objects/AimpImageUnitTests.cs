//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Drawing;
using System.IO;
using AIMP.SDK;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests;

[TestFixture(Category = "ImageUnit")]
public class AimpImageUnitTests : AimpIntegrationTest
{
    public override void RunBeforeAnyTests()
    {
        base.RunBeforeAnyTests();
        Image1 = Path.Combine(RootPath, "resources", "img1.jpg");
    }

    private string Image1;

    [Test]
    [Order(1)]
    public void Create_ShouldReturnNewObject()
    {
        var res = Player.Core.CreateObject<IAimpImage>();
        AssertOKResult(res);
    }

    [Test]
    [Order(2)]
    public void LoadFromFile_NotEmptyPath_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpImage>();
        AssertOKResult(res);

        var img = res.Result;
        var loadFromFileResult = img.LoadFromFile(Image1);
        AimpAssert.AreEqual(ActionResultType.OK, loadFromFileResult.ResultType);
        AimpAssert.IsTrue(img.Size != PointF.Empty);
    }

    [Test]
    public void LoadFromFile_EmptyPath_ShouldThrowException()
    {
        var res = Player.Core.CreateAimpObject<IAimpImage>();
        AssertOKResult(res);

        var img = res.Result;
        var exception = AimpAssert.Throw<ArgumentNullException>(() => img.LoadFromFile(string.Empty));
        AimpAssert.IsTrue(exception.Message.Contains("fileName cannot be empty"));
    }

    [TestCase("img1.bmp", AimpImageFormat.BPM)]
    [TestCase("img1.gif", AimpImageFormat.GIF)]
    [TestCase("img1.jpg", AimpImageFormat.JPG)]
    [TestCase("img1.png", AimpImageFormat.PNG)]
    [Ignore("Not working")]
    public void SaveToFile_OK(string fileName, AimpImageFormat format)
    {
        var res = Player.Core.CreateAimpObject<IAimpImage>();
        AssertOKResult(res);

        var file = Path.Combine(TmpPath, fileName);

        var img = res.Result;
        img.LoadFromFile(Image1);

        var saveResult = img.SaveToFile(file, format);
        AimpAssert.AreEqual(ActionResultType.OK, saveResult.ResultType,
            $"Unable save file to {file}, format {format}");
    }

    [Test]
    [Ignore("Clone not working, AccessViolationException")]
    public void Clone_OK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.CreateAimpObject<IAimpImage>();
            AssertOKResult(res);

            res.Result.LoadFromFile(Image1);
            var cloneResult = res.Result.Clone();
            AimpAssert.AreEqual(ActionResultType.OK, cloneResult.ResultType);
            AimpAssert.NotNull(cloneResult.Result);
        });
    }

    [Test]
    public void Resize_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpImage>();
        AssertOKResult(res);

        res.Result.LoadFromFile(Image1);
        var resizeResult = res.Result.Resize(100, 100);
        AimpAssert.AreEqual(ActionResultType.OK, resizeResult.ResultType);
    }
}
