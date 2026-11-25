using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Threading;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Threading;

namespace AIMP.Internal.Runtime.Threading;

/// <summary>
/// v1 <see cref="IAimpServiceSynchronizer"/>.
/// </summary>
internal sealed class AimpServiceSynchronizer : AimpObjectWrapper, IAimpServiceSynchronizer
{
    private readonly IAIMPServiceSynchronizerNative _native;

    public AimpServiceSynchronizer(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceSynchronizerNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult ExecuteInMainThread(IAimpTask task, bool executeNow)
    {
        if (_native == null || task == null)
        {
            return AimpResult.Fail();
        }

        var bridge = new AimpTaskBridge(task);
        var pointer = AimpComHelper.GetPointer(bridge, typeof(IAIMPTaskNative));

        return AimpResult.From(_native.ExecuteInMainThread(pointer, executeNow ? 1 : 0));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}