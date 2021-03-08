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

namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Extension for the IAIMPServiceFileSystems service.
    /// Must implement one or few file system commands(Refer to the children articles of the IAIMPServiceFileSystems
    /// chapter).
    /// </summary>
    public interface IAimpExtensionFileSystem : IAimpExtension
    {
        /// <summary>
        /// Gets the scheme filesystem paths.
        /// </summary>
        /// <value>The schema.</value>
        string Schema { get; }

        /// <summary>
        /// Returns false, if the file system does not support the modification of data.
        /// </summary>
        /// <value><c>true</c> if [read only]; otherwise, <c>false</c>.</value>
        bool ReadOnly { get; }
    }
}
