// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System;

namespace AIMP.SDK
{
    public interface IAimpConfig
    {
        /// <summary>
        /// Deletes the value or section from config (section or section\value name).
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        AimpActionResult Delete(string keyPath);

        /// <summary>
        /// Gets the value as float.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        float GetValueAsFloat(string keyPath);

        /// <summary>
        /// Gets the value as int32.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        int GetValueAsInt32(string keyPath);

        /// <summary>
        /// Gets the value as int64.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        Int64 GetValueAsInt64(string keyPath);

        /// <summary>
        /// Gets the value as binary stream.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        IAimpStream GetValueAsStream(string keyPath);

        /// <summary>
        /// Gets the value as string.
        /// </summary>
        /// <param name="keyPath">The key path (section\value name).</param>
        string GetValueAsString(string keyPath);

        /// <summary>
        /// Sets the value as float.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="keyPath">The key path (section\value name).</param>
        AimpActionResult SetValueAsFloat(string keyPath, float value);

        /// <summary>
        /// Sets the value as int32.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="keyPath">The key path (section\value name).</param>
        AimpActionResult SetValueAsInt32(string keyPath, int value);

        /// <summary>
        /// Sets the value as int64.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="keyPath">The key path (section\value name).</param>
        AimpActionResult SetValueAsInt64(string keyPath, Int64 value);

        /// <summary>
        /// Sets the value as stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <param name="keyPath">The key path (section\value name).</param>
        AimpActionResult SetValueAsStream(string keyPath, IAimpStream stream);

        /// <summary>
        /// Sets the value as string.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="keyPath">The key path (section\value name).</param>
        AimpActionResult SetValueAsString(string keyPath, string value);
    }
}