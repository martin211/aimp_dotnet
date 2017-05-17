namespace AIMP.SDK.PlayList
{
    using System.Collections.Generic;

    /// <summary>
    /// This interface provides an access to playback queue. 
    /// </summary>
    /// <seealso cref="AIMP.SDK.PlayList.IAimpPlaylistQueueListener" />
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
        /// <returns></returns>
        AimpActionResult Add(IAimpPlayListItem item, bool insertAtBeginning);

        /// <summary>
        /// Adds the list of items.
        /// </summary>
        /// <param name="items">The list of the <see cref="IAimpPlayListItem"/> items.</param>
        /// <param name="insertAtBeginning">if set to <c>true</c> [insert at beginning].</param>
        /// <returns></returns>
        AimpActionResult AddList(IList<IAimpPlayListItem> items, bool insertAtBeginning);

        /// <summary>
        /// Deletes the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <returns></returns>
        AimpActionResult Delete(IAimpPlayListItem item);

        /// <summary>
        /// Deletes the specified play list.
        /// </summary>
        /// <param name="playList">The play list.</param>
        /// <returns></returns>
        AimpActionResult Delete(IAimpPlaylist playList);

        /// <summary>
        /// Moves the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        AimpActionResult Move(IAimpPlayListItem item, int index);

        /// <summary>
        /// Moves item from index to target index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="targetIndex">Index of the target.</param>
        /// <returns></returns>
        AimpActionResult Move(int index, int targetIndex);

        /// <summary>
        /// Gets the item from specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="item">The item.</param>
        /// <returns></returns>
        AimpActionResult GetItem(int index, out IAimpPlayListItem item);

        /// <summary>
        /// Gets the item count.
        /// </summary>
        /// <returns></returns>
        int GetItemCount();
    }
}