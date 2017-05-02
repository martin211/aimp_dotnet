using System;
using System.Collections.Generic;

namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Interface is an extension for the <see cref="IAimpServiceFileManager"/> service that allows split real file container into one or view virtual files.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application at the plugin initialization method via the IAimpCore.RegisterExtension method.
    /// </para>
    /// </summary>
    public interface IAimpExtensionFileExpander
    {
        /// <summary>
        /// Split the file container to virtual files.
        /// </summary>
        /// <param name="fileName">The real file name</param>
        /// <param name="filesList">Out. The list of virtual files.</param>
        /// <param name="progressCallback">Progress callback.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Expand(string fileName, out IList<IAimpVirtualFile> filesList, Func<long, bool> progressCallback);
    }
}