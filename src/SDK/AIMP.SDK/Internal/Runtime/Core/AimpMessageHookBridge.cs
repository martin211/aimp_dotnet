using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MessageDispatcher;
using AIMP.SDK.MessageDispatcher;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// Native <c>IAIMPMessageHook</c> over a managed hook.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class AimpMessageHookBridge : IAIMPMessageHookNative
    {
        private readonly IAimpMessageHook _hook;

        public AimpMessageHookBridge(IAimpMessageHook hook)
        {
            _hook = hook ?? throw new ArgumentNullException(nameof(hook));
        }

        [PreserveSig]
        public void CoreMessage(uint message, int param1, IntPtr param2, IntPtr result)
        {
            try
            {
                // Do not write to 'result': AIMP uses it for modal dialogs.
                _hook.CoreMessage((AimpCoreMessageType)message, param1, param2);
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
            }
        }
    }
}