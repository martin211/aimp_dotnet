using System.IO;

namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Provides detailed information about the specified file.
    /// </summary>
    public interface IAimpExtensionFileInfoProvider
    {
        /// <summary>
        /// Returns the file information.
        /// </summary>
        /// <param name="fileUri">The virtual file name.</param>
        /// <param name="fileInfo">Out. File information/</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfo(string fileUri, out IAimpFileInfo fileInfo);

        /// <summary>
        /// Returns the file information. This method slowes then get info by file name.
        /// </summary>
        /// <param name="stream">The file stream.</param>
        /// <param name="fileInfo">Out. File information/</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfo(Stream stream, out IAimpFileInfo fileInfo);
    }
}