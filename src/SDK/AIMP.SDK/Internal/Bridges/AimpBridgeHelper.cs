using System;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Parses a pointer from a managed object or pins it as a native CCW.
    /// </summary>
    internal static class AimpBridgeHelper
    {
        public static IntPtr GetPointer(object instance, Type nativeInterface)
        {
            if (instance == null)
            {
                return IntPtr.Zero;
            }

            if (instance is IAimpNativeObject native)
            {
                return native.NativePointer;
            }

            return AimpComHelper.GetPointer(instance, nativeInterface);
        }

        public static IntPtr GetStreamPointer(IAimpStream stream)
        {
            if (stream == null)
            {
                return IntPtr.Zero;
            }

            if (stream is IAimpNativeObject native)
            {
                return native.NativePointer;
            }

            return AimpComHelper.GetPointer(new AimpStreamBridge(stream), typeof(IAIMPStreamNative));
        }
    }
}