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

using System;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// Delegate PlayListChangedHandler
    /// </summary>
    /// <param name="sender">The sender.</param>
    /// <param name="notifType">Type of the notif.</param>
    public delegate void PlayListChangedHandler(IAimpPlaylist sender, PlaylistNotifyType notifType);

    /// <summary>
    /// Delegate AimpPlayListHandler
    /// </summary>
    /// <param name="sender">The sender.</param>
    public delegate void AimpPlayListHandler(IAimpPlaylist sender);

    /// <summary>
    /// Delegate AimpPlayListHandler
    /// </summary>
    /// <typeparam name="TEventArgs">The type of the t event arguments.</typeparam>
    /// <param name="sender">The sender.</param>
    /// <param name="args">The <see cref="TEventArgs" /> instance containing the event data.</param>
    public delegate void AimpPlayListHandler<in TEventArgs>(IAimpPlaylist sender, TEventArgs args)
        where TEventArgs : EventArgs;

    /// <summary>
    /// Class ScanningProgressEventArgs.
    /// Implements the <see cref="System.EventArgs" />
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class ScanningProgressEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ScanningProgressEventArgs" /> class.
        /// </summary>
        /// <param name="progress">The progress.</param>
        public ScanningProgressEventArgs(double progress)
        {
            Progress = progress;
        }

        /// <summary>
        /// Gets the progress.
        /// </summary>
        /// <value>The progress.</value>
        public double Progress { get; }
    }

    /// <summary>
    /// Class ScanningEndEventArgs.
    /// Implements the <see cref="System.EventArgs" />
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class ScanningEndEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ScanningEndEventArgs" /> class.
        /// </summary>
        /// <param name="hasChanges">if set to <c>true</c> [has changes].</param>
        /// <param name="canceled">if set to <c>true</c> [canceled].</param>
        public ScanningEndEventArgs(bool hasChanges, bool canceled)
        {
            HasChanges = hasChanges;
            Canceled = canceled;
        }

        /// <summary>
        /// Gets a value indicating whether this instance has changes.
        /// </summary>
        /// <value><c>true</c> if this instance has changes; otherwise, <c>false</c>.</value>
        public bool HasChanges { get; }

        /// <summary>
        /// Gets a value indicating whether this <see cref="ScanningEndEventArgs" /> is canceled.
        /// </summary>
        /// <value><c>true</c> if canceled; otherwise, <c>false</c>.</value>
        public bool Canceled { get; }
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