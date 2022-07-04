using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.MusicLibrary;

[TestFixture(Category = "ServiceMusicLibrary")]
public class AimpServiceMusicLibraryTests : AimpIntegrationTest
{
    [Test]
    public void GetStorageById_LocalDataStorage_OK()
    {
        ExecuteInMainThread(() =>
        {
            var storageResult = Player.ServiceMusicLibrary.GetStorageById<IAimpLocalDataStorage>();
            AssertOKResult(storageResult);
            AimpAssert.AreEqual("Local files", storageResult.Result.Caption);
            AimpAssert.AreEqual(string.Empty, storageResult.Result.Id);
            AimpAssert.Null(() => storageResult.Result.GroupingPreset);
        });
    }

    [Test]
    public void GetStorageCount_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceMusicLibrary.GetStorageCount();
            AimpAssert.IsTrue(result > 0);
        });
    }

    [Test]
    public void GetActiveStorage_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceMusicLibrary.GetActiveStorage();
            AssertOKResult(result);
        });
    }

    [Test]
    public void GetStorage_CorrectId_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceMusicLibrary.GetStorage(1);
            AssertOKResult(result);
        });
    }

    [Test]
    public void GetStorage_WrongId_Fail()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceMusicLibrary.GetStorage(int.MaxValue);
            AimpAssert.AreEqual(ActionResultType.InvalidArguments, result.ResultType);
        });
    }
}