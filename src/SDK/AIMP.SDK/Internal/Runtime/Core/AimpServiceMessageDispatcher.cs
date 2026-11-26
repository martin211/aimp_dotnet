using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MessageDispatcher;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceMessageDispatcher"/>.
    /// </summary>
    internal sealed class AimpServiceMessageDispatcher : AimpObjectWrapper, IAimpServiceMessageDispatcher
    {
        private readonly IAIMPServiceMessageDispatcherNative _native;

        private AimpMessageHookBridge _hook;
        private IntPtr _hookPointer;

        public AimpServiceMessageDispatcher(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceMessageDispatcherNative>(borrowedPointer);
        }

        public bool IsExists => _native != null;

        public AimpActionResult Send(AimpCoreMessageType message, int param1, ref IntPtr param2)
        {
            return _native == null
                ? AimpResult.Fail()
                : AimpResult.From(_native.Send((uint)message, param1, param2));
        }

        public AimpActionResult Send(AimpCoreMessageType message)
        {
            return Send(message, 0);
        }

        public AimpActionResult Send(AimpCoreMessageType message, int param1)
        {
            return _native == null
                ? AimpResult.Fail()
                : AimpResult.From(_native.Send((uint)message, param1, IntPtr.Zero));
        }

        public int Register(string message)
        {
            if (string.IsNullOrEmpty(message))
            {
                throw new ArgumentNullException(nameof(message), "Message cannot be empty.");
            }

            if (_native == null)
            {
                return 0;
            }

            var text = AimpString.CreateNative(message ?? string.Empty);

            try
            {
                return (int)_native.Register(text);
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult Hook(IAimpMessageHook hook)
        {
            if (hook == null)
            {
                throw new ArgumentNullException(nameof(hook));
            }

            if (_native == null)
            {
                return AimpResult.Fail();
            }

            _hook = new AimpMessageHookBridge(hook);
            _hookPointer = AimpComHelper.GetPointer(_hook, typeof(IAIMPMessageHookNative));

            return AimpResult.From(_native.Hook(_hookPointer));
        }

        public AimpActionResult Unhook(IAimpMessageHook hook)
        {
            if (_native == null || _hookPointer == IntPtr.Zero)
            {
                return AimpResult.Fail();
            }

            var hr = _native.Unhook(_hookPointer);

            AimpComHelper.Release(_hookPointer);
            _hookPointer = IntPtr.Zero;
            _hook = null;

            return AimpResult.From(hr);
        }

        protected override void OnDispose()
        {
            if (_hookPointer != IntPtr.Zero)
            {
                AimpComHelper.Release(_hookPointer);
                _hookPointer = IntPtr.Zero;
                _hook = null;
            }

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}