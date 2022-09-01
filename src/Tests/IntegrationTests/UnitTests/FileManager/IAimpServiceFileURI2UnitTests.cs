using AIMP.SDK;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager;

[TestFixture(Category = "IAimpServiceFileURI2")]
public class IAimpServiceFileURI2UnitTests : AimpIntegrationTest
{
    [Test]
    public void GetScheme_OK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceFileUri2.GetScheme("test://file.mp3");
            Assert.AreEqual(ActionResultType.OK, result.ResultType);
            Assert.AreEqual("test", result.Result);
        });
    }
}