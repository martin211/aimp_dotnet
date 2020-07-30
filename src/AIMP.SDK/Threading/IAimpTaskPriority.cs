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
    /// <summary>
    /// Enum AimpTaskPriority
    /// </summary>
    public enum AimpTaskPriority
    {
        /// <summary>
        /// The normal
        /// </summary>
        Normal,

        /// <summary>
        /// The low
        /// </summary>
        Low,

        /// <summary>
        /// The hight
        /// </summary>
        Hight
    }

    /// <summary>
    /// This is tool interface that provides an ability to plugin define priority of task.
    /// Interface should be implemented on same to <see cref="IAimpTask" /> level. Priority affects to task position in the
    /// waiting queue (waiting queue is used if all threads from pool are busy) and to priority of working thread.
    /// </summary>
    public interface IAimpTaskPriority
    {
        /// <summary>
        /// Gets the priority.
        /// </summary>
        /// <returns>The <see cref="AimpTaskPriority" /> priority.</returns>
        AimpTaskPriority GetPriority();
    }
}