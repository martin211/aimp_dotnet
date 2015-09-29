namespace AIMP.SDK
{
    public static class AimpMessages
    {
        private const int AIMP_MSG_CMD_BASE = 0;

        private const int BaseEvent = 0x2000;

        private const int AIMP_MSG_PROPERTY_BASE = 0x1000;

        
        /// <summary>
        /// Path type.
        /// </summary>
        public enum AimpCorePathType
        {
            /// <summary>
            /// Path to audiolibrary.
            /// </summary>
            AIMP_CORE_PATH_AUDIOLIBRARY = 6,

            /// <summary>
            /// Path to encoders.
            /// </summary>
            AIMP_CORE_PATH_ENCODERS = 8,

            /// <summary>
            /// Path to help files.
            /// </summary>
            AIMP_CORE_PATH_HELP = 9,

            /// <summary>
            /// Path to icons.
            /// </summary>
            AIMP_CORE_PATH_ICONS = 5,

            /// <summary>
            /// Path to language files.
            /// </summary>
            AIMP_CORE_PATH_LANGS = 2,

            /// <summary>
            /// Path to playlist.
            /// </summary>
            AIMP_CORE_PATH_PLAYLISTS = 1,

            /// <summary>
            /// Path to plugins.
            /// </summary>
            AIMP_CORE_PATH_PLUGINS = 4,

            /// <summary>
            /// Path to profile.
            /// </summary>
            AIMP_CORE_PATH_PROFILE = 0,

            /// <summary>
            /// Path to skins.
            /// </summary>
            AIMP_CORE_PATH_SKINS = 3,

            /// <summary>
            /// Path to common skins.
            /// </summary>
            AIMP_CORE_PATH_SKINS_COMMON = 11
        }

        /// <summary>
        /// Core message type.
        /// </summary>
        public enum AimpCoreMessageType
        {
            #region Message

            AIMP_MSG_CMD_STATE_GET = AIMP_MSG_CMD_BASE + 1,

            AIMP_MSG_CMD_QFI_PLAYBACK_TRACK = AIMP_MSG_CMD_BASE + 2,

            AIMP_MSG_CMD_SHOW_NOTIFICATION = AIMP_MSG_CMD_BASE + 3,

            AIMP_MSG_CMD_TOGGLE_PARTREPEAT = AIMP_MSG_CMD_BASE + 5,

            AIMP_MSG_CMD_ABOUT = AIMP_MSG_CMD_BASE + 6,

            AIMP_MSG_CMD_OPTIONS = AIMP_MSG_CMD_BASE + 7,

            AIMP_MSG_CMD_PLUGINS = AIMP_MSG_CMD_BASE + 8,

            AIMP_MSG_CMD_QUIT = AIMP_MSG_CMD_BASE + 9,

            AIMP_MSG_CMD_SCHEDULER = AIMP_MSG_CMD_BASE + 11,

            AIMP_MSG_CMD_VISUAL_NEXT = AIMP_MSG_CMD_BASE + 12,

            AIMP_MSG_CMD_VISUAL_PREV = AIMP_MSG_CMD_BASE + 13,

            AIMP_MSG_CMD_PLAY = AIMP_MSG_CMD_BASE + 14,

            AIMP_MSG_CMD_PLAYPAUSE = AIMP_MSG_CMD_BASE + 15,

            AIMP_MSG_CMD_PLAY_PREV_PLAYLIST = AIMP_MSG_CMD_BASE + 16,

            AIMP_MSG_CMD_PAUSE = AIMP_MSG_CMD_BASE + 17,

            AIMP_MSG_CMD_STOP = AIMP_MSG_CMD_BASE + 18,

            AIMP_MSG_CMD_NEXT = AIMP_MSG_CMD_BASE + 19,

            AIMP_MSG_CMD_PREV = AIMP_MSG_CMD_BASE + 20,

            AIMP_MSG_CMD_OPEN_FILES = AIMP_MSG_CMD_BASE + 21,

            AIMP_MSG_CMD_OPEN_FOLDERS = AIMP_MSG_CMD_BASE + 22,

            AIMP_MSG_CMD_OPEN_PLAYLISTS  = AIMP_MSG_CMD_BASE + 23,

            AIMP_MSG_CMD_SAVE_PLAYLISTS  = AIMP_MSG_CMD_BASE + 24,

            AIMP_MSG_CMD_BOOKMARKS = AIMP_MSG_CMD_BASE + 25,

            AIMP_MSG_CMD_BOOKMARKS_ADD = AIMP_MSG_CMD_BASE + 26,

            AIMP_MSG_CMD_PLS_RESCAN  = AIMP_MSG_CMD_BASE + 27,

            AIMP_MSG_CMD_PLS_FOCUS_PLAYABLE = AIMP_MSG_CMD_BASE + 28,

            AIMP_MSG_CMD_PLS_DELETE_ALL = AIMP_MSG_CMD_BASE + 29,

            AIMP_MSG_CMD_PLS_DELETE_NON_EXISTS = AIMP_MSG_CMD_BASE + 30,

            AIMP_MSG_CMD_PLS_DELETE_NON_SELECTED = AIMP_MSG_CMD_BASE + 31,

            AIMP_MSG_CMD_PLS_DELETE_PLAYING_FROM_HDD = AIMP_MSG_CMD_BASE + 32,

            AIMP_MSG_CMD_PLS_DELETE_SELECTED = AIMP_MSG_CMD_BASE + 33,

            AIMP_MSG_CMD_PLS_DELETE_SELECTED_FROM_HDD = AIMP_MSG_CMD_BASE + 34,

            AIMP_MSG_CMD_PLS_DELETE_SWITCHEDOFF = AIMP_MSG_CMD_BASE + 35,

            AIMP_MSG_CMD_PLS_DELETE_SWITCHEDOFF_FROM_HDD = AIMP_MSG_CMD_BASE + 36,

            AIMP_MSG_CMD_PLS_DELETE_DUPLICATES = AIMP_MSG_CMD_BASE + 37,

            AIMP_MSG_CMD_PLS_SORT_BY_ARTIST = AIMP_MSG_CMD_BASE + 38,

            AIMP_MSG_CMD_PLS_SORT_BY_TITLE = AIMP_MSG_CMD_BASE + 39,

            AIMP_MSG_CMD_PLS_SORT_BY_PATH = AIMP_MSG_CMD_BASE + 40,

            AIMP_MSG_CMD_PLS_SORT_BY_DURATION = AIMP_MSG_CMD_BASE + 41,

            AIMP_MSG_CMD_PLS_SORT_RANDOMIZE = AIMP_MSG_CMD_BASE + 42,

            AIMP_MSG_CMD_PLS_SORT_INVERT = AIMP_MSG_CMD_BASE + 43,

            AIMP_MSG_CMD_PLS_SWITCH_ON = AIMP_MSG_CMD_BASE + 44,

            AIMP_MSG_CMD_PLS_SWITCH_OFF = AIMP_MSG_CMD_BASE + 45,

            AIMP_MSG_CMD_ADD_FILES = AIMP_MSG_CMD_BASE + 46,

            AIMP_MSG_CMD_ADD_FOLDERS = AIMP_MSG_CMD_BASE + 47,

            AIMP_MSG_CMD_ADD_PLAYLISTS = AIMP_MSG_CMD_BASE + 48,

            AIMP_MSG_CMD_ADD_URL = AIMP_MSG_CMD_BASE + 49,

            AIMP_MSG_CMD_QTE_PLAYABLE_TRACK = AIMP_MSG_CMD_BASE + 51,

            AIMP_MSG_CMD_SEARCH = AIMP_MSG_CMD_BASE + 52,

            AIMP_MSG_CMD_DSPMANAGER = AIMP_MSG_CMD_BASE + 53,

            AIMP_MSG_CMD_DSPMANAGER_EQ = AIMP_MSG_CMD_BASE + 54,

            AIMP_MSG_CMD_PLS_RELOAD_FROM_PREIMAGE = AIMP_MSG_CMD_BASE + 55,

            AIMP_MSG_CMD_DSPMANAGER_CROSSMIXING = AIMP_MSG_CMD_BASE + 56,

            AIMP_MSG_CMD_VISUAL_START = AIMP_MSG_CMD_BASE + 57,

            IMP_MSG_CMD_VISUAL_STOP = AIMP_MSG_CMD_BASE + 58,

            #endregion

            #region Events
            /// <summary>
            /// Command state has been changed.
            /// </summary>
            AIMP_MSG_EVENT_CMD_STATE = BaseEvent + 1,

            /// <summary>
            /// The Options has been changed.
            /// </summary>
            AIMP_MSG_EVENT_OPTIONS = BaseEvent + 2,

            /// <summary>
            /// Audio stream starts playing.
            /// </summary>
            AIMP_MSG_EVENT_STREAM_START = BaseEvent + 3,

            /// <summary>
            /// Similar to AIMP_MSG_EVENT_STREAM_START event, but called when an Internet radio station changes the track.
            /// </summary>
            AIMP_MSG_EVENT_STREAM_START_SUBTRACK = BaseEvent + 4,

            /// <summary>
            /// Audio stream has been finished.
            /// </summary>
            AIMP_MSG_EVENT_STREAM_END = BaseEvent + 5,

            /// <summary>
            /// Player state has been changed.
            /// </summary>
            AIMP_MSG_EVENT_PLAYER_STATE = BaseEvent + 6,

            /// <summary>
            /// The property value has been changed.
            /// </summary>
            AIMP_MSG_EVENT_PROPERTY_VALUE = BaseEvent + 7,

            /// <summary>
            /// Options frame has been added or removed.
            /// </summary>
            AIMP_MSG_EVENT_OPTIONS_FRAME_LIST = BaseEvent + 8,

            /// <summary>
            /// Options frame content has been changed.
            /// </summary>
            AIMP_MSG_EVENT_OPTIONS_FRAME_MODIFIED = BaseEvent + 9,

            /// <summary>
            /// Visulal plugin has been changed.
            /// </summary>
            AIMP_MSG_EVENT_VISUAL_PLUGIN = BaseEvent + 11,

            /// <summary>
            /// The file mark has been changed.
            /// </summary>
            AIMP_MSG_EVENT_FILEMARK = BaseEvent + 12,

            /// <summary>
            /// 
            /// </summary>
            AIMP_MSG_EVENT_STATISTICS_CHANGED = BaseEvent + 14,

            AIMP_MSG_EVENT_SKIN = BaseEvent + 15,

            AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION = BaseEvent + 16,

            AIMP_MSG_EVENT_LANGUAGE = BaseEvent + 17,

            AIMP_MSG_EVENT_TERMINATING = BaseEvent + 19,

            AIMP_MSG_EVENT_PLAYABLE_FILE_INFO = BaseEvent + 20,

            #endregion

            #region Properties

            AIMP_MSG_PROPERTY_VOLUME = AIMP_MSG_PROPERTY_BASE + 1,

            AIMP_MSG_PROPERTY_MUTE = AIMP_MSG_PROPERTY_BASE + 2,

            AIMP_MSG_PROPERTY_BALANCE = AIMP_MSG_PROPERTY_BASE + 3,

            AIMP_MSG_PROPERTY_CHORUS = AIMP_MSG_PROPERTY_BASE + 4,

            AIMP_MSG_PROPERTY_ECHO = AIMP_MSG_PROPERTY_BASE + 5,

            AIMP_MSG_PROPERTY_ENHANCER = AIMP_MSG_PROPERTY_BASE + 6,

            AIMP_MSG_PROPERTY_FLANGER = AIMP_MSG_PROPERTY_BASE + 7,

            AIMP_MSG_PROPERTY_REVERB = AIMP_MSG_PROPERTY_BASE + 8,

            AIMP_MSG_PROPERTY_PITCH = AIMP_MSG_PROPERTY_BASE + 9,

            AIMP_MSG_PROPERTY_SPEED = AIMP_MSG_PROPERTY_BASE + 10,

            AIMP_MSG_PROPERTY_TEMPO = AIMP_MSG_PROPERTY_BASE + 11,

            AIMP_MSG_PROPERTY_TRUEBASS = AIMP_MSG_PROPERTY_BASE + 12,

            AIMP_MSG_PROPERTY_PREAMP = AIMP_MSG_PROPERTY_BASE + 13,

            AIMP_MSG_PROPERTY_EQUALIZER = AIMP_MSG_PROPERTY_BASE + 14,

            AIMP_MSG_PROPERTY_EQUALIZER_BAND = AIMP_MSG_PROPERTY_BASE + 15,  

            AIMP_MSG_PROPERTY_PLAYER_STATE = AIMP_MSG_PROPERTY_BASE + 16,

            AIMP_MSG_PROPERTY_PLAYER_POSITION = AIMP_MSG_PROPERTY_BASE + 17,

            AIMP_MSG_PROPERTY_PLAYER_DURATION = AIMP_MSG_PROPERTY_BASE + 18,

            AIMP_MSG_PROPERTY_PARTREPEAT = AIMP_MSG_PROPERTY_BASE + 19,

            AIMP_MSG_PROPERTY_REPEAT = AIMP_MSG_PROPERTY_BASE + 20,

            AIMP_MSG_PROPERTY_SHUFFLE = AIMP_MSG_PROPERTY_BASE + 21,

            AIMP_MSG_PROPERTY_HWND = AIMP_MSG_PROPERTY_BASE + 22,

            AIMP_MSG_PROPERTY_STAYONTOP = AIMP_MSG_PROPERTY_BASE + 23,

            AIMP_MSG_PROPERTY_REVERSETIME = AIMP_MSG_PROPERTY_BASE + 24,

            AIMP_MSG_PROPERTY_MINIMIZED_TO_TRAY = AIMP_MSG_PROPERTY_BASE + 25,

            AIMP_MSG_PROPERTY_REPEAT_SINGLE_FILE_PLAYLISTS = AIMP_MSG_PROPERTY_BASE + 26,

            AIMP_MSG_PROPERTY_ACTION_ON_END_OF_PLAYLIST = AIMP_MSG_PROPERTY_BASE + 27,

            AIMP_MSG_PROPERTY_STOP_AFTER_TRACK = AIMP_MSG_PROPERTY_BASE + 28,

            AIMP_MSG_PROPERTY_RADIOCAP = AIMP_MSG_PROPERTY_BASE + 29,

            AIMP_MSG_PROPERTY_LOADED = AIMP_MSG_PROPERTY_BASE + 30,

            AIMP_MSG_PROPERTY_VISUAL_FULLSCREEN = AIMP_MSG_PROPERTY_BASE + 31

            #endregion
        }
    }

    public enum AimpPlayerState
    {
        Stopped,

        Pause,

        Playing,
    }
}