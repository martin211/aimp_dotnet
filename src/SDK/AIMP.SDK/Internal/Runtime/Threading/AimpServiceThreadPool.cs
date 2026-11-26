using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Threading;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Threading;

namespace AIMP.Internal.Runtime.Threading;

/// <summary>
/// v1 <see cref="IAimpServiceThreadPool"/>.
/// </summary>
internal sealed class AimpServiceThreadPool : AimpObjectWrapper, IAimpServiceThreadPool
{
    private readonly IAIMPServiceThreadPoolNative _native;
    private readonly Dictionary<ulong, IntPtr> _tasks = new Dictionary<ulong, IntPtr>();

    public AimpServiceThreadPool(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceThreadPoolNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<UIntPtr> Execute(IAimpTask task)
    {
        if (_native == null || task == null)
        {
            return AimpResult.Fail<UIntPtr>();
        }

        var bridge = new AimpTaskBridge(task);
        var pointer = AimpComHelper.GetPointer(bridge, typeof(IAIMPTaskNative));
        var hr = _native.Execute(pointer, out var handle);

        if (hr < 0)
        {
            AimpComHelper.Release(pointer);
            return AimpResult.Fail<UIntPtr>();
        }

        _tasks[handle.ToUInt64()] = pointer;
        return AimpResult.Ok(handle);
    }

    public AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var result = AimpResult.From(_native.Cancel(taskHandle, (uint)flags));
        Release(taskHandle);
        return result;
    }

    public AimpActionResult WaitFor(UIntPtr taskHandle)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var result = AimpResult.From(_native.WaitFor(taskHandle));
        Release(taskHandle);
        return result;
    }

    private void Release(UIntPtr handle)
    {
        if (_tasks.TryGetValue(handle.ToUInt64(), out var pointer))
        {
            _tasks.Remove(handle.ToUInt64());
            AimpComHelper.Release(pointer);
        }
    }

    protected override void OnDispose()
    {
        foreach (var pointer in _tasks.Values)
        {
            AimpComHelper.Release(pointer);
        }

        _tasks.Clear();

        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}