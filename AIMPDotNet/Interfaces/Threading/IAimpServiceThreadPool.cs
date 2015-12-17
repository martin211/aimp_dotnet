namespace AIMP.SDK.Services.Threading
{
    using System;

    public enum AimpServiceThreadPoolType
    {
        None = 0,
        AIMP_SERVICE_THREADPOOL_FLAGS_WAITFOR
    }

    public interface IAimpServiceThreadPool
    {
        AimpActionResult Cancel(IntPtr taskhandle, AimpServiceThreadPoolType flags);

        AimpActionResult Execute(IAimpAsyncTask task, out IntPtr taskHandle);

        AimpActionResult WaitFor(IntPtr taskHandle);
    }
}