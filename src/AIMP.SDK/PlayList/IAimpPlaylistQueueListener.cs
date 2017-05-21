﻿namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// Playlist queue listener handler.
    /// </summary>
    /// <param name="playlistQueue">The playlist queue.</param>
    public delegate void AimpPlaylistQueueListenerHandler(IAimpPlaylistQueue playlistQueue);

    /// <summary>
    /// Interface provides an ability to receive notifications about changes in the queue.
    /// </summary>
    public interface IAimpPlaylistQueueListener
    {
        /// <summary>
        /// Event occurs when content of queue was changed.
        /// </summary>
        event AimpPlaylistQueueListenerHandler ContentChanged;

        /// <summary>
        /// Event occurs when the <see cref="IAimpPlaylistQueue.IsSuspended"/> has been changed.
        /// </summary>
        event AimpPlaylistQueueListenerHandler StateChanged;
    }
}