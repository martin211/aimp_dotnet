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
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests
{
    [TestFixture]
    public class AimpActionResultTests
    {
        [Test]
        public void ShouldSetActionResult()
        {
            var r = new AimpActionResult(ActionResultType.OK);
            Assert.AreEqual(ActionResultType.OK, r.ResultType);
        }

        [Test]
        public void NullResult()
        {
            var r = new AimpActionResult<object>(ActionResultType.OK, null);
            Assert.Null(r.Result);
        }

        [Test]
        public void NotNullResult()
        {
            var r = new AimpActionResult<object>(ActionResultType.OK, "test");
            Assert.NotNull(r.Result);
            Assert.AreEqual(r.Result, "test");
        }
    }
}
