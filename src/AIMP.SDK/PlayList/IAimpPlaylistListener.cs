using System;

namespace AIMP.SDK.PlayList
{
    public delegate void PlayListChangedHandler(IAimpPlayList sender, PlayListNotifyType notifType);

    public delegate void AimpPlayListHandler(IAimpPlayList sender);

    public delegate void AimpPlayListHandler<in TEventArgs>(IAimpPlayList sender, TEventArgs args) where TEventArgs : EventArgs;

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
        public bool HasChanges { get; private set; }

        public bool Canceled { get; private set; }

        public ScanningEndEventArgs(bool hasChanges, bool canceled)
        {
            HasChanges = hasChanges;
            Canceled = canceled;
        }
    }

    public interface IAimpPlaylistListener
    {
        event AimpPlayListHandler Activated;

        event AimpPlayListHandler Removed;

        event PlayListChangedHandler Changed;

        event AimpPlayListHandler ScanningBegin;

        event AimpPlayListHandler<ScanningProgressEventArgs> ScanningProgress;

        event AimpPlayListHandler<ScanningEndEventArgs> ScanningEnd;
    }
}