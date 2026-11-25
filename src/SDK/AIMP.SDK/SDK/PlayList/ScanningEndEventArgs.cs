using System;

namespace AIMP.SDK.PlayList;

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