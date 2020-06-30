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
    /// The storage for information about the playlist item.
    /// </summary>
    public interface IAimpPlaylistItem
    {
        /// <summary>
        /// Gets the display text.
        /// </summary>
        string DisplayText { get; }

        /// <summary>
        /// Gets the file information.
        /// </summary>
        IAimpFileInfo FileInfo { get; }

        /// <summary>
        /// Gets or sets the name of the file.
        /// </summary>
        string FileName { get; set; }

        /// <summary>
        /// Gets the group.
        /// </summary>
        IAimpPlaylistGroup Group { get; }

        /// <summary>
        /// Gets or sets the absolute item index in the playlist.
        /// </summary>
        int Index { get; set; }

        /// <summary>
        /// Gets or sets the mark (0.0 to 5.0)
        /// </summary>
        double Mark { get; set; }

        /// <summary>
        /// Index in the internal playback queue.
        /// This index is different from playlist item index.
        /// </summary>
        int PlaybackIndex { get; }

        /// <summary>
        /// Gets or sets a value indicating whether [playback switch].
        /// </summary>
        bool PlaybackSwitch { get; set; }

        /// <summary>
        /// Gets or sets the play list.
        /// </summary>
        IAimpPlaylist PlayList { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlaylistItem"/> is selected.
        /// </summary>
        bool Selected { get; set; }

        /// <summary>
        /// Reloads the information.
        /// </summary>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        ActionResultType ReloadInfo();
    }
}