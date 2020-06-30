// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Threading
{
    using System;

    public enum AimpServiceThreadPoolType
    {
        None = 0,

        /// <summary>
        /// the method will not return control until operation has been completed if this flag is used.
        /// </summary>
        AIMP_SERVICE_THREADPOOL_FLAGS_WAITFOR
    }

    /// <summary>
    /// Service provides an access to thread pool and allows to plugin add a task to asynchronous execution.
    /// Note that count of running threads at same time is limited. All tasks will be added to special queue and will be executed when one of the threads is idle.
    /// <para>
    /// Make sure that all your tasks is completed or canceled during plugin finalization.
    /// </para>
    /// </summary>
    public interface IAimpServiceThreadPool : IAimpService
    {
        /// <summary>
        /// Cancels the specified task.
        /// </summary>
        /// <param name="taskhandle">The task handle.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        ActionResultType Cancel(UIntPtr taskhandle, AimpServiceThreadPoolType flags);

        /// <summary>
        /// Executes the specified task.
        /// </summary>
        /// <param name="task">The task.</param>
        /// <param name="taskHandle">The task handle.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        ActionResultType Execute(IAimpTask task, out UIntPtr taskHandle);

        /// <summary>
        /// Method provides an ability to wait for task completion.
        /// </summary>
        /// <param name="taskHandle">The task handle.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        ActionResultType WaitFor(UIntPtr taskHandle);
    }
}