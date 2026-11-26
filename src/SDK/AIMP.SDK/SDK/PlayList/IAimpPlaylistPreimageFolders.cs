using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Interface IAimpPlaylistPreimageFolders
/// Implements the <see cref="IAimpPlaylistPreimage" />
/// </summary>
/// <seealso cref="IAimpPlaylistPreimage" />
public interface IAimpPlaylistPreimageFolders : IAimpPlaylistPreimage
{
    /// <summary>
    /// Adds a new items.
    /// </summary>
    /// <param name="path">The path.</param>
    /// <param name="recursive">if set to <c>true</c> [recursive].</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult ItemsAdd(string path, bool recursive);

    /// <summary>
    /// Delete item by index.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult ItemsDelete(int index);

    /// <summary>
    /// Delete all items.
    /// </summary>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult ItemsDeleteAll();

    /// <summary>
    /// Get the items by index.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>Item1 - path, Item2 - recursive or not.</returns>
    AimpActionResult<string, bool> ItemsGet(int index);

    /// <summary>
    /// Get count of items at playlist.
    /// </summary>
    /// <returns>System.Int32.</returns>
    int ItemsGetCount();
}