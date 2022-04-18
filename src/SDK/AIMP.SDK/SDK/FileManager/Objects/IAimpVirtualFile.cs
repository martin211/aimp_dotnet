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


using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager.Objects
{
    /// <summary>
    /// Interface provides information about virtual file.
    /// </summary>
    public interface IAimpVirtualFile
    {
        /// <summary>
        /// Gets or sets the index of virtual track in the set (if presented).
        /// </summary>
        /// <value>The index in set.</value>
        int IndexInSet { get; set; }

        /// <summary>
        /// The beginning of the passage to play (in seconds).
        /// </summary>
        /// <value>The clip start.</value>
        double ClipStart { get; set; }

        /// <summary>
        /// The end of the passage to play (in seconds).
        /// </summary>
        /// <value>The clip finish.</value>
        double ClipFinish { get; set; }

        /// <summary>
        /// Gets or sets the real source file.
        /// <para>
        /// Property can be not set if real file name is not exists or file name is same to file name of file-container.
        /// </para>
        /// </summary>
        /// <value>The audio source file.</value>
        string AudioSourceFile { get; set; }

        /// <summary>
        /// Gets the file format. Ex. mp3, ogg, cda.
        /// </summary>
        /// <value>The file format.</value>
        string FileFormat { get; }

        /// <summary>
        /// Gets or sets the virtual file name.
        /// </summary>
        /// <value>The file URI.</value>
        string FileUri { get; set; }

        /// <summary>
        /// Create the instance of the <see cref="IAimpStream" />.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
        AimpActionResult<IAimpStream> CreateStream();

        /// <summary>
        /// Gets the file info.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpFileInfo&gt;.</returns>
        AimpActionResult<IAimpFileInfo> GetFileInfo();

        /// <summary>
        /// Check is the source exists.
        /// </summary>
        /// <returns><c>true</c> if this instance is exists; otherwise, <c>false</c>.</returns>
        bool IsExists();

        /// <summary>
        /// Determines whether [is in same stream] [the specified virtual file].
        /// </summary>
        /// <param name="virtualFile">The virtual file.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult IsInSameStream(IAimpVirtualFile virtualFile);

        /// <summary>
        /// Plugin must validate state of all internal data that refer with source.
        /// If internal data is not valid, plugin must return any error code except ActionResultType.OK.
        /// In this case, the application will automatically reload virtual files for current file-container via one of the
        /// IAimpExtensionFileExpander extensions.
        /// <para>
        /// The method called by the application before call the CreateStream method.
        /// </para>
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Synchronize();
    }
}
