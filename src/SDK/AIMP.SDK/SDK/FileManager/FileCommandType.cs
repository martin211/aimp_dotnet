//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Enum FileCommandType
    /// </summary>
    public enum FileCommandType
    {
        /// <summary>
        /// The copy to clipboard
        /// </summary>
        CopyToClipboard,

        /// <summary>
        /// The delete
        /// </summary>
        Delete,

        /// <summary>
        /// The drop source
        /// </summary>
        DropSource,

        /// <summary>
        /// The file information
        /// </summary>
        FileInfo,

        /// <summary>
        /// The open file folder
        /// </summary>
        OpenFileFolder,

        /// <summary>
        /// The streaming
        /// </summary>
        Streaming,

        /// <summary>
        /// The file exists
        /// </summary>
        FileExists
    }
}
