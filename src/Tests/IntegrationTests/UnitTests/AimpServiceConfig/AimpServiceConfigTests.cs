// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.AimpServiceConfig;

[TestFixture(Category = "ServiceConfig")]
public class AimpServiceConfigTests : AimpIntegrationTest
{
    private const string FloatSetting = @"integrationTest\Float";
    private const string IntSetting = @"integrationTest\Int";
    private const string Int64Setting = @"integrationTest\Int64";
    private const string StringSetting = @"integrationTest\String";
    private const string StreamSetting = @"integrationTest\Stream";

    [Test]
    public void FlushCache_ShouldReturnOK()
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceConfig.FlushCache();
            AssertOKResult(result);
        });
    }

    [TestCase(FloatSetting, (float)1.1)]
    [Order(1)]
    [TestCase(IntSetting, 1)]
    [TestCase(Int64Setting, (long)2)]
    [TestCase(StringSetting, "SomeString")]
    [TestCase(StreamSetting, new byte[] { 0x1, 0x2, 0x3 })]
    public void Set_ShouldReturnOK(string path, object value)
    {
        ExecuteInMainThread(() =>
        {
            AimpActionResult result = null;

            if (path.EndsWith("Float"))
            {
                result = Player.ServiceConfig.SetValueAsFloat(path, (float)value);
            }
            else if (path.EndsWith("Int"))
            {
                result = Player.ServiceConfig.SetValueAsInt32(path, (int)value);
            }
            else if (path.EndsWith("Int64"))
            {
                result = Player.ServiceConfig.SetValueAsInt64(path, (long)value);
            }
            else if (path.EndsWith("String"))
            {
                result = Player.ServiceConfig.SetValueAsString(path, value.ToString());
            }
            else if (path.EndsWith("Stream"))
            {
                var buf = (byte[])value;
                var streamResult = Player.Core.CreateStream();
                var r = streamResult.Result.Write(buf, buf.Length, out var written);
                AssertOKResult(r);
                result = Player.ServiceConfig.SetValueAsStream(path, streamResult.Result);
            }

            AssertOKResult(result);
        });
    }

    [TestCase(FloatSetting)]
    [Order(2)]
    [TestCase(IntSetting)]
    [TestCase(Int64Setting)]
    [TestCase(StringSetting)]
    [TestCase(StreamSetting)]
    public void Get_ShouldReadValues(string path)
    {
        ExecuteInMainThread(() =>
        {
            if (path.EndsWith("Float"))
            {
                var result = Player.ServiceConfig.GetValueAsFloat(path);
                AssertOKResult(result);
                AimpAssert.AreEqual((float)1.1, result.Result);
            }
            else if (path.EndsWith("Int"))
            {
                var result = Player.ServiceConfig.GetValueAsInt32(path);
                AssertOKResult(result);
                AimpAssert.AreEqual(1, result.Result);
            }
            else if (path.EndsWith("Int64"))
            {
                var result = Player.ServiceConfig.GetValueAsInt64(path);
                AssertOKResult(result);
                AimpAssert.AreEqual(2, result.Result);
            }
            else if (path.EndsWith("String"))
            {
                var result = Player.ServiceConfig.GetValueAsString(path);
                AssertOKResult(result);
                AimpAssert.AreEqual("SomeString", result.Result);
            }
            else if (path.EndsWith("Stream"))
            {
                var result = Player.ServiceConfig.GetValueAsStream(path);
                AssertOKResult(result);
                var buf = new byte[result.Result.GetSize()];
                result.Result.Read(buf, buf.Length);
                AimpAssert.AreEqual(3, buf.Length);
            }
        });
    }

    [TestCase(FloatSetting)]
    [Order(3)]
    [TestCase(IntSetting)]
    [TestCase(Int64Setting)]
    [TestCase(StringSetting)]
    [TestCase(StreamSetting)]
    public void Delete_ShouldDeleteSettings(string path)
    {
        ExecuteInMainThread(() =>
        {
            var result = Player.ServiceConfig.Delete(path);
            AssertOKResult(result);
        });
    }

    [TestCase(FloatSetting)]
    [Order(4)]
    [TestCase(IntSetting)]
    [TestCase(Int64Setting)]
    [TestCase(StringSetting)]
    [TestCase(StreamSetting)]
    public void Get_NotExist_ShouldReturnDefault(string path)
    {
        ExecuteInMainThread(
            () =>
            {
                if (path.EndsWith("Float"))
                {
                    var result = Player.ServiceConfig.GetValueAsFloat(path);
                    AimpAssert.AreEqual(ActionResultType.Fail, result.ResultType);
                    AimpAssert.AreEqual(default(float), result.Result);
                }
                else if (path.EndsWith("Int"))
                {
                    var result = Player.ServiceConfig.GetValueAsInt32(path);
                    AimpAssert.AreEqual(ActionResultType.Fail, result.ResultType);
                    AimpAssert.AreEqual(default(int), result.Result);
                }
                else if (path.EndsWith("Int64"))
                {
                    var result = Player.ServiceConfig.GetValueAsInt64(path);
                    AimpAssert.AreEqual(ActionResultType.Fail, result.ResultType);
                    AimpAssert.AreEqual(default(long), result.Result);
                }
                else if (path.EndsWith("String"))
                {
                    var result = Player.ServiceConfig.GetValueAsString(path);
                    AimpAssert.AreEqual(ActionResultType.Fail, result.ResultType);
                    AimpAssert.Null(() => result.Result);
                }
                else if (path.EndsWith("Stream"))
                {
                    var result = Player.ServiceConfig.GetValueAsStream(path);
                    AimpAssert.AreEqual(ActionResultType.Fail, result.ResultType);
                    AimpAssert.Null(() => result.Result);
                }
            });
    }
}
