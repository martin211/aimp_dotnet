namespace AIMP.SDK.FileManager.Extensions
{
    public interface IAimpExtensionFileSystem
    {
        /// <summary>
        /// Gets the scheme filesystem paths.
        /// </summary>
        string Schema { get; }

        /// <summary>
        /// Returns false, if the file system does not support the modification of data.
        /// </summary>
        bool ReadOnly { get; }
    }
}