namespace AIMP.SDK.UI.MenuItem
{
    using System.Threading;

    public delegate void ItemAddedHandler(MenuItem parent, MenuItem item);

    public delegate void ItemDeletedHandler(object item);

    public class MenuItemCollection : MBRCollection<MenuItem>
    {
        public event ItemAddedHandler ItemAdded;

        public event ItemDeletedHandler ItemDeleted;

        internal void Add(MenuItem parent, MenuItem item)
        {
            AddItem(item);
            OnItemAdded(parent, item);
        }

        internal void Insert(int index, MenuItem parent, MenuItem item)
        {
            InsertItem(index, item);
            OnItemAdded(parent, item);
        }

        internal void OnItemAdded(MenuItem parent, MenuItem item)
        {
            var tmp = Interlocked.CompareExchange(ref ItemAdded, null, null);
            tmp?.Invoke(parent, item);
        }

        internal void OnItemDeleted(MenuItem item)
        {
            var tmp = Interlocked.CompareExchange(ref ItemDeleted, null, null);
            tmp?.Invoke(item);
        }
    }
}