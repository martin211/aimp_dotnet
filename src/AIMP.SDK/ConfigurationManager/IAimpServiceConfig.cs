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

namespace AIMP.SDK.ConfigurationManager
{
    /// <summary>
    /// Configuration manager.
    /// </summary>
    public interface IAimpServiceConfig : IAimpConfig, IAimpService
    {
        /// <summary>
        /// Flushes the cache.
        /// </summary>
        AimpActionResult FlushCache();
    }
}