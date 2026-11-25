using System.Collections;
using AIMP.SDK.Threading;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Provides data for smart-playlist.
/// </summary>
public interface IAimpPlaylistPreimageDataProvider
{
    /// <summary>
    /// Gets the files.
    /// </summary>
    /// <param name="owner">The owner.</param>
    /// <returns>Item1 - pre image flag, item2 - the data list.</returns>
    AimpActionResult<int, IList> GetFiles(IAimpTaskOwner owner);
}