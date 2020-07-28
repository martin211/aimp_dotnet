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
    ///     Configuration manager.
    ///     Implements the <see cref="AIMP.SDK.IAimpConfig" />
    ///     Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpConfig" />
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceConfig : IAimpConfig, IAimpService
    {
        /// <summary>
        ///     Flushes the cache.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult FlushCache();
    }
}