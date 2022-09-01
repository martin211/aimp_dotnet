using AIMP.SDK;
using AIMP.SDK.FileManager;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager;

[TestFixture(Category = "IAimpServiceFileURI")]
public class IAimpServiceFileURIUnitTests : AimpIntegrationTest
{
    [Test]
    public void Build_ShouldBuildFileURI()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.Build("test", "1");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual("test:1", result.Result);
        });
    }

    [Test]
    public void Parse_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.Parse("test:1");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual("test", result.Result.Item1);
            AimpAssert.AreEqual("1", result.Result.Item2);
        });
    }

    [TestCase(FileUriFlag.DoubleExt)]
    [TestCase(FileUriFlag.PartExt)]
    public void ChangeFileExt_OK(FileUriFlag flag)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.ChangeFileExt("test:file.mp3", "mp4", flag);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }

    [TestCase(FileUriFlag.DoubleExt)]
    [TestCase(FileUriFlag.PartExt)]
    public void ExtractFileExt_OK(FileUriFlag flag)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.ExtractFileExt("file.mp3", flag);
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual(".mp3", result.Result);
        });
    }

    [Test]
    public void ExtractFileName_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.ExtractFileName("/folder/file.mp3");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual("file.mp3", result.Result);
        });
    }

    [Test]
    public void ExtractFileParentDirName_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.ExtractFileParentDirName("/parent/file.mp3");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual("parent", result.Result);
        });
    }

    [Test]
    public void ExtractFileParentName_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.ExtractFileParentName("/parent/file.mp3");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual("parent", result.Result);
        });
    }

    [Test]
    public void ExtractFilePath_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.ExtractFilePath("/parent/file.mp3");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
            AimpAssert.AreEqual("/parent/", result.Result);
        });
    }

    [Test]
    public void IsURL_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri.IsURL("http://localhost/file.mp3");
            AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        });
    }
}