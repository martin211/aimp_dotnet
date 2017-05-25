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

using System.IO;

namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Interface is an extension for the <see cref="IAimpServiceFileInfo"/> service that provides an extended information about the file.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application at the plugin initialization method via the IAimpCore.RegisterExtension method.
    /// </para>
    /// </summary>
    public interface IAimpExtensionFileInfoProvider
    {
        /// <summary>
        /// Returns the file information.
        /// </summary>
        /// <param name="fileUri">The virtual file name.</param>
        /// <param name="fileInfo">Out. File information/</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfo(string fileUri, ref IAimpFileInfo fileInfo);

        /// <summary>
        /// Returns the file information. This method slowes then get info by file name.
        /// </summary>
        /// <param name="stream">The file stream.</param>
        /// <param name="fileInfo">Out. File information/</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfo(Stream stream, ref IAimpFileInfo fileInfo);
    }
}