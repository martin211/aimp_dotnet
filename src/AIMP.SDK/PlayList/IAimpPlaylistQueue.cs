// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System.Collections.Generic;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// This interface provides an access to playback queue. 
    /// </summary>
    /// <seealso cref="AIMP.SDK.Playlist.IAimpPlaylistQueueListener" />
    public interface IAimpPlaylistQueue : IAimpPlaylistQueueListener
    {
        /// <summary>
        /// Gets or sets a value indicating whether the queue is suspended.
        /// </summary>
        bool IsSuspended { get; set; }

        /// <summary>
        /// Adds the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <param name="insertAtBeginning">if set to <c>true</c> [insert at beginning].</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult Add(IAimpPlaylistItem item, bool insertAtBeginning);

        /// <summary>
        /// Adds the list of items.
        /// </summary>
        /// <param name="items">The list of the <see cref="IAimpPlaylistItem"/> items.</param>
        /// <param name="insertAtBeginning">if set to <c>true</c> [insert at beginning].</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult AddList(IList<IAimpPlaylistItem> items, bool insertAtBeginning);

        /// <summary>
        /// Deletes the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult Delete(IAimpPlaylistItem item);

        /// <summary>
        /// Deletes the specified play list.
        /// </summary>
        /// <param name="playList">The play list.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult Delete(IAimpPlaylist playList);

        /// <summary>
        /// Moves the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult Move(IAimpPlaylistItem item, int index);

        /// <summary>
        /// Moves item from index to target index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="targetIndex">Index of the target.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult Move(int index, int targetIndex);

        /// <summary>
        /// Gets the item from specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult<IAimpPlaylistItem> GetItem(int index);

        /// <summary>
        /// Gets the item count.
        /// </summary>
        /// <returns></returns>
        int GetItemCount();
    }
}