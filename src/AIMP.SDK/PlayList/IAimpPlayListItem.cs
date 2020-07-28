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

using AIMP.SDK.FileManager;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    ///     The storage for information about the playlist item.
    /// </summary>
    public interface IAimpPlaylistItem
    {
        /// <summary>
        ///     Gets the display text.
        /// </summary>
        /// <value>The display text.</value>
        string DisplayText { get; }

        /// <summary>
        ///     Gets the file information.
        /// </summary>
        /// <value>The file information.</value>
        IAimpFileInfo FileInfo { get; }

        /// <summary>
        ///     Gets or sets the name of the file.
        /// </summary>
        /// <value>The name of the file.</value>
        string FileName { get; set; }

        /// <summary>
        ///     Gets the group.
        /// </summary>
        /// <value>The group.</value>
        IAimpPlaylistGroup Group { get; }

        /// <summary>
        ///     Gets or sets the absolute item index in the playlist.
        /// </summary>
        /// <value>The index.</value>
        int Index { get; set; }

        /// <summary>
        ///     Gets or sets the mark (0.0 to 5.0)
        /// </summary>
        /// <value>The mark.</value>
        double Mark { get; set; }

        /// <summary>
        ///     Index in the internal playback queue.
        ///     This index is different from playlist item index.
        /// </summary>
        /// <value>The index of the playback.</value>
        int PlaybackIndex { get; }

        /// <summary>
        ///     Gets or sets a value indicating whether [playback switch].
        /// </summary>
        /// <value><c>true</c> if [playback switch]; otherwise, <c>false</c>.</value>
        bool PlaybackSwitch { get; set; }

        /// <summary>
        ///     Gets or sets the play list.
        /// </summary>
        /// <value>The play list.</value>
        IAimpPlaylist PlayList { get; set; }

        /// <summary>
        ///     Gets or sets a value indicating whether this <see cref="IAimpPlaylistItem" /> is selected.
        /// </summary>
        /// <value><c>true</c> if selected; otherwise, <c>false</c>.</value>
        bool Selected { get; set; }

        /// <summary>
        ///     Reloads the information.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult ReloadInfo();
    }
}