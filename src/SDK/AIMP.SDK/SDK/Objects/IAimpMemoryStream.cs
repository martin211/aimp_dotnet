//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Objects;

namespace AIMP.SDK
{
    /// <summary>
    /// Interface IAimpMemoryStream
    /// Implements the <see cref="IAimpStream" />
    /// </summary>
    /// <seealso cref="IAimpStream" />
    public interface IAimpMemoryStream : IAimpStream
    {
        /// <summary>
        /// Gets the data.
        /// </summary>
        /// <returns>AimpActionResult&lt;System.Byte[]&gt;.</returns>
        AimpActionResult<byte[]> GetData();
    }
}
