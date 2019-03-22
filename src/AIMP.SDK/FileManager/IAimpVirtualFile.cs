// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System.IO;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Interface provides information about virtual file.
    /// </summary>
    public interface IAimpVirtualFile
    {
        /// <summary>
        /// Gets or sets the index of virtual track in the set (if presented).
        /// </summary>
        int IndexInSet { get; set; }

        /// <summary>
        /// The beginning of the passage to play (in seconds).
        /// </summary>
        double ClipStart { get; set; }

        /// <summary>
        /// The end of the passage to play (in seconds).
        /// </summary>
        double ClipFinish { get; set; }

        /// <summary>
        /// Gets or sets the real source file.
        /// <para>
        /// Property can be not set if real file name is not exists or file name is same to file name of file-container.
        /// </para>
        /// </summary>
        string AudioSourceFile { get; set; }

        /// <summary>
        /// Gets the file format. Ex. mp3, ogg, cda.
        /// </summary>
        string FileFormat { get; }

        /// <summary>
        /// Gets or sets the virtual file name.
        /// </summary>
        string FileUri { get; set; }

        //TODO: ADN-26
        /// <summary>
        /// Create the instance of the <see cref="IAimpStream"/>.
        /// </summary>
        /// <param name="stream"></param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult CreateStream(out Stream stream);

        /// <summary>
        /// Gets the file info.
        /// </summary>
        /// <param name="fileInfo">Out. File info <see cref="IAimpFileInfo"/>.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFileInfo(out IAimpFileInfo fileInfo);

        /// <summary>
        /// Check is the source exists.
        /// </summary>
        /// <returns></returns>
        bool IsExists();

        /// <summary>
        ///
        /// </summary>
        /// <param name="virtualFile"></param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult IsInSameStream(IAimpVirtualFile virtualFile);

        /// <summary>
        /// Plugin must validate state of all internal data that refer with source.
        /// If internal data is not valid, plugin must return any error code except AimpActionResult.Ok.
        /// In this case, the application will automatically reload virtual files for current file-container via one of the IAimpExtensionFileExpander extensions.
        /// <para>
        /// The method called by the application before call the CreateStream method.
        /// </para>
        /// </summary>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Synchronize();
    }
}