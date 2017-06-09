// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Threading
{
    /// <summary>
    /// This service provides an ability to run specified task in main thread of the application.
    /// </summary>
    public interface IAimpServiceSynchronizer
    {
        /// <summary>
        /// Executes the in main thread.
        /// </summary>
        /// <param name="task">The task.</param>
        /// <param name="executeNow">True - the method will not return control until operation has been completed (Not recommended).
        /// Otherwise, task will be queued and executed when main thread is idle. Default value is False.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        AimpActionResult ExecuteInMainThread(IAimpTask task, bool executeNow);
    }
}