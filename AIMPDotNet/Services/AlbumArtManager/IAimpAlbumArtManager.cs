namespace AIMP.SDK.Services.AlbumArtManager
{
    using System;

    using AIMP.SDK.Services.PlayList;

    /// <summary>
    /// Album art manager.
    /// </summary>
    public interface IAimpAlbumArtManager
    {
        /// <summary>
        /// Gets or sets a value indicating whether [find in files].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [find in files]; otherwise, <c>false</c>.
        /// </value>
        bool FindInFiles { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [find in internet].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [find in internet]; otherwise, <c>false</c>.
        /// </value>
        bool FindInInternet { get; set; }

        /// <summary>
        /// Gets or sets the file masks.
        /// </summary>
        /// <value>
        /// The file masks.
        /// </value>
        string[] FileMasks { get; set; }

        /// <summary>
        /// Gets or sets the availabel cover file extensions.
        /// </summary>
        /// <value>
        /// The file extensions.
        /// </value>
        string[] FileExtensions { get; set; }

        /// <summary>
        /// Gets or sets the maximum size of the file wich can be downloaded from internet.
        /// </summary>
        /// <value>
        /// The maximum size of the file.
        /// </value>
        int MaxFileSize { get; set; }

        /// <summary>
        /// Occurs when [completed].
        /// </summary>
        event EventHandler<AimpGetAlbumArtEventArgs> Completed;

        /// <summary>
        /// Gets the image.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="artist">The artist.</param>
        /// <param name="album">The album.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="userData">The user data.</param>
        /// <returns></returns>
        IntPtr GetImage(string fileUrl, string artist, string album, AimpFingCovertArtType flags, object userData);

        /// <summary>
        /// Gets the image.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="userData">The user data.</param>
        /// <returns></returns>
        IntPtr GetImage(IAimpFileInfo fileInfo, AimpFingCovertArtType flags, object userData);

        /// <summary>
        /// Cancels the get cover art request by specified task identifier.
        /// </summary>
        /// <param name="taskId">The task identifier.</param>
        /// <param name="flags">The flags.</param>
        void Cancel(IntPtr taskId, AimpFingCovertArtType flags);
    }
}