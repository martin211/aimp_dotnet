using System;

namespace AIMP.SDK.PlayList;

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