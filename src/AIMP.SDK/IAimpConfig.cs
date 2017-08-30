// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
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
        /// <param name="keyPath">The key path.</param>
        AimpActionResult Delete(string keyPath);

        /// <summary>
        /// Gets the value as float.
        /// </summary>
        /// <param name="keyPath">The key path.</param>
        float GetValueAsFloat(string keyPath);

        /// <summary>
        /// Gets the value as int32.
        /// </summary>
        /// <param name="keyPath">The key path.</param>
        int GetValueAsInt32(string keyPath);

        /// <summary>
        /// Gets the value as int64.
        /// </summary>
        /// <param name="keyPath">The key path.</param>
        Int64 GetValueAsInt64(string keyPath);

        /// <summary>
        /// Gets the value as binary stream.
        /// </summary>
        /// <param name="keyPath">The key path.</param>
        IAimpStream GetValueAsStream(string keyPath);

        /// <summary>
        /// Gets the value as string.
        /// </summary>
        /// <param name="keyPath">The key path.</param>
        string GetValueAsString(string keyPath);

        /// <summary>
        /// Sets the value as float.
        /// </summary>
        /// <param name="value">The value.</param>
        AimpActionResult SetValueAsFloat(float value);

        /// <summary>
        /// Sets the value as int32.
        /// </summary>
        /// <param name="value">The value.</param>
        AimpActionResult SetValueAsInt32(int value);

        /// <summary>
        /// Sets the value as int64.
        /// </summary>
        /// <param name="value">The value.</param>
        AimpActionResult SetValueAsInt64(Int64 value);

        /// <summary>
        /// Sets the value as stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        AimpActionResult SetValueAsStream(IAimpStream stream);

        /// <summary>
        /// Sets the value as string.
        /// </summary>
        /// <param name="value">The value.</param>
        AimpActionResult SetValueAsString(string value);
    }
}