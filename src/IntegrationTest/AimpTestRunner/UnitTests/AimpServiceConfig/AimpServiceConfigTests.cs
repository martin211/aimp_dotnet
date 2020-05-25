using AIMP.SDK;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.AimpServiceConfig
{
    [TestFixture]
    public class AimpServiceConfigTests : AimpIntegrationTest
    {
        [Test]
        public void FlushCache_ShouldReturnOK()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceConfig.FlushCache();
                this.AreEqual(ActionResultType.OK, () => result.ResultType);
                return result.ResultType;
            });
        }

        [TestCase(@"integrationTest\Float", (float)1.1), Order(1)]
        [TestCase(@"integrationTest\Int", (int)1)]
        [TestCase(@"integrationTest\Int64", (long)2)]
        [TestCase(@"integrationTest\String", "SomeString")]
        [TestCase(@"integrationTest\Stream", new byte[] { 0x1, 0x2, 0x3})]
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
                    var buf = (byte[]) value;
                    var stream = Player.Core.CreateStream();
                    var r = stream.Write(buf, buf.Length, out var written);

                    this.AreEqual(ActionResultType.OK, () => r);
                    result = Player.ServiceConfig.SetValueAsStream(path, stream);
                }

                this.NotNull(() => result);
                this.AreEqual(ActionResultType.OK, () => result.ResultType);

                return result.ResultType;
            });
        }

        [TestCase(@"integrationTest\Float"), Order(2)]
        [TestCase(@"integrationTest\Int")]
        [TestCase(@"integrationTest\Int64")]
        [TestCase(@"integrationTest\String")]
        [TestCase(@"integrationTest\Stream")]
        public void Get_ShouldReadValues(string path)
        {
            ExecuteInMainThread(() =>
            {
                ActionResultType r = ActionResultType.Fail;

                if (path.EndsWith("Float"))
                {
                    var result = Player.ServiceConfig.GetValueAsFloat(path);
                    this.NotNull(() => result);
                    this.AreEqual((float)1.1, () => result.Result);
                    r = result.ResultType;
                }
                else if (path.EndsWith("Int"))
                {
                    var result = Player.ServiceConfig.GetValueAsInt32(path);
                    this.NotNull(() => result);
                    this.AreEqual(1, () => result.Result);
                    r = result.ResultType;
                }
                else if (path.EndsWith("Int64"))
                {
                    var result = Player.ServiceConfig.GetValueAsInt64(path);
                    this.NotNull(() => result);
                    this.AreEqual(2, () => result.Result);
                    r = result.ResultType;
                }
                else if (path.EndsWith("String"))
                {
                    var result = Player.ServiceConfig.GetValueAsString(path);
                    this.NotNull(() => result);
                    this.AreEqual("SomeString", () => result.Result);
                    r = result.ResultType;
                }
                else if (path.EndsWith("Stream"))
                {
                    var result = Player.ServiceConfig.GetValueAsStream(path);
                    this.NotNull(() => result);
                    this.NotNull(() => result.Result);
                    byte[] buf = new byte[result.Result.GetSize()];
                    result.Result.Read(buf, buf.Length);
                    this.AreEqual(3, buf.Length);
                    r = result.ResultType;
                }

                this.AreEqual(ActionResultType.OK, r);
                return r;
            });
        }

        [TestCase(@"integrationTest\Float"), Order(3)]
        [TestCase(@"integrationTest\Int")]
        [TestCase(@"integrationTest\Int64")]
        [TestCase(@"integrationTest\String")]
        [TestCase(@"integrationTest\Stream")]
        public void Delete_ShouldDeleteSettings(string path)
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceConfig.Delete(path);
                this.NotNull(result);
                this.AreEqual(ActionResultType.OK, () => result.ResultType);
                return result.ResultType;
            });
        }
    }
}