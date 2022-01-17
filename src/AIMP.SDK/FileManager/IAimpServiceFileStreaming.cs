﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK.FileManager.Primitives;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Enum FileStreamingType
    /// </summary>
    [Flags]
    public enum FileStreamingType
    {
        /// <summary>
        /// The aimp service filestreaming flag read
        /// </summary>
        Read = 0,

        /// <summary>
        /// The aimp service filestreaming flag createnew
        /// </summary>
        CreateNew = 1,

        /// <summary>
        /// The aimp service filestreaming flag readwrite
        /// </summary>
        ReadWrite = 2,

        /// <summary>
        /// The aimp service filestreaming flag maptomemory
        /// </summary>
        MapToMemory = 4
    }

    /// <summary>
    /// Class CeateStreamResult.
    /// </summary>
    public class CreateStreamResult
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CreateStreamResult" /> class.
        /// </summary>
        /// <param name="virtualFile">The virtual file.</param>
        /// <param name="stream">The stream.</param>
        public CreateStreamResult(IAimpVirtualFile virtualFile, IAimpStream stream)
        {
            VirtualFile = virtualFile;
            Stream = stream;
        }

        /// <summary>
        /// Gets the virtual file.
        /// </summary>
        /// <value>The virtual file.</value>
        public IAimpVirtualFile VirtualFile { get; }

        /// <summary>
        /// Gets the stream.
        /// </summary>
        /// <value>The stream.</value>
        public IAimpStream Stream { get; }
    }

    /// <summary>
    /// Interface IAimpServiceFileStreaming
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceFileStreaming : IAimpService
    {
        /// <summary>
        /// Creates the stream for file.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="offset">The offset.</param>
        /// <param name="size">The size.</param>
        /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
        AimpActionResult<IAimpStream> CreateStreamForFile(string fileName, FileStreamingType flags, long offset, long size);

        /// <summary>
        /// Creates the stream for file URI.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <returns>AimpActionResult&lt;CeateStreamResult&gt;.</returns>
        AimpActionResult<CreateStreamResult> CreateStreamForFileUri(string fileUrl);
    }
}
