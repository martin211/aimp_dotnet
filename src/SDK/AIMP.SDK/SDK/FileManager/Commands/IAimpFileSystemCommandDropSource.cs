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

using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager.Commands
{
    /// <summary>
    /// Interface IAimpFileSystemCommandDropSource
    /// Implements the <see cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
    public interface IAimpFileSystemCommandDropSource : IAimpFileSystemCommand
    {
        /// <summary>
        /// Creates the stream.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
        AimpActionResult<IAimpStream> CreateStream(string fileName);
    }
}
