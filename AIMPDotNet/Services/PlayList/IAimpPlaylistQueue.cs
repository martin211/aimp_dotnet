namespace AIMP.SDK.Services.PlayList
{
    using System.Collections.Generic;

    public interface IAimpPlayListQueue
    {
        bool IsSuspended { get; set; }

        void Add(IAimpPlayListItem item, bool insertAtBeginning);

        void AddList(IList<IAimpPlayListItem> items, bool insertAtBeginning);

        void Delete(IAimpPlayListItem item);

        void Delete(IAimpPlayList playList);

        void Move(IAimpPlayListItem item, int index);

        void Move(int index, int targetIndex);

        // TODO: Add GetItem
        //object GetItem(int index,);

        int Count();
    }
}