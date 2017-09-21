namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Providers an ability to customize display value for specified field.
    /// </summary>
    public interface IAimpDataFieldDisplayValue
    {
        /// <summary>
        /// Gets the display value.
        /// </summary>
        /// <param name="value">The original value.</param>
        /// <param name="length">Count of characters in result.</param>
        string GetDisplayValue(object value, out int length);
    }
}