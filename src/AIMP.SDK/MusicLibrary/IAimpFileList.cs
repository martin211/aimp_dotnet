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

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Represents the pair {File name, ID} for data provider.
    /// </summary>
    public interface IAimpFileList
    {
        /// <summary>
        /// Adds new file to the list.
        /// </summary>
        /// <param name="id">File identifier.</param>
        /// <param name="fileName">File name.</param>
        AimpActionResult Add(object id, string fileName);

        /// <summary>
        /// Clears the list.
        /// </summary>
        AimpActionResult Clear();

        /// <summary>
        /// Deletes the file by index.
        /// </summary>
        /// <param name="index">The index.</param>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Inserts new file to the list at specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">The identifier.</param>
        /// <param name="fileName">The file name.</param>
        AimpActionResult Insert(int index, object id, string fileName);

        /// <summary>
        /// Get the count of list.
        /// </summary>
        int GetCount();

        /// <summary>
        /// Gets the file name.
        /// </summary>
        /// <param name="index">The index.</param>
        AimpActionResult<string> GetFileName(int index);

        /// <summary>
        /// Sets the new name for file.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fileName">New file name.</param>
        AimpActionResult SetFileName(int index, string fileName);

        /// <summary>
        /// Gets the file identifier.
        /// </summary>
        /// <param name="index">The index.</param>
        AimpActionResult<object> GetId(int index);

        /// <summary>
        /// Sets the new identifier for file.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">New identifier.</param>
        AimpActionResult SetId(int index, object id);

        /// <summary>
        /// Clones the list.
        /// </summary>
        AimpActionResult<IAimpFileList> Clone();
    }
}