// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.FileManager
{
    public enum ServiceFileInfoFlags
    {
        AIMP_SERVICE_FILEINFO_FLAG_DONTUSEAUDIODECODERS
    }

    /// <summary>
    /// Provide access to get information about virtual file.
    /// </summary>
    public interface IAimpServiceFileInfo
    {
        /// <summary>
        /// Gets the file information from virtual file.
        /// </summary>
        /// <param name="fileUri">The virtual file name.</param>
        /// <param name="fileInfoFlags">The file info flags.</param>
        /// <param name="fileInfo">Out. The file info <see cref="IAimpFileInfo"/>.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfoFromFileUri(string fileUri, ServiceFileInfoFlags fileInfoFlags,
            out IAimpFileInfo fileInfo);

        /// <summary>
        /// Gets the file information from stream.
        /// </summary>
        /// <param name="fileStream">The file stream.</param>
        /// <param name="fileInfoFlags">The file info flags.</param>
        /// <param name="fileInfo">Out. The file info <see cref="IAimpFileInfo"/>.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfoFromStream(IAimpStream fileStream, ServiceFileInfoFlags fileInfoFlags,
            out IAimpFileInfo fileInfo);

        /// <summary>
        /// Gets the virtual file.
        /// </summary>
        /// <param name="fileUri">The virtual file name.</param>
        /// <param name="virtualFile">Out. Virtual file <see cref="IAimpVirtualFile"/>.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetVirtualFile(string fileUri, out IAimpVirtualFile virtualFile);
    }
}