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
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Add(object id, string fileName);

        /// <summary>
        /// Clears the list.
        /// </summary>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Clear();

        /// <summary>
        /// Deletes the file by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Inserts new file to the list at specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">The identifier.</param>
        /// <param name="fileName">The file name.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Insert(int index, object id, string fileName);

        /// <summary>
        /// Get the count of list.
        /// </summary>
        int GetCount();

        /// <summary>
        /// Gets the file name.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fileName">[out] The file name.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileName(int index, out string fileName);

        /// <summary>
        /// Sets the new name for file.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fileName">New file name.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult SetFileName(int index, string fileName);

        /// <summary>
        /// Gets the file identifier.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">[out] The file identifier,</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetId(int index, out object id);

        /// <summary>
        /// Sets the new identifier for file.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="id">New identifier.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult SetId(int index, object id);

        /// <summary>
        /// Clones the list.
        /// </summary>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Clone(out IAimpFileList list);
    }
}