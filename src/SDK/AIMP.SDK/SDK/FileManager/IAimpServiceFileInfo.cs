//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Enum ServiceFileInfoFlags
    /// </summary>
    public enum ServiceFileInfoFlags
    {
        /// <summary>
        /// The aimp service fileinfo flag dontuseaudiodecoders
        /// </summary>
        DontUseAudioCoders
    }

    /// <summary>
    /// Provide access to get information about virtual file.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceFileInfo : IAimpService
    {
        /// <summary>
        /// Gets the file information from virtual file.
        /// </summary>
        /// <param name="fileUri">The virtual file name.</param>
        /// <param name="fileInfoFlags">The file info flags.</param>
        /// <returns>AimpActionResult&lt;IAimpFileInfo&gt;.</returns>
        AimpActionResult<IAimpFileInfo> GetFileInfoFromFileUri(string fileUri, ServiceFileInfoFlags fileInfoFlags);

        /// <summary>
        /// Gets the file information from stream.
        /// </summary>
        /// <param name="fileStream">The file stream.</param>
        /// <param name="fileInfoFlags">The file info flags.</param>
        /// <returns>AimpActionResult&lt;IAimpFileInfo&gt;.</returns>
        AimpActionResult<IAimpFileInfo> GetFileInfoFromStream(IAimpStream fileStream,
            ServiceFileInfoFlags fileInfoFlags);

        /// <summary>
        /// Gets the virtual file.
        /// </summary>
        /// <param name="fileUri">The virtual file name.</param>
        /// <returns>AimpActionResult&lt;IAimpVirtualFile&gt;.</returns>
        AimpActionResult<IAimpVirtualFile> GetVirtualFile(string fileUri);
    }
}
