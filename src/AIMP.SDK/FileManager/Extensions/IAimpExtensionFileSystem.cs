namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Extension for the IAIMPServiceFileSystems service.
    /// Must implement one or few file system commands(Refer to the children articles of the IAIMPServiceFileSystems chapter).
    /// </summary>
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