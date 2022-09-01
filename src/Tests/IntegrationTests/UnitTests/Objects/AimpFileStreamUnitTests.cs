//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Objects;

[TestFixture(Category = "FileStream")]
public class AimpFileStreamUnitTests : AimpIntegrationTest
{
    [Test]
    [Ignore("Not working")]
    public void GetClipping_OK()
    {
        var fileStream =
            Player.ServiceFileStreaming.CreateStreamForFile(TrackPath1, FileStreamingType.Read, -1, -1);
        AimpAssert.AreEqual(ActionResultType.OK, fileStream.ResultType);

        if (!IsValid) return;

        var stream = fileStream.Result as IAimpFileStream;
        AimpAssert.NotNull(stream);

        var clippingResult = stream.GetClipping();
        AimpAssert.AreEqual(ActionResultType.OK, clippingResult.ResultType);

        AimpAssert.IsTrue(clippingResult.Result.Size > 0);
        AimpAssert.IsTrue(clippingResult.Result.Offset > 0);
    }

    [Test]
    [Ignore("Not working")]
    public void GetFileName_OK()
    {
        var fileStream =
            Player.ServiceFileStreaming.CreateStreamForFile(TrackPath1, FileStreamingType.Read, -1, -1);
        AimpAssert.AreEqual(ActionResultType.OK, fileStream.ResultType);

        if (!IsValid) return;

        var stream = fileStream.Result as IAimpFileStream;
        AimpAssert.NotNull(stream);

        var result = stream.GetFileName();
        AimpAssert.AreEqual(ActionResultType.OK, result.ResultType);
        AimpAssert.NotNull(result.Result);
    }
}
