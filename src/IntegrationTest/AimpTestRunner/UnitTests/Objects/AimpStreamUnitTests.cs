﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System.IO;
using AIMP.SDK;
using AIMP.SDK.Objects;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Objects
{
    [TestFixture]
    public class AimpStreamUnitTests : AimpIntegrationTest
    {
        [Test]
        [Order(1)]
        public void Stream_Write_OK()
        {
            var res = Player.Core.CreateAimpObject<IAimpStream>();
            this.AreEqual(ActionResultType.OK, res.ResultType);

            if (!IsValid)
            {
                return;
            }

            var buf = new byte[]
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 0
            };

            using var stream = res.Result;
            var res2 = stream.Write(buf, buf.Length, out var written);

            this.AreEqual(ActionResultType.OK, res2.ResultType);
            this.AreEqual(buf.Length, written);
        }

        [Test]
        [Order(2)]
        public void Stream_GetSize_OK()
        {
            var res = Player.Core.CreateAimpObject<IAimpStream>();
            this.AreEqual(ActionResultType.OK, res.ResultType);

            if (!IsValid)
            {
                return;
            }

            var buf = new byte[]
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 0
            };

            using var stream = res.Result;
            var res2 = stream.Write(buf, buf.Length, out var written);
            this.AreEqual(ActionResultType.OK, res2.ResultType);
            this.AreEqual(buf.Length, stream.GetSize());
        }

        [Test]
        [Order(3)]
        public void Stream_Read_OK()
        {
            var res = Player.Core.CreateAimpObject<IAimpStream>();
            this.AreEqual(ActionResultType.OK, res.ResultType);

            if (!IsValid)
            {
                return;
            }

            var buf = new byte[]
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 0
            };

            using var stream = res.Result;
            stream.Write(buf, buf.Length, out var written);
            var readBuf = new byte[stream.GetSize()];
            stream.Seek(0, SeekOrigin.Begin);
            int readLength = stream.Read(readBuf, readBuf.Length);
            this.AreEqual(readLength, readBuf.Length);
        }

        [Test]
        [Order(4)]
        public void Stream_Seek_OK()
        {
            var res = Player.Core.CreateAimpObject<IAimpStream>();
            this.AreEqual(ActionResultType.OK, res.ResultType);

            if (!IsValid)
            {
                return;
            }

            var buf = new byte[]
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 0
            };

            using var stream = res.Result;
            stream.Write(buf, buf.Length, out _);

            this.AreEqual(buf.Length, stream.GetPosition());
            stream.Seek(2, SeekOrigin.Begin);
            this.AreEqual(2, stream.GetPosition());
            stream.Seek(-2, SeekOrigin.Current);
            this.AreEqual(0, stream.GetPosition());
            stream.Seek(-2, SeekOrigin.End);
            this.AreEqual(8, stream.GetPosition());
        }

        [Test]
        [Order(10)]
        public void Stream_GetPosition_OK()
        {
            var res = Player.Core.CreateAimpObject<IAimpStream>();
            this.AreEqual(ActionResultType.OK, res.ResultType);

            if (!IsValid)
            {
                return;
            }

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
            this.AreEqual(4, pos);
        }

        [Test]
        [Order(20)]
        public void MemoryStream_GetData_OK()
        {
            var res = Player.Core.CreateAimpObject<IAimpMemoryStream>();
            this.AreEqual(ActionResultType.OK, res.ResultType);
            if (!IsValid)
            {
                return;
            }
            var buf = new byte[]
            {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 0
            };

            using var stream = res.Result;
            stream.Write(buf, buf.Length, out _);
            stream.Seek(0, SeekOrigin.Begin);
            var getDataResult = stream.GetData();
            this.AreEqual(ActionResultType.OK, getDataResult.ResultType);
            this.NotNull(getDataResult.Result);
            this.AreEqual(10, getDataResult.Result.Length);
        }
    }
}
