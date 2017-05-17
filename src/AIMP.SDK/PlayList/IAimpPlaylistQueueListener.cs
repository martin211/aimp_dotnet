using System;

namespace AIMP.SDK.PlayList
{
    /// <summary>
    /// Interface provides an ability to receive notifications about changes in the queue.
    /// </summary>
    public interface IAimpPlaylistQueueListener
    {
        /// <summary>
        /// Event occurs when content of queue was changed.
        /// </summary>
        event EventHandler ContentChanged;

        /// <summary>
        /// Event occurs when the <see cref="IAimpPlaylistQueue.IsSuspended"/> has been changed.
        /// </summary>
        event EventHandler StateChanged;
    }
}