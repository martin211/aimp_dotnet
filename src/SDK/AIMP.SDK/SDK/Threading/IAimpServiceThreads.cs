//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.Threading
{
    public interface IAimpServiceThreads
    {
        /// <summary>
        /// Cancels the specified task.
        /// </summary>
        /// <param name="taskHandle">The task handle.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);

        /// <summary>
        /// Method provides an ability to wait for task completion.
        /// </summary>
        /// <param name="taskHandle">The task handle.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult WaitFor(UIntPtr taskHandle);

        /// <summary>
        /// Executes the in main thread.
        /// </summary>
        /// <param name="task">The task.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult ExecuteInMainThread(IAimpTask task, AimpServiceThreadPoolType flags);

        /// <summary>
        /// Executes the specified task.
        /// </summary>
        /// <param name="task">The task.</param>
        /// <returns>AimpActionResult&lt;UIntPtr&gt;.</returns>
        AimpActionResult<UIntPtr> ExecuteInThread(IAimpTask task);
    }
}
