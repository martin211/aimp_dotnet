using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Configuration;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceConfig"/>.
    /// </summary>
    internal sealed class AimpConfigService : AimpObjectWrapper, IAimpServiceConfig
    {
        private readonly AimpConfigWrapper _config;

        public AimpConfigService(AimpCore core)
        {
            var native = core.GetService<IAIMPConfigNative>(AimpIids.IAIMPConfig);
            _config = native == null ? null : new AimpConfigWrapper(native, false);
        }

        public bool IsExists => _config != null;

        public AimpActionResult FlushCache()
        {
            return AimpResult.Ok();
        }

        public AimpActionResult Delete(string keyPath)
        {
            return _config?.Delete(keyPath) ?? AimpResult.Fail();
        }

        public AimpActionResult<float> GetValueAsFloat(string keyPath)
        {
            return _config?.GetValueAsFloat(keyPath) ?? AimpResult.Fail<float>();
        }

        public AimpActionResult<int> GetValueAsInt32(string keyPath)
        {
            return _config?.GetValueAsInt32(keyPath) ?? AimpResult.Fail<int>();
        }

        public AimpActionResult<long> GetValueAsInt64(string keyPath)
        {
            return _config?.GetValueAsInt64(keyPath) ?? AimpResult.Fail<long>();
        }

        public AimpActionResult<IAimpStream> GetValueAsStream(string keyPath)
        {
            return _config?.GetValueAsStream(keyPath) ?? AimpResult.Fail<IAimpStream>();
        }

        public AimpActionResult<string> GetValueAsString(string keyPath)
        {
            return _config?.GetValueAsString(keyPath) ?? AimpResult.Fail<string>();
        }

        public AimpActionResult SetValueAsFloat(string keyPath, float value)
        {
            return _config?.SetValueAsFloat(keyPath, value) ?? AimpResult.Fail();
        }

        public AimpActionResult SetValueAsInt32(string keyPath, int value)
        {
            return _config?.SetValueAsInt32(keyPath, value) ?? AimpResult.Fail();
        }

        public AimpActionResult SetValueAsInt64(string keyPath, long value)
        {
            return _config?.SetValueAsInt64(keyPath, value) ?? AimpResult.Fail();
        }

        public AimpActionResult SetValueAsStream(string keyPath, IAimpStream stream)
        {
            return _config?.SetValueAsStream(keyPath, stream) ?? AimpResult.Fail();
        }

        public AimpActionResult SetValueAsString(string keyPath, string value)
        {
            return _config?.SetValueAsString(keyPath, value) ?? AimpResult.Fail();
        }

        protected override void OnDispose()
        {
            _config?.Dispose();
        }
    }
}