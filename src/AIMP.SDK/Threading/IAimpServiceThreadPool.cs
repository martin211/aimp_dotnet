namespace AIMP.SDK.Threading
{
    using System;

    public enum AimpServiceThreadPoolType
    {
        None = 0,
        AIMP_SERVICE_THREADPOOL_FLAGS_WAITFOR
    }

    public interface IAimpServiceThreadPool
    {
        AimpActionResult Cancel(UIntPtr taskhandle, AimpServiceThreadPoolType flags);

        AimpActionResult Execute(IAimpTask task, out UIntPtr taskHandle);

        AimpActionResult WaitFor(UIntPtr taskHandle);
    }
}