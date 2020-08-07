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

// ReSharper disable InconsistentNaming
// ReSharper disable UnusedMember.Global

namespace AIMP.SDK.MessageDispatcher
{
    /// <summary>
    /// Class Constants.
    /// </summary>
    internal class Constants
    {
        /// <summary>
        /// The message command base
        /// </summary>
        internal const int MessageCommandBase = 0;

        /// <summary>
        /// The base event
        /// </summary>
        internal const int BaseEvent = 0x2000;

        /// <summary>
        /// The message property base
        /// </summary>
        internal const int MessagePropertyBase = 0x1000;
    }

    /// <summary>
    /// Core message type.
    /// </summary>
    public enum AimpCoreMessageType
    {
        #region Message

        /// <summary>
        /// This messages provides an ability to check command accessibility.
        /// <note><li>Param1: Command ID. See the "Commands" charter.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdStateGet = Constants.MessageCommandBase + 1,

        /// <summary>
        /// Show the "Quick File Information" card for playable file.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdQFIPlaybackTrack = Constants.MessageCommandBase + 2,

        /// <summary>
        /// Show custom text in the running line or text box.
        /// <note><li>
        /// Param1: 0 - text will be automatically hidden (delay before hiding is 2 seconds), 1 - text will be hidden
        /// manually (you must send message with Param2 set to nil / null).
        /// </li><li>
        /// Param2: Showing text: pointer to first element of null-terminating widechar array Hiding text: nil / null
        /// (for Param set to 1 only)
        /// </li></note>
        /// </summary>
        CmdShowNotification = Constants.MessageCommandBase + 3,

        /// <summary>
        /// Toggles state of the "Repeat part A-B" function.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdTogglePartRepeat = Constants.MessageCommandBase + 5,

        /// <summary>
        /// Show the "About" dialog.
        /// <note>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdAbout = Constants.MessageCommandBase + 6,

        /// <summary>
        /// Show options dialog.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdOptions = Constants.MessageCommandBase + 7,

        /// <summary>
        /// Show options dialog and activate the "Plugins" sheet.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlugins = Constants.MessageCommandBase + 8,

        /// <summary>
        /// Close the application.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdQuit = Constants.MessageCommandBase + 9,

        /// <summary>
        /// Show settings dialog of the "Simple Scheduler" plugin.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdScheduler = Constants.MessageCommandBase + 11,

        /// <summary>
        /// Next visualization.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdVisualNext = Constants.MessageCommandBase + 12,

        /// <summary>
        /// Previous visualization.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdVisualPrev = Constants.MessageCommandBase + 13,

        /// <summary>
        /// If player is stopped - starts playback. If player is paused - resumes playback. If player is playing - start
        /// playing from beginning.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlay = Constants.MessageCommandBase + 14,

        /// <summary>
        /// If player is stopped - starts playback. If player is paused - resumes playback. If player is playing - pauses
        /// playback.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlayPause = Constants.MessageCommandBase + 15,

        /// <summary>
        /// Start playback of previous playing playlist.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPrevPlaylist = Constants.MessageCommandBase + 16,

        /// <summary>
        /// Pause / Resume.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPause = Constants.MessageCommandBase + 17,

        /// <summary>
        /// Stop playback.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdStop = Constants.MessageCommandBase + 18,

        /// <summary>
        /// Jump to next track.
        /// <note>
        /// Note that function doesn't check if file playback really started. It just put the file into queue of loading
        /// thread (Refer to the AIMP_MSG_EVENT_STREAM_START).
        /// </note><p>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </p>
        /// </summary>
        CmdNext = Constants.MessageCommandBase + 19,

        /// <summary>
        /// Previous track. Note 1: Note that function doesn't check if file playback really started. It just put the file into
        /// queue of loading thread (Refer to the AIMP_MSG_EVENT_STREAM_START).
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPrev = Constants.MessageCommandBase + 20,

        /// <summary>
        /// Show the "Open files" dialog.
        /// <p>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </p>
        /// </summary>
        CmdOpenFiles = Constants.MessageCommandBase + 21,

        /// <summary>
        /// Show the "Open folders" dialog.
        /// <p>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </p>
        /// </summary>
        CmdOpenFolders = Constants.MessageCommandBase + 22,

        /// <summary>
        /// Show the "Open Playlists" dialog.
        /// <p>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </p>
        /// </summary>
        CmdOpenPlaylists = Constants.MessageCommandBase + 23,

        /// <summary>
        /// Show the "Save Playlist" dialog
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdSavePlaylists = Constants.MessageCommandBase + 24,

        /// <summary>
        /// Show the "Bookmarks Manager" dialog.
        /// <note>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdBookmarks = Constants.MessageCommandBase + 25,

        /// <summary>
        /// Add file(s) to bookmarks.
        /// <note>
        /// Param1 - 0 - add playing file, 1 - add selected files from active playlist
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdBookmarksAdd = Constants.MessageCommandBase + 26,

        /// <summary>
        /// Reload file tags for all tracks in active playlist
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistRescan = Constants.MessageCommandBase + 27,

        /// <summary>
        /// Activate playable playlist and focus playable file.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistFocusPlayable = Constants.MessageCommandBase + 28,

        /// <summary>
        /// Delete all tracks from active playlist.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteAll = Constants.MessageCommandBase + 29,

        /// <summary>
        /// Remove non exists tracks from active playlist.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteNonExists = Constants.MessageCommandBase + 30,

        /// <summary>
        /// Remove all tracks from active playlist except selected.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteNonSelected = Constants.MessageCommandBase + 31,

        /// <summary>
        /// Remove playable file from disk drive.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeletePlayingFromHDD = Constants.MessageCommandBase + 32,

        /// <summary>
        /// Delete selected tracks from active playlist.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteSelected = Constants.MessageCommandBase + 33,

        /// <summary>
        /// Delete selected tracks from disk drive.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdDeleteSelectedFromHDD = Constants.MessageCommandBase + 34,

        /// <summary>
        /// Delete switched off tracks from active playlist.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteSwitchedOff = Constants.MessageCommandBase + 35,

        /// <summary>
        /// Delete switched off tracks from disk drive.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteSwitchedOffFromHDD = Constants.MessageCommandBase + 36,

        /// <summary>
        /// Delete duplicate tracks from active playlist. Tracks will be compared by full file name.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistDeleteDuplicates = Constants.MessageCommandBase + 37,

        /// <summary>
        /// Sort tracks in active playlist by artist field.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSortByArtist = Constants.MessageCommandBase + 38,

        /// <summary>
        /// Sort tracks in active playlist by title.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSortByTitle = Constants.MessageCommandBase + 39,

        /// <summary>
        /// Sort tracks in active playlist by path.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSortByPath = Constants.MessageCommandBase + 40,

        /// <summary>
        /// Sort tracks in active playlist by duration field.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSortByDuration = Constants.MessageCommandBase + 41,

        /// <summary>
        /// Shuffle tracks in active playlists.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSortRandomize = Constants.MessageCommandBase + 42,

        /// <summary>
        /// Invert tracks in active playlists.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSortInvert = Constants.MessageCommandBase + 43,

        /// <summary>
        /// Switch on auto playing marker for selected tracks in active playlist
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSwitchOn = Constants.MessageCommandBase + 44,

        /// <summary>
        /// Switch off auto playing marker for selected tracks in active playlist.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistSwitchOff = Constants.MessageCommandBase + 45,

        /// <summary>
        /// Show the "File Adding" dialog.
        /// <note>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdAddFiles = Constants.MessageCommandBase + 46,

        /// <summary>
        /// Show the "Folder adding" dialog.
        /// <note>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdAddFolders = Constants.MessageCommandBase + 47,

        /// <summary>
        /// Show the "Playlists adding" dialog.
        /// <note>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdAddPlaylists = Constants.MessageCommandBase + 48,

        /// <summary>
        /// Show the "Add URL" dialog.
        /// <note>
        /// Param1 - Not used.
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdAddUrl = Constants.MessageCommandBase + 49,

        /// <summary>
        /// Show the "File Information" dialog for playable track.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdQTEPlayableTrack = Constants.MessageCommandBase + 51,

        /// <summary>
        /// Show the "Advanced Search" dialog.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdSearch = Constants.MessageCommandBase + 52,

        /// <summary>
        /// Show the "DSP Manager" dialog.
        /// <note>
        /// Param1 - Index of tab sheet to active, 0..3. 0 - Common settings (default) 1 - Equalizer 2 - Volume
        /// normalization 3 - Cross mixing settings
        /// Param2 - Not used.
        /// </note>
        /// </summary>
        CmdDSPManager = Constants.MessageCommandBase + 53,

        /// <summary>
        /// The command DSP manager eq
        /// </summary>
        CmdDSPManagerEQ = Constants.MessageCommandBase + 54,

        /// <summary>
        /// Synchronize active playlist with preimage if it presents.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdPlaylistReloadFromPreimage = Constants.MessageCommandBase + 55,

        /// <summary>
        /// The command DSP manager crossmixing
        /// </summary>
        CmdDspManagerCrossmixing = Constants.MessageCommandBase + 56,

        /// <summary>
        /// Starts previous selected by user visualization. If visualization is not found - first will be started.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdVisualStart = Constants.MessageCommandBase + 57,

        /// <summary>
        /// Stop visualization.
        /// <note><li>Param1 - Not used.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        CmdVisualStop = Constants.MessageCommandBase + 58,

        #endregion

        #region Events

        /// <summary>
        /// Command state has been changed.
        /// <note><li>Param1: Command ID. See the "Commands" charter.</li><li>Param2 - Not used.</li></note>
        /// </summary>
        EventCmdState = Constants.BaseEvent + 1,

        /// <summary>
        /// Event occurs when some settings have been changed.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventOptions = Constants.BaseEvent + 2,

        /// <summary>
        /// Event occurs when playback of track has been started.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventStreamStart = Constants.BaseEvent + 3,

        /// <summary>
        /// This event like to AIMP_MSG_EVENT_STREAM_START, but it occurs when playing radio stream and track has been changed.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventStreamStartSubtrack = Constants.BaseEvent + 4,

        /// <summary>
        /// Event occurs when track has been finished.
        /// <note><li>Param1: Contains zero or combination of following flags: AIMP_MES_END_OF_QUEUE, AIMP_MES_END_OF_PLAYLIST.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventStreamEnd = Constants.BaseEvent + 5,

        /// <summary>
        /// Event occurs when player state has been changed.
        /// <note><li>Param1: 0 - Stopped, 1 - Paused, 2 - Playing.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventPlayerState = Constants.BaseEvent + 6,

        /// <summary>
        /// Event occurs when property value has been changed. See the "Properties" charter.
        /// <note><li>Param1: Property ID.</li><li>Param2: This parameter is same to Param2 for specified property.</li></note>
        /// </summary>
        EventPropertyValue = Constants.BaseEvent + 7,

        /// <summary>
        /// Event occurs when list of sheet for Options Dialog has been changed.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventOptionsFrameList = Constants.BaseEvent + 8,

        /// <summary>
        /// Event occurs when one of settings in the Option Dialog sheet has been changed by user.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventOptionsFrameModified = Constants.BaseEvent + 9,

        /// <summary>
        /// Event occurs when switching between visualizations.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventVisualPlugin = Constants.BaseEvent + 11,

        /// <summary>
        /// Event occurs when file mark has been changed.
        /// <note><li>Param1: New mark (from 0 to 5)</li><li>
        /// Param2: File name - pointer to first element of null terminated widechar-array. If file name is nil / null
        /// or empty its mean that marks for all files have been changed.
        /// </li></note>
        /// </summary>
        EventFileMark = Constants.BaseEvent + 12,

        /// <summary>
        /// Event occurs when statistics has been changed.
        /// <note><li>Param1: Not used.</li><li>
        /// Param2: File name - pointer to first element of null-terminated widechar-array. If file name is nil / null
        /// or empty its mean that statistic for all files have been changed.
        /// </li></note>
        /// </summary>
        EventStatisticsChanged = Constants.BaseEvent + 14,

        /// <summary>
        /// Event occurs when skin has been applied.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventSkin = Constants.BaseEvent + 15,

        /// <summary>
        /// Unlike the AIMP_MSG_EVENT_PROPERTY_VALUE event for the AIMP_MSG_PROPERTY_PLAYER_POSITION property, this event
        /// occurs even second. This event can be useful for update information about the playable track.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventPlayerUpdatePosition = Constants.BaseEvent + 16,

        /// <summary>
        /// Event occurs when localization has been changed.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventLanguage = Constants.BaseEvent + 17,

        /// <summary>
        /// Event occurs when application completely initialized.
        /// <note>
        /// Note that plugin can be loaded after program initialization. You should check current state via the
        /// AIMP_MSG_PROPERTY_LOADED property if it needed.
        /// </note><note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventLoaded = Constants.BaseEvent + 18,

        /// <summary>
        /// Event occurs when closing the application.
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventTerminating = Constants.BaseEvent + 19,

        /// <summary>
        /// Event occurs when information about the playable file has been changed.
        /// Event not occurs:
        /// 1. On start playback (See AIMP_MSG_EVENT_STREAM_START, AIMP_MSG_EVENT_STREAM_START_SUBTRACK)
        /// 2. On stop playback(See AIMP_MSG_EVENT_STREAM_END)
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventPlayableFileInfo = Constants.BaseEvent + 20,

        /// <summary>
        /// Unlike the AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION event this event has higher resolution (about 10-15 calls per
        /// second).
        /// <note><li>Param1: Not used.</li><li>Param2: Not used.</li></note>
        /// </summary>
        EventPlayerUpdatePositionHr = Constants.BaseEvent + 21,

        /// <summary>
        /// Event occurs when name of currently used preset has been changed.
        /// <note><li>Param1: Not used</li><li>Param2: Pointer to WideChar array, can be = nil (ReadOnly!)</li></note>
        /// </summary>
        EventEqualizerPresetName = Constants.BaseEvent + 22,

        #endregion

        #region Properties

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.0 .. 1.0
        /// </li>
        /// </note>
        /// </summary>
        PropertyVolume = Constants.MessagePropertyBase + 1,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li>
        /// </note>
        /// </summary>
        PropertyMute = Constants.MessagePropertyBase + 2,

        /// <summary>
        /// Balance.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: -1.0 .. +1.0
        /// Default: 0.0
        /// </li></note>
        /// </summary>
        PropertyBalance = Constants.MessagePropertyBase + 3,

        /// <summary>
        /// Chorus effect.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.0 .. 1.0
        /// Default: 0.0 (switched off)
        /// </li></note>
        /// </summary>
        PropertyChorus = Constants.MessagePropertyBase + 4,

        /// <summary>
        /// Echo effect.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.0 .. 1.0
        /// Default: 0.0 (switched off)
        /// </li></note>
        /// </summary>
        PropertyEcho = Constants.MessagePropertyBase + 5,

        /// <summary>
        /// Enhancer effect.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 1.0 .. 5.0
        /// Default: 1.0 (switched off)
        /// </li></note>
        /// </summary>
        PropertyEnhancer = Constants.MessagePropertyBase + 6,

        /// <summary>
        /// Flanger effect.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.0 .. 1.0
        /// Default: 0.0 (switched off)
        /// </li></note>
        /// </summary>
        PropertyFlanger = Constants.MessagePropertyBase + 7,

        /// <summary>
        /// Reverb effect.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.0 .. 1.0
        /// Default: 0.0 (switched off)
        /// </li></note>
        /// </summary>
        PropertyReverb = Constants.MessagePropertyBase + 8,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: -10.0 .. 10.0
        /// Default: 0.0 (switched off)
        /// </li>
        /// </note>
        /// </summary>
        PropertyPitch = Constants.MessagePropertyBase + 9,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.5 .. 1.5 (50% .. 150%)
        /// Default: 1.0 (100%)
        /// </li>
        /// </note>
        /// </summary>
        PropertySpeed = Constants.MessagePropertyBase + 10,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Values: 0.8 .. 1.5 (80% .. 150%)
        /// Default: 1.0 (100%)
        /// </li>
        /// </note>
        /// </summary>
        PropertyTempo = Constants.MessagePropertyBase + 11,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: 0.0 .. 2.0
        /// Default: 0.0 (switched off)
        /// </li>
        /// </note>
        /// </summary>
        PropertyTruebass = Constants.MessagePropertyBase + 12,

        /// <summary>
        /// Preamp. Equalizer must be switched on, see AIMP_MSG_PROPERTY_EQUALIZER.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: -15.0 .. 15.0 dB
        /// Default: 0.0 dB
        /// </li></note>
        /// </summary>
        PropertyPreamp = Constants.MessagePropertyBase + 13,

        /// <summary>
        /// Equalizer state (switched on / off).
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyEqualizer = Constants.MessagePropertyBase + 14,

        /// <summary>
        /// <note>
        ///   <li>
        /// Param1: LoWord: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
        /// HiWord: Band Index (from 0 to 17)
        /// </li>
        ///   <li>
        /// Param2: Pointer to the 32-bit floating point variable (Single).
        /// Range: -15.0 .. 15.0 dB
        /// Default: 0.0 dB
        /// </li>
        /// </note>
        /// </summary>
        PropertyEqualizerBand = Constants.MessagePropertyBase + 15,

        /// <summary>
        /// <note>
        ///   <li>Param1: AIMP_MSG_PROPVALUE_GET. Read Only.</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit integer variable (Integer).
        /// 0 = Stopped
        /// 1 = Paused
        /// 2 = Playing
        /// </li>
        /// </note>
        /// </summary>
        PropertyPlayerState = Constants.MessagePropertyBase + 16,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET).</li>
        ///   <li>Param2: Pointer to the 32-bit floating point variable (Single). Value is defined in seconds.</li>
        /// </note>
        /// </summary>
        PropertyPlayerPosition = Constants.MessagePropertyBase + 17,

        /// <summary>
        /// <note>
        ///   <li>Param1: AIMP_MSG_PROPVALUE_GET. Read Only</li>
        ///   <li>Param2: Pointer to the 32-bit floating point variable (Single). Value is defined in seconds.</li>
        /// </note>
        /// </summary>
        PropertyPlayerDuration = Constants.MessagePropertyBase + 18,

        /// <summary>
        /// Part repeat state. Read only.
        /// <note><li>Param1: AIMP_MSG_PROPVALUE_GET Read Only</li><li>
        /// Param2: Pointer to the 32-bit integer variable (Integer).
        /// 0 - Repeat is switched off
        /// 1 - Point "A" is defined
        /// 2 - Point "B" is defined, repeat is switched on
        /// </li></note>
        /// </summary>
        PropertyPartRepeat = Constants.MessagePropertyBase + 19,

        /// <summary>
        /// Track repeat state.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Value: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyRepeat = Constants.MessagePropertyBase + 20,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Value: False / True
        /// Default: False
        /// </li>
        /// </note>
        /// </summary>
        PropertyShuffle = Constants.MessagePropertyBase + 21,

        /// <summary>
        /// Handle of one of application windows. Read only.
        /// <note><li>
        /// Param1: One of following values:
        /// AIMP_MPH_MAINFORM
        /// AIMP_MPH_APPLICATION
        /// AIMP_MPH_TRAYCONTROL
        /// AIMP_MPH_PLAYLISTFORM
        /// AIMP_MPH_EQUALIZERFORM
        /// </li><li>Param2: Pointer to the HWND.</li></note>
        /// </summary>
        PropertyHwnd = Constants.MessagePropertyBase + 22,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Value: False / True
        /// Default: False
        /// </li>
        /// </note>
        /// </summary>
        PropertyStayOnTop = Constants.MessagePropertyBase + 23,

        /// <summary>
        /// Switching on/off countdown mode of playback time.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Value: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyReverseTime = Constants.MessagePropertyBase + 24,

        /// <summary>
        /// <note>
        ///   <li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li>
        ///   <li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li>
        /// </note>
        /// </summary>
        PropertyMinimizedToTray = Constants.MessagePropertyBase + 25,

        /// <summary>
        /// State of "repeat single file playlists" option. It is actual for "repeat playlist" mode only (see
        /// AIMP_MSG_PROPERTY_ACTION_ON_END_OF_PLAYLIST).
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyRepeatSingleFilePlaylists = Constants.MessagePropertyBase + 26,

        /// <summary>
        /// Action on end of playlist.
        /// <note><li>
        /// Param1: Access direction: Read / Write (<see cref="AimpCoreMessageType.AIMP_MSG_PROPVALUE_GET" /> /
        /// <see cref="AimpCoreMessageType.AIMP_MSG_PROPVALUE_SET" />)
        /// </li><li>
        /// Param2: Pointer to the 32-bit integer variable (Integer).
        /// 0 - Jump to the next playlist
        /// 1 - Repeat current playlist
        /// 2 - Stand by
        /// </li></note>
        /// </summary>
        PropertyActionOnEndOfPlaylist = Constants.MessagePropertyBase + 27,

        /// <summary>
        /// Stop playback after playable file will finished.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyStopAfterTrack = Constants.MessagePropertyBase + 28,

        /// <summary>
        /// State of internet radio capture.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyRadioCap = Constants.MessagePropertyBase + 29,

        /// <summary>
        /// Property shows whether an application is initialized.
        /// <note><li>Param1: AIMP_MSG_PROPVALUE_GET. Read Only</li><li>Param2: Pointer to LongBool.</li></note>
        /// </summary>
        PropertyLoaded = Constants.MessagePropertyBase + 30,

        /// <summary>
        /// Full screen visualization mode.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>
        /// Param2: Pointer to the 32-bit logical variable (LongBool).
        /// Values: False / True
        /// Default: False
        /// </li></note>
        /// </summary>
        PropertyVisualFullscreen = Constants.MessagePropertyBase + 31,

        /// <summary>
        /// Displays buffering progress of playing track.
        /// <note><li>Param1: Access direction: Read / Write (AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET)</li><li>Param2: Pointer to the 32-bit floating point variable (Single). Value in percents (from 0.0 to 100.0 %)</li></note>
        /// </summary>
        PropertyPlayerBuffering = Constants.MessagePropertyBase + 32

        #endregion
    }


    /// <summary>
    /// Path type.
    /// </summary>
    public enum AimpCorePathType
    {
        /// <summary>
        /// Path to audiolibrary.
        /// </summary>
        Audiolibrary = 6,

        /// <summary>
        /// Path to encoders.
        /// </summary>
        Encoders = 8,

        /// <summary>
        /// Path to help files.
        /// </summary>
        Help = 9,

        /// <summary>
        /// Path to icons.
        /// </summary>
        Icons = 5,

        /// <summary>
        /// Path to language files.
        /// </summary>
        Langs = 2,

        /// <summary>
        /// Path to playlist.
        /// </summary>
        Playlists = 1,

        /// <summary>
        /// Path to plugins.
        /// </summary>
        Plugins = 4,

        /// <summary>
        /// Path to profile.
        /// </summary>
        Profile = 0,

        /// <summary>
        /// Path to skins.
        /// </summary>
        Skins = 3,

        /// <summary>
        /// Path to common skins.
        /// </summary>
        SkinsCommon = 11
    }
}
