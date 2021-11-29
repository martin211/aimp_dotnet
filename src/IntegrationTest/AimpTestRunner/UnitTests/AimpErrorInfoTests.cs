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
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests
{
    [TestFixture]
    public class AimpErrorInfoTests : AimpIntegrationTest
    {
        [Test]
        public void RegisterNewError_ShouldBeOK()
        {
            ExecuteInMainThread(() =>
            {
                var res = Player.Core.CreateObject<IAimpErrorInfo>();
                this.AreEqual(ActionResultType.OK, res.ResultType);
                var err = res.Result as IAimpErrorInfo;

                err.SetInfo(123456, "test", "This is a test error info");

                var info = err.GetInfo();

                this.AreEqual(ActionResultType.OK, info.ResultType);
                this.AreEqual(123456, info.Result.ErrorCode);
                this.AreEqual("test", info.Result.Message);
                this.AreEqual("This is a test error info", info.Result.Details);

                var formatted = err.GetInfoFormatted();

                this.AreEqual(ActionResultType.OK, formatted.ResultType);
                this.IsFalse(string.IsNullOrEmpty(formatted.Result));
            });
        }
    }
}
