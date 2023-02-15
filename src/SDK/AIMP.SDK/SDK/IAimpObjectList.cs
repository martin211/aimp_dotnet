//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections;
using AIMP.SDK.MusicLibrary;

namespace AIMP.SDK
{
    /// <summary>
    /// This is a list of general purpose, it can contains any interfaces.
    /// </summary>
    /// <typeparam name="TObject">The type of elements in the list.</typeparam>
    public interface IAimpObjectList<TObject> : IAimpObject
    {
        /// <summary>
        /// Gets the count.
        /// </summary>
        /// <value>The count.</value>
        int Count { get; }

        /// <summary>
        /// Adds an item to the collection.
        /// </summary>
        /// <param name="entry">The object to add to the collection.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Add(TObject entry);

        /// <summary>
        /// Removes all items from the list.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Clear();

        /// <summary>
        /// Removes the item at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the item to remove.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Inserts an item to the collection at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item" /> should be inserted.</param>
        /// <param name="item">The object to insert into the collection.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Insert(int index, TObject item);

        /// <summary>
        /// Gets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to get.</param>
        /// <param name="item">The item at specified <paramref name="index" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult GetObject(int index, out TObject item);

        /// <summary>
        /// Sets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to set.</param>
        /// <param name="item">The item to set.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetObject(int index, TObject item);
    }

    /// <summary>
    /// Interface IAimpObjectList
    /// </summary>
    public interface IAimpObjectList : IAimpObject
    {
        /// <summary>
        /// Gets the count.
        /// </summary>
        /// <value>The count.</value>
        int Count { get; }

        /// <summary>
        /// Adds an item to the collection.
        /// </summary>
        /// <param name="entry">The object to add to the collection.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Add(object entry);

        /// <summary>
        /// Removes all items from the list.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Clear();

        /// <summary>
        /// Removes the item at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the item to remove.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Inserts an item to the collection at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item" /> should be inserted.</param>
        /// <param name="item">The object to insert into the collection.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Insert(int index, object item);

        /// <summary>
        /// Gets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to get.</param>
        /// <param name="item">The item at specified <paramref name="index" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult GetObject(int index, out object item);

        /// <summary>
        /// Sets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to set.</param>
        /// <param name="item">The item to set.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetObject(int index, object item);
    }

    public interface IAimpOrderedObjectList : IAimpObjectList<IAimpOrderedItem>
    {
        IAimpOrderedItem Create(string name, SortDirectionType sortDirection);
    }

    public interface IAimpOrderedItem
    {
        IAimpString Name { get; }

        SortDirectionType Value { get; set; }
    }
}
