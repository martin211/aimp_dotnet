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

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    /// <summary>
    /// Interface IAimpDataStorageCommandUserMark
    /// </summary>
    public interface IAimpDataStorageCommandUserMark
    {
        /// <summary>
        /// Sets the mark.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="value">The value.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetMark(object id, double value);
    }
}