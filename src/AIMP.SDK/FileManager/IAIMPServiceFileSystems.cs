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
using AIMP.SDK.FileManager.Commands;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Provide ability to work with files.
    /// </summary>
    public interface IAimpServiceFileSystems : IAimpService
    {
        /// <summary>
        /// Get the interface of specified command.
        /// </summary>
        /// <param name="commandType">The command type <see cref="FileCommandType"/>.</param>
        /// <param name="fileUri">The name of virtual file.</param>
        /// <param name="command">The command.</param>
        /// <returns></returns>
        AimpActionResult Get(FileCommandType commandType, string fileUri, out IAimpFileSystemCommand command);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="commandType"></param>
        /// <param name="command"></param>
        /// <returns></returns>
        AimpActionResult GetDefault(FileCommandType commandType, out IAimpFileSystemCommand command);
    }
}