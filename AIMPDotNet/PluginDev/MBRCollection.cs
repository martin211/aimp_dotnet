using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Reflection;
using System.Runtime;
using System.Runtime.InteropServices;

namespace dotNetInteropPlugin.PluginDev.Additions
{
    /// <summary>
    /// Base collection class, that derived form MarshalByRefObject
    /// </summary>
    /// <typeparam name="T">Type</typeparam>
    public class MBRCollection<T>: MarshalByRefObject, IList<T>, ICollection<T>, IEnumerable<T>
    {
        public MBRCollection()
        {
            Items = new List<T>();
        }
        public MBRCollection(IList<T> list)
        {
            Items = new List<T>(list);
        }

        /// <summary>
        /// Number of elements
        /// </summary>
        public int Count { get { return Items.Count; } }

        /// <summary>
        /// Items
        /// </summary>
        protected IList<T> Items 
        { 
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets elements inside collection
        /// </summary>
        /// <param name="index">Index</param>
        /// <returns>Value</returns>
        public T this[int index]
        {
            get { return Items[index]; }
            set
            {
                SetItem(index, value);
            }
        }

        /// <summary>
        /// Add new element to collection
        /// </summary>
        /// <param name="item">Element</param>
        public void Add(T item)
        {
            InsertItem(Count, item);
        }

        /// <summary>
        /// Clear collection
        /// </summary>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public void Clear()
        {
            ClearItems();
        }

        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        protected virtual void ClearItems()
        {
            Items.Clear();
        }

        /// <summary>
        /// Determines whether an element is in the
        /// </summary>
        /// <param name="item">element</param>
        /// <returns>true if item is found</returns>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public bool Contains(T item)
        {
            return Items.Contains(item);
        }

        /// <summary>
        /// Copies collection to array
        /// </summary>
        /// <param name="array">Array</param>
        /// <param name="index">Index</param>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public void CopyTo(T[] array, int index)
        {
            Items.CopyTo(array, index);
        }
        /// <summary>
        /// Returns an enumerator that iterates through the collection
        /// </summary>
        /// <returns>Enumerator</returns>
        public IEnumerator<T> GetEnumerator()
        {
            return Items.GetEnumerator();
        }

        /// <summary>
        /// Searches for the specified object and returns the zero-based index of the
        /// first occurrence within
        /// </summary>
        /// <param name="item">Element</param>
        /// <returns>Index</returns>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public int IndexOf(T item)
        {
            return Items.IndexOf(item);
        }

        /// <summary>
        /// Insert element to collection
        /// </summary>
        /// <param name="index">index</param>
        /// <param name="item">element</param>
        public void Insert(int index, T item)
        {
            InsertItem(index, item);
        }

        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        protected virtual void InsertItem(int index, T item)
        {
            Items.Insert(index, item);
        }
        /// <summary>
        /// Remove element from collection
        /// </summary>
        /// <param name="item">element</param>
        /// <returns>Success</returns>
        public bool Remove(T item)
        {
            int index = Items.IndexOf(item);
            if (index >= 0)
                RemoveItem(index);
            return index >= 0;
        }
        /// <summary>
        /// Remove element from particular position
        /// </summary>
        /// <param name="index">Index</param>
        public void RemoveAt(int index)
        {
            if (index < 0 || index >= Count)
                throw new IndexOutOfRangeException("Index '" + index.ToString() + "' is out of range");
            RemoveItem(index);
        }

        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        protected virtual void RemoveItem(int index)
        {
            Items.RemoveAt(index);
        }
        protected virtual void SetItem(int index, T item)
        {
            Items[index] = item;
        }

        /// <summary>
        /// False
        /// </summary>
        public bool IsReadOnly
        {
            get { return false; }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }



    // ======================================

    /// <summary>
    /// Base collection class, that derived form MarshalByRefObject
    /// </summary>
    /// <typeparam name="T">Type</typeparam>
    public class MBRCollectionNI<T> : MarshalByRefObject, ICollection<T>, IEnumerable<T>
    {
        public MBRCollectionNI()
        {
            Items = new List<T>();
        }
        public MBRCollectionNI(IList<T> list)
        {
            Items = new List<T>(list);
        }

        /// <summary>
        /// Number of elements
        /// </summary>
        public int Count { get { return Items.Count; } }

        /// <summary>
        /// Items
        /// </summary>
        protected IList<T> Items
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets elements inside collection
        /// </summary>
        /// <param name="index">Index</param>
        /// <returns>Value</returns>
        public T this[int index]
        {
            get { return Items[index]; }
        }

        /// <summary>
        /// Add new element to collection
        /// </summary>
        /// <param name="item">Element</param>
        public void Add(T item)
        {
            InsertItem(Count, item);
        }

        /// <summary>
        /// Remove all elements from collection
        /// </summary>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public void Clear()
        {
            ClearItems();
        }

        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        protected virtual void ClearItems()
        {
            Items.Clear();
        }

        /// <summary>
        /// Determines whether an element is in the
        /// </summary>
        /// <param name="item">element</param>
        /// <returns>true if item is found</returns>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public bool Contains(T item)
        {
            return Items.Contains(item);
        }

        /// <summary>
        /// Copies collection to array
        /// </summary>
        /// <param name="array">Array</param>
        /// <param name="index">Index</param>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public void CopyTo(T[] array, int index)
        {
            Items.CopyTo(array, index);
        }

        /// <summary>
        /// Returns an enumerator that iterates through the collection
        /// </summary>
        /// <returns>Enumerator</returns>
        public IEnumerator<T> GetEnumerator()
        {
            return Items.GetEnumerator();
        }

        /// <summary>
        /// Searches for the specified object and returns the zero-based index of the
        /// first occurrence within
        /// </summary>
        /// <param name="item">Element</param>
        /// <returns>Index</returns>
        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        public int IndexOf(T item)
        {
            return Items.IndexOf(item);
        }

        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        protected virtual void InsertItem(int index, T item)
        {
            Items.Insert(index, item);
        }

        /// <summary>
        /// Remove element from collection
        /// </summary>
        /// <param name="item">element</param>
        /// <returns>Success</returns>
        public bool Remove(T item)
        {
            int index = Items.IndexOf(item);
            if (index >= 0)
                RemoveItem(index);
            return index >= 0;
        }
        /// <summary>
        /// Remove element from particular position
        /// </summary>
        /// <param name="index">Index</param>
        public void RemoveAt(int index)
        {
            if (index < 0 || index >= Count)
                throw new IndexOutOfRangeException("Index '" + index.ToString() + "' is out of range");
            RemoveItem(index);
        }

        [TargetedPatchingOptOut("Performance critical to inline across NGen image boundaries")]
        protected virtual void RemoveItem(int index)
        {
            Items.RemoveAt(index);
        }
        protected virtual void SetItem(int index, T item)
        {
            Items[index] = item;
        }

        /// <summary>
        /// False
        /// </summary>
        public bool IsReadOnly
        {
            get { return false; }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
