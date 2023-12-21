//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests;

[TestFixture(Category = "ErrorInfo")]
public class AimpErrorInfoTests : AimpIntegrationTest
{
    [Test]
    public void RegisterNewError_ShouldBeOK()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.CreateObject<IAimpErrorInfo>();
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
            var err = res.Result as IAimpErrorInfo;

            err.SetInfo(123456, "test", "This is a test error info");

            var info = err.GetInfo();

            AimpAssert.AreEqual(ActionResultType.OK, info.ResultType);
            AimpAssert.AreEqual(123456, info.Result.ErrorCode);
            AimpAssert.AreEqual("test", info.Result.Message);
            AimpAssert.AreEqual("This is a test error info", info.Result.Details);

            var formatted = err.GetInfoFormatted();

            AimpAssert.AreEqual(ActionResultType.OK, formatted.ResultType);
            AimpAssert.IsFalse(string.IsNullOrEmpty(formatted.Result));
        });
    }
}
