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
using AIMP.SDK.FileManager;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.FileManager
{
    [TestFixture]
    public class AimpServiceFileStreamingUnitTests : AimpIntegrationTest
    {
        [Test]
        public void CreateStreamForFile_OK()
        {
            var createStream = Player.ServiceFileStreaming.CreateStreamForFile(TrackPath1, FileStreamingType.Read, -1, -1);
            this.AreEqual(ActionResultType.OK, createStream.ResultType);

            if (!IsValid)
            {
                return;
            }

            this.NotNull(createStream.Result);
            createStream.Result.Dispose();
        }

        [Test]
        [Ignore("TODO")]
        public void GetClipping_OK()
        {
            var createStream = Player.ServiceFileStreaming.CreateStreamForFileUri("");
            this.AreEqual(ActionResultType.OK, createStream.ResultType);

            if (!IsValid)
            {
                return;
            }
        }
    }
}
