namespace AIMP.SDK.Services.ConfigurationManager
{
    using System;
    using System.IO;

    /// <summary>
    /// Configuration manager.
    /// </summary>
    public interface IAimpConfigurationManager
    {
        /// <summary>
        /// Deletes value or section from configuration file.
        /// </summary>
        /// <param name="key"></param>
        void Delete(string key);

        /// <summary>
        /// Gets value as double.
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        double GetValueAsFloat(string key);

        /// <summary>
        /// Gets value as integer.
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        int GetValueAsInt32(string key);

        /// <summary>
        /// Gets value as int64.
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        Int64 GetValueAsInt64(string key);

        /// <summary>
        /// Gets the value as stream.
        /// </summary>
        /// <param name="key">The key.</param>
        Stream GetValueAsStream(string key);

        /// <summary>
        /// Gets the value as string.
        /// </summary>
        /// <param name="key">The key.</param>
        string GetValueAsString(string key);

        /// <summary>
        /// Sets the value as float.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="value">The value.</param>
        void SetValueAsFloat(string key, double value);

        /// <summary>
        /// Sets the value as int32.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="value">The value.</param>
        void SetValueAsInt32(string key, int value);

        /// <summary>
        /// Sets the value as int64.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="value">The value.</param>
        void SetValueAsInt64(string key, Int64 value);

        /// <summary>
        /// Sets the value as stream.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="value">The value.</param>
        void SetValueAsStream(string key, Stream value);

        /// <summary>
        /// Sets the value as string.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="value">The value.</param>
        void SetValueAsString(string key, string value);

        /// <summary>
        /// Flushes the cache.
        /// </summary>
        void FlushCache();
    }
}