using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Player;
using AIMP.SDK.Player.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for <see cref="IAimpExtensionPlayerHook"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class PlayerHookBridge : IAIMPExtensionPlayerHookNative
    {
        private readonly IAimpExtensionPlayerHook _provider;

        public PlayerHookBridge(IAimpExtensionPlayerHook provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        public int OnCheckURL(IntPtr url, out int handled)
        {
            var handledValue = 0;

            var hr = Safe.Run(() =>
            {
                var value = AimpString.Read(url);
                var original = value;
                var result = _provider.OnCheckURL(ref value);

                if (url != IntPtr.Zero && !string.Equals(original, value, StringComparison.Ordinal))
                {
                    using (var target = new AimpString(AimpComHelper.AddRef(url), null))
                    {
                        target.Value = value ?? string.Empty;
                    }
                }

                handledValue = result ? 1 : 0;
                return Safe.S_OK;
            });

            handled = handledValue;
            return hr;
        }
    }
}