using System;
using System.Collections.Generic;

namespace AIMP.SDK.FileManager.Extensions
{
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