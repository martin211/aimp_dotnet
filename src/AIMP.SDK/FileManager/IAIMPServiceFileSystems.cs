// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Provide ability to work with files.
    /// </summary>
    public interface IAimpServiceFileSystems
    {
        /// <summary>
        /// Get the interface of specified command.
        /// </summary>
        /// <typeparam name="TCommand">The command interface.</typeparam>
        /// <param name="commandType">The command type <see cref="FileCommandType"/>.</param>
        /// <param name="fileUri">The name of virtual file.</param>
        /// <param name="command">The command.</param>
        /// <returns></returns>
        AimpActionResult Get<TCommand>(FileCommandType commandType, string fileUri, out TCommand command);

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="TCommand"></typeparam>
        /// <param name="commandType"></param>
        /// <param name="command"></param>
        /// <returns></returns>
        AimpActionResult GetDefault<TCommand>(FileCommandType commandType, out TCommand command);
    }
}