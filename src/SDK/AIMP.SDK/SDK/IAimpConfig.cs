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

namespace AIMP.SDK
{
    /// <summary>
    /// Interface IAimpConfig
    /// </summary>
    public interface IAimpConfig
    {
        /// <summary>
        /// Deletes the value or section from config (section or section\value name).
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(string keyPath);

        /// <summary>
        /// Gets the value as float.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <returns>AimpActionResult&lt;System.Single&gt;.</returns>
        AimpActionResult<float> GetValueAsFloat(string keyPath);

        /// <summary>
        /// Gets the value as int32.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <returns>AimpActionResult&lt;System.Int32&gt;.</returns>
        AimpActionResult<int> GetValueAsInt32(string keyPath);

        /// <summary>
        /// Gets the value as int64.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <returns>AimpActionResult&lt;Int64&gt;.</returns>
        AimpActionResult<long> GetValueAsInt64(string keyPath);

        /// <summary>
        /// Gets the value as binary stream.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
        AimpActionResult<IAimpStream> GetValueAsStream(string keyPath);

        /// <summary>
        /// Gets the value as string.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> GetValueAsString(string keyPath);

        /// <summary>
        /// Sets the value as float.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <param name="value">The value.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetValueAsFloat(string keyPath, float value);

        /// <summary>
        /// Sets the value as int32.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <param name="value">The value.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetValueAsInt32(string keyPath, int value);

        /// <summary>
        /// Sets the value as int64.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <param name="value">The value.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetValueAsInt64(string keyPath, long value);

        /// <summary>
        /// Sets the value as stream.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <param name="stream">The stream.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetValueAsStream(string keyPath, IAimpStream stream);

        /// <summary>
        /// Sets the value as string.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        /// <param name="value">The value.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetValueAsString(string keyPath, string value);
    }
}
