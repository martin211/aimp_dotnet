using System.IO;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Provide information about virtual file.
    /// </summary>
    public interface IAimpVirtualFile
    {
        /// <summary>
        /// Gets or sets the index number at steck.
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

        /// <summary>
        /// Create the new stream.
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
        ///
        /// </summary>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult Synchronize();
    }
}