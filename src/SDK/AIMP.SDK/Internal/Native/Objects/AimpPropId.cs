namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// Constants from apiFileManager.h / apiPlaylists.h / apiMenu.h.
    /// </summary>
    public static class AimpPropId
    {
        // IAIMPExtensionFileSystem
        public const int FileSystemScheme = 1;
        public const int FileSystemReadOnly = 2;

        // IAIMPPlaylistPreimage
        public const int PlaylistPreimageFactoryId = 1;
        public const int PlaylistPreimageAutoSync = 2;
        public const int PlaylistPreimageHasDialog = 3;
        public const int PlaylistPreimageSortTemplate = 4;
        public const int PlaylistPreimageAutoSyncOnStartup = 5;

        // IAIMPAction
        public const int ActionCustom = 0;
        public const int ActionId = 1;
        public const int ActionName = 2;
        public const int ActionGroupName = 3;
        public const int ActionEnabled = 4;
        public const int ActionDefaultLocalHotKey = 5;
        public const int ActionDefaultGlobalHotKey = 6;
        public const int ActionDefaultGlobalHotKey2 = 7;
        public const int ActionEvent = 8;

        // IAIMPPlaylist (the object exposes IAIMPPropertyList via QueryInterface)
        public const int PlaylistName = 1;
        public const int PlaylistReadOnly = 2;
        public const int PlaylistFocusedObject = 3;
        public const int PlaylistId = 4;
        public const int PlaylistGroupingName = 5;
        public const int PlaylistGrouping = 10;
        public const int PlaylistGroupingOverridden = 11;
        public const int PlaylistGroupingTemplate = 12;
        public const int PlaylistGroupingAutomerging = 13;
        public const int PlaylistFormattingOverridden = 20;
        public const int PlaylistFormattingLine1 = 21;
        public const int PlaylistFormattingLine2 = 22;
        public const int PlaylistViewOverridden = 30;
        public const int PlaylistViewDuration = 31;
        public const int PlaylistViewExpandButtons = 32;
        public const int PlaylistViewMarks = 33;
        public const int PlaylistViewNumbers = 34;
        public const int PlaylistViewNumbersAbsolute = 35;
        public const int PlaylistViewSecondLine = 36;
        public const int PlaylistViewSwitches = 37;
        public const int PlaylistViewThumbnails = 38;
        public const int PlaylistFocusIndex = 50;
        public const int PlaylistPlaybackCursor = 51;
        public const int PlaylistPlayingIndex = 52;
        public const int PlaylistSize = 53;
        public const int PlaylistDuration = 54;
        public const int PlaylistDurationRemaining = 55;
        public const int PlaylistPreimage = 60;

        // IAIMPPlaylistItem
        public const int PlaylistItemCustom = 0;
        public const int PlaylistItemDisplayText = 1;
        public const int PlaylistItemFileInfo = 2;
        public const int PlaylistItemFileName = 3;
        public const int PlaylistItemGroup = 4;
        public const int PlaylistItemIndex = 5;
        public const int PlaylistItemMark = 6;
        public const int PlaylistItemPlayingSwitch = 7;
        public const int PlaylistItemPlaylist = 8;
        public const int PlaylistItemSelected = 9;
        public const int PlaylistItemPlaybackQueueIndex = 10;
        public const int PlaylistItemDeadState = 11;

        // IAIMPPlaylistGroup
        public const int PlaylistGroupName = 1;
        public const int PlaylistGroupExpanded = 2;
        public const int PlaylistGroupDuration = 3;
        public const int PlaylistGroupIndex = 4;
        public const int PlaylistGroupSelected = 5;

        // IAIMPPlaylistQueue
        public const int PlaylistQueueSuspended = 1;

        // IAIMPMenuItem
        public const int MenuItemCustom = 0;
        public const int MenuItemAction = 1;
        public const int MenuItemId = 2;
        public const int MenuItemName = 3;
        public const int MenuItemHint = 8;
        public const int MenuItemTag = 9;
        public const int MenuItemEnabled = 4;
        public const int MenuItemStyle = 5;
        public const int MenuItemEvent = 6;
        public const int MenuItemEventOnShow = 7;
        public const int MenuItemGlyph = 10;
        public const int MenuItemParent = 11;
        public const int MenuItemVisible = 12;
        public const int MenuItemChecked = 13;
        public const int MenuItemDefault = 14;
        public const int MenuItemShortcut = 15;

        // IAIMPFileInfo (subset used by the sample file info provider)
        public const int FileInfoAlbum = 1;
        public const int FileInfoAlbumArt = 2;
        public const int FileInfoAlbumArtist = 3;
        public const int FileInfoArtist = 6;
        public const int FileInfoBitRate = 7;
        public const int FileInfoComment = 10;
        public const int FileInfoDuration = 17;
        public const int FileInfoFileName = 18;
        public const int FileInfoFileSize = 19;
        public const int FileInfoGenre = 20;
        public const int FileInfoTitle = 25;
        public const int FileInfoTrackNumber = 27;
        public const int FileInfoKey = 46;

        // Connection settings (apiInternet.h)
        public const int ConnectionType = 1;
        public const int ConnectionProxyServer = 2;
        public const int ConnectionProxyPort = 3;
        public const int ConnectionProxyUserName = 4;
        public const int ConnectionProxyUserPass = 5;
        public const int ConnectionTimeout = 6;
        public const int ConnectionUserAgent = 7;

        // Player (apiPlayer.h)
        public const int PlayerStopAfterTrack = 1;
        public const int PlayerAutoJumpToNextTrack = 2;
        public const int PlayerAutoSwitching = 10;
        public const int PlayerAutoSwitchingCrossfade = 11;
        public const int PlayerAutoSwitchingFadeIn = 12;
        public const int PlayerAutoSwitchingFadeOut = 13;
        public const int PlayerAutoSwitchingPauseBetweenTracks = 14;
        public const int PlayerManualSwitching = 20;
        public const int PlayerManualSwitchingCrossfade = 21;
        public const int PlayerManualSwitchingFadeIn = 22;
        public const int PlayerManualSwitchingFadeOut = 23;

        // Playback queue item (apiPlayer.h)
        public const int PlaybackQueueItemCustom = 0;
        public const int PlaybackQueueItemPlaylistItem = 1;
        public const int PlaybackQueueItemOffset = 2;

        // Lyrics (apiLyrics.h)
        public const int LyricsText = 1;
        public const int LyricsType = 2;
        public const int LyricsLyricist = 3;
        public const int LyricsOffset = 4;
        public const int LyricsAlbum = 5;
        public const int LyricsTitle = 6;
        public const int LyricsCreator = 7;
        public const int LyricsApplication = 8;
        public const int LyricsApplicationVersion = 9;

        // File tag (apiTagEditor.h)
        public const int FileTagId = 101;
        public const int FileTagDeleteOnSaving = 102;

        // Album art request (apiAlbumArt.h)
        public const int AlbumArtFindInFiles = 1;
        public const int AlbumArtFindInFilesMasks = 2;
        public const int AlbumArtFindInFilesExtensions = 3;
        public const int AlbumArtFindInInternet = 4;
        public const int AlbumArtFindInInternetMaxFileSize = 5;
        public const int AlbumArtFindInTags = 6;
        public const int AlbumArtResults = 7;
        public const int AlbumArtUserAction = 8;
    }
}