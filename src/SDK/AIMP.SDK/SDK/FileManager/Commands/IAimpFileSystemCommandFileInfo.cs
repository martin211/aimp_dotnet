//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.FileManager.Commands
{
    /// <summary>
    /// Interface IAimpFileSystemCommandFileInfo
    /// Implements the <see cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
    public interface IAimpFileSystemCommandFileInfo : IAimpFileSystemCommand
    {
        /// <summary>
        /// Gets the file attributes.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <returns>AimpActionResult&lt;AimpFileAttributes&gt;.</returns>
        AimpActionResult<AimpFileAttributes> GetFileAttrs(string fileName);

        /// <summary>
        /// Gets the size of the file.
        /// </summary>
        /// <param name="file">The file.</param>
        /// <returns>AimpActionResult&lt;System.Int64&gt;.</returns>
        AimpActionResult<long> GetFileSize(string file);

        /// <summary>
        /// Determines whether [is file exists] [the specified file].
        /// </summary>
        /// <param name="file">The file.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult IsFileExists(string file);
    }
}
