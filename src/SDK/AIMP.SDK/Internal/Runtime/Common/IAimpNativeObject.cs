using System;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// Wrapper that owns a native interface pointer.
/// </summary>
internal interface IAimpNativeObject
{
    IntPtr NativePointer { get; }
}