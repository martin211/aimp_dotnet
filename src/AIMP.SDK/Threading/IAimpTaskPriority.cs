﻿namespace AIMP.SDK.Threading
{
    public enum AimpTaskPriority
    {
        Normal,
        Low,
        Hight
    }

    /// <summary>
    /// This is tool interface that provides an ability to plugin define priority of task.
    /// Interface should be implemented on same to <see cref="IAimpTask"/> level. Priority affects to task position in the waiting queue (waiting queue is used if all threads from pool are busy) and to priority of working thread.
    /// </summary>
    public interface IAimpTaskPriority
    {
        /// <summary>
        /// Gets the priority.
        /// </summary>
        /// <returns>The <see cref="AimpTaskPriority"/> priority.</returns>
        AimpTaskPriority GetPriority();
    }
}