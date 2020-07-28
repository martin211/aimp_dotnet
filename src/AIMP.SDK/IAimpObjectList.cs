// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;

namespace AIMP.SDK
{
    /// <summary>
    /// This is a list of general purpose, it can contains any interfaces.
    /// </summary>
    /// <typeparam name="TObject">The type of elements in the list.</typeparam>
    public interface IAimpObjectList<TObject>
    {
        int Count { get; }

        /// <summary>
        /// Adds an item to the collection.
        /// </summary>
        /// <param name="entry">The object to add to the collection.</param>
        AimpActionResult Add(TObject entry);

        /// <summary>
        /// Removes all items from the list.
        /// </summary>
        AimpActionResult Clear();

        /// <summary>
        /// Removes the item at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the item to remove.</param>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Inserts an item to the collection at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item" /> should be inserted.</param>
        /// <param name="item">The object to insert into the collection.</param>
        AimpActionResult Insert(int index, TObject item);

        /// <summary>
        /// Gets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to get.</param>
        /// <param name="item">The item at specified <paramref name="index"/>.</param>
        AimpActionResult GetObject(int index, out TObject item);

        /// <summary>
        /// Sets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to set.</param>
        /// <param name="item">The item to set.</param>
        AimpActionResult SetObject(int index, TObject item);
    }

    public interface IAimpObjectList
    {
        int Count { get; }

        /// <summary>
        /// Adds an item to the collection.
        /// </summary>
        /// <param name="entry">The object to add to the collection.</param>
        AimpActionResult Add(object entry);

        /// <summary>
        /// Removes all items from the list.
        /// </summary>
        AimpActionResult Clear();

        /// <summary>
        /// Removes the item at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the item to remove.</param>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Inserts an item to the collection at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item" /> should be inserted.</param>
        /// <param name="item">The object to insert into the collection.</param>
        AimpActionResult Insert(int index, object item);

        /// <summary>
        /// Gets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to get.</param>
        /// <param name="item">The item at specified <paramref name="index"/>.</param>
        AimpActionResult GetObject(int index, out object item);

        /// <summary>
        /// Sets the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to set.</param>
        /// <param name="item">The item to set.</param>
        AimpActionResult SetObject(int index, object item);
    }
}