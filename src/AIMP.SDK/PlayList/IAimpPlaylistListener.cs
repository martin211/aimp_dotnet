using System;

namespace AIMP.SDK.Playlist
{
    public delegate void PlayListChangedHandler(IAimpPlaylist sender, PlayListNotifyType notifType);

    public delegate void AimpPlayListHandler(IAimpPlaylist sender);

    public delegate void AimpPlayListHandler<in TEventArgs>(IAimpPlaylist sender, TEventArgs args) where TEventArgs : EventArgs;

    public class ScanningProgressEventArgs : EventArgs
    {
        public double Progress { get; }

        public ScanningProgressEventArgs(double progress)
        {
            Progress = progress;
        }
    }

    public class ScanningEndEventArgs : EventArgs
    {
        public bool HasChanges { get; }

        public bool Canceled { get; }

        public ScanningEndEventArgs(bool hasChanges, bool canceled)
        {
            HasChanges = hasChanges;
            Canceled = canceled;
        }
    }

    /// <summary>
    /// Interface provides an ability to receive notifications about changes in the playlist.
    /// </summary>
    public interface IAimpPlaylistListener
    {
        /// <summary>
        /// Event occurs when playlist is activating.
        /// </summary>
        event AimpPlayListHandler Activated;

        /// <summary>
        /// Event occurs before deleting or unloading.
        /// </summary>
        event AimpPlayListHandler Removed;

        /// <summary>
        /// Occurs when playlist was changed.
        /// </summary>
        event PlayListChangedHandler Changed;

        /// <summary>
        /// Occurs when scanning begin.
        /// </summary>
        event AimpPlayListHandler ScanningBegin;

        /// <summary>
        /// Occurs during scanning progress.
        /// </summary>
        event AimpPlayListHandler<ScanningProgressEventArgs> ScanningProgress;

        /// <summary>
        /// Occurs when scanning end.
        /// </summary>
        event AimpPlayListHandler<ScanningEndEventArgs> ScanningEnd;
    }
}