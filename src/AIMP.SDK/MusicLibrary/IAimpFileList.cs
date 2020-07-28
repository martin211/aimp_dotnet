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
    ///     Represents the pair {File name, ID} for data provider.
    /// </summary>
    public interface IAimpFileList
    {
        /// <summary>
        ///     Adds new file to the list.
        /// </summary>
        /// <param name="id">File identifier.</param>
        /// <param name="fileName">File name.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Add(object id, string fileName);

        /// <summary>
        ///     Clears the list.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Clear();

        /// <summary>
        ///     Deletes the file by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(int index);

        /// <summary>
        ///     Inserts new file to the list at specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">The identifier.</param>
        /// <param name="fileName">The file name.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Insert(int index, object id, string fileName);

        /// <summary>
        ///     Get the count of list.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetCount();

        /// <summary>
        ///     Gets the file name.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> GetFileName(int index);

        /// <summary>
        ///     Sets the new name for file.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fileName">New file name.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetFileName(int index, string fileName);

        /// <summary>
        ///     Gets the file identifier.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;System.Object&gt;.</returns>
        AimpActionResult<object> GetId(int index);

        /// <summary>
        ///     Sets the new identifier for file.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">New identifier.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetId(int index, object id);

        /// <summary>
        ///     Clones the list.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpFileList&gt;.</returns>
        AimpActionResult<IAimpFileList> Clone();
    }
}