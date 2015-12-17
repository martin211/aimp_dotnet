namespace AIMP.SDK.Services.MUIManager
{
    /// <summary>
    /// MUI manager.
    /// </summary>
    // ReSharper disable InconsistentNaming
    public interface IAimpMUIManager
        // ReSharper restore InconsistentNaming
    {
        /// <summary>
        /// Gets the current locale name.
        /// </summary>
        /// <returns></returns>
        string GetName();

        /// <summary>
        /// Gets the value.
        /// </summary>
        /// <param name="key">The key.</param>
        string GetValue(string key);

        /// <summary>
        /// Gets the value part.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="index">The index.</param>
        string GetValuePart(string key, int index);
    }
}