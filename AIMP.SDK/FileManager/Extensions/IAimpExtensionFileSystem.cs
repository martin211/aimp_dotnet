namespace AIMP.SDK.FileManager.Extensions
{
    public interface IAimpExtensionFileSystem
    {
        /// <summary>
        /// Gets or sets the scheme filesystem paths.
        /// </summary>
        string Schema { get; set; }

        /// <summary>
        /// Returns false, if the file system does not support the modification of data.
        /// </summary>
        bool ReadOnly { get; }
    }
}