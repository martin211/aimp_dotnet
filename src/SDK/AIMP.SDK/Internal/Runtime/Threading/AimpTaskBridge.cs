using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Threading;
using AIMP.Internal.Runtime.Player;
using AIMP.SDK.Threading;

namespace AIMP.Internal.Runtime.Threading;

/// <summary>
/// Native <c>IAIMPTask</c> over a managed task.
/// </summary>
[ComVisible(true)]
[ClassInterface(ClassInterfaceType.None)]
internal sealed class AimpTaskBridge : IAIMPTaskNative
{
    private readonly IAimpTask _task;

    public AimpTaskBridge(IAimpTask task)
    {
        _task = task ?? throw new ArgumentNullException(nameof(task));
    }

    [PreserveSig]
    public void Execute(IntPtr owner)
    {
        try
        {
            using (var taskOwner = new AimpTaskOwnerWrapper(owner))
            {
                _task.Execute(taskOwner);
            }
        }
        catch (Exception exception)
        {
            AimpLog.Write(exception);
        }
    }
}