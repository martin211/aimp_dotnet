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

namespace AIMP.SDK.Objects
{
    /// <summary>
    /// Interface IAimpMemoryStream
    /// Implements the <see cref="AIMP.SDK.IAimpStream" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpStream" />
    public interface IAimpMemoryStream : IAimpStream
    {
        /// <summary>
        /// Gets the data.
        /// </summary>
        /// <returns>AimpActionResult&lt;System.Byte[]&gt;.</returns>
        AimpActionResult<byte[]> GetData();
    }
}
