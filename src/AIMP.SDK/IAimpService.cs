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

namespace AIMP.SDK
{
    /// <summary>
    /// Interface IAimpService.
    /// </summary>
    public interface IAimpService
    {
        /// <summary>
        /// Gets a value indicating whether this instance is exists.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is exists; otherwise, <c>false</c>.
        /// </value>
        bool IsExists { get; }
    }
}