//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.IO;
using AIMP.SDK;
using AIMP.SDK.Objects;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Objects;

[TestFixture(Category = "Stream")]
public class AimpStreamUnitTests : AimpIntegrationTest
{
    [Test]
    [Order(1)]
    public void Stream_Write_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpStream>();
        AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

        if (!IsValid) return;

        var buf = new byte[]
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 0
        };

        using var stream = res.Result;
        var res2 = stream.Write(buf, buf.Length, out var written);

        AimpAssert.AreEqual(ActionResultType.OK, res2.ResultType);
        AimpAssert.AreEqual(buf.Length, written);
    }

    [Test]
    [Order(2)]
    public void Stream_GetSize_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpStream>();
        AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

        if (!IsValid) return;

        var buf = new byte[]
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 0
        };

        using var stream = res.Result;
        var res2 = stream.Write(buf, buf.Length, out var written);
        AimpAssert.AreEqual(ActionResultType.OK, res2.ResultType);
        AimpAssert.AreEqual(buf.Length, stream.GetSize());
    }

    [Test]
    [Order(3)]
    public void Stream_Read_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpStream>();
        AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

        if (!IsValid) return;

        var buf = new byte[]
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 0
        };

        using var stream = res.Result;
        stream.Write(buf, buf.Length, out var written);
        var readBuf = new byte[stream.GetSize()];
        stream.Seek(0, SeekOrigin.Begin);
        var readLength = stream.Read(readBuf, readBuf.Length);
        AimpAssert.AreEqual(readLength, readBuf.Length);
    }

    [Test]
    [Order(4)]
    public void Stream_Seek_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpStream>();
        AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

        if (!IsValid) return;

        var buf = new byte[]
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 0
        };

        using var stream = res.Result;
        stream.Write(buf, buf.Length, out _);

        AimpAssert.AreEqual(buf.Length, stream.GetPosition());
        stream.Seek(2, SeekOrigin.Begin);
        AimpAssert.AreEqual(2, stream.GetPosition());
        stream.Seek(-2, SeekOrigin.Current);
        AimpAssert.AreEqual(0, stream.GetPosition());
        stream.Seek(-2, SeekOrigin.End);
        AimpAssert.AreEqual(8, stream.GetPosition());
    }

    [Test]
    [Order(10)]
    public void Stream_GetPosition_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpStream>();
        AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);

        if (!IsValid) return;

        var buf = new byte[]
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 0
        };

        using var stream = res.Result;
        stream.Write(buf, buf.Length, out _);
        var readBuf = new byte[stream.GetSize()];
        stream.Seek(0, SeekOrigin.Begin);
        stream.Read(readBuf, 4);

        var pos = stream.GetPosition();
        AimpAssert.AreEqual(4, pos);
    }

    [Test]
    [Order(20)]
    public void MemoryStream_GetData_OK()
    {
        var res = Player.Core.CreateAimpObject<IAimpMemoryStream>();
        AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
        if (!IsValid) return;
        var buf = new byte[]
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 0
        };

        using var stream = res.Result;
        stream.Write(buf, buf.Length, out _);
        stream.Seek(0, SeekOrigin.Begin);
        var getDataResult = stream.GetData();
        AimpAssert.AreEqual(ActionResultType.OK, getDataResult.ResultType);
        AimpAssert.NotNull(getDataResult.Result);
        AimpAssert.AreEqual(10, getDataResult.Result.Length);
    }
}
