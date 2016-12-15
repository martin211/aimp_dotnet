using AIMP.SDK.FileManager;

namespace AIMP.SDK.AlbumArtManager
{
    using System;

    using AIMP.SDK.PlayList;

    /// <summary>
    /// Album art manager.
    /// </summary>
    public interface IAimpAlbumArtManager : IAimpAlbumArtSearchOptions
    {
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