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

using AIMP.SDK.FileManager.Commands;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Provide ability to work with files.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceFileSystems : IAimpService
    {
        /// <summary>
        /// Get the interface of specified command.
        /// </summary>
        /// <param name="commandType">The command type <see cref="FileCommandType" />.</param>
        /// <param name="fileUri">The name of virtual file.</param>
        /// <returns>AimpActionResult&lt;IAimpFileSystemCommand&gt;.</returns>
        AimpActionResult<IAimpFileSystemCommand> Get(FileCommandType commandType, string fileUri);

        /// <summary>
        /// Gets the default.
        /// </summary>
        /// <param name="commandType">Type of the command.</param>
        /// <returns>AimpActionResult&lt;IAimpFileSystemCommand&gt;.</returns>
        AimpActionResult<IAimpFileSystemCommand> GetDefault(FileCommandType commandType);
    }
}