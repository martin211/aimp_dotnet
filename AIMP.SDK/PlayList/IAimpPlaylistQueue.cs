namespace AIMP.SDK.PlayList
{
    using System.Collections.Generic;

    public interface IAimpPlayListQueue : IAimpPlaylistQueueListener
    {
        bool IsSuspended { get; set; }

        AimpActionResult Add(IAimpPlayListItem item, bool insertAtBeginning);

        AimpActionResult AddList(IList<IAimpPlayListItem> items, bool insertAtBeginning);

        AimpActionResult Delete(IAimpPlayListItem item);

        AimpActionResult Delete(IAimpPlayList playList);

        AimpActionResult Move(IAimpPlayListItem item, int index);

        AimpActionResult Move(int index, int targetIndex);

        AimpActionResult GetItem(int index, out IAimpPlayListItem item);

        int GetItemCount();
    }
}