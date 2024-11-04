//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    /// <summary>
    /// Command removes all data from data storage.
    /// The confirmation dialog must be implemented on data storage side.
    /// </summary>
    public interface IAimpDataStorageCommandDropData
    {
        /// <summary>
        /// Drops the data.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult DropData();
    }
}
