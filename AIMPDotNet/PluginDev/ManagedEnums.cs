using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// AIMP event type
    /// </summary>
	public enum AIMP2CallbackType: uint
	{
        /// <summary>
        /// Staus was changed
        /// </summary>
		AIMP_STATUS_CHANGE = 1,
        /// <summary>
        /// Playing file
        /// </summary>
		AIMP_PLAY_FILE = 2,
        /// <summary>
        /// Update Info for current track
        /// </summary>
		AIMP_INFO_UPDATE = 5,
        /// <summary>
        /// Play/Pause/Stop
        /// </summary>
		AIMP_PLAYER_STATE = 11,
        /// <summary>
        /// Balance, Speed, Tempo, Pitch, Flanger and etc.
        /// </summary>
		AIMP_EFFECT_CHANGED = 12,
        /// <summary>
        /// Equalizer sliders changed
        /// </summary>
		AIMP_EQ_CHANGED = 13,
        /// <summary>
        /// Changed track position
        /// </summary>
		AIMP_TRACK_POS_CHANGED = 14
	};


	internal enum AIMPStatus: uint
	{
		AIMP_STS_VOLUME = 1,
		AIMP_STS_BALANCE = 2,
		AIMP_STS_SPEED = 3,
		AIMP_STS_PLAYER = 4,
		AIMP_STS_MUTE = 5,
		AIMP_STS_REVERB = 6,
		AIMP_STS_ECHO = 7,
		AIMP_STS_CHORUS = 8,
		AIMP_STS_FLANGER = 9,

		AIMP_STS_EQ_STS = 10,
		AIMP_STS_EQ_SLDR01 = 11,
		AIMP_STS_EQ_SLDR02 = 12,
		AIMP_STS_EQ_SLDR03 = 13,
		AIMP_STS_EQ_SLDR04 = 14,
		AIMP_STS_EQ_SLDR05 = 15,
		AIMP_STS_EQ_SLDR06 = 16,
		AIMP_STS_EQ_SLDR07 = 17,
		AIMP_STS_EQ_SLDR08 = 18,
		AIMP_STS_EQ_SLDR09 = 19,
		AIMP_STS_EQ_SLDR10 = 20,
		AIMP_STS_EQ_SLDR11 = 21,
		AIMP_STS_EQ_SLDR12 = 22,
		AIMP_STS_EQ_SLDR13 = 23,
		AIMP_STS_EQ_SLDR14 = 24,
		AIMP_STS_EQ_SLDR15 = 25,
		AIMP_STS_EQ_SLDR16 = 26,
		AIMP_STS_EQ_SLDR17 = 27,
		AIMP_STS_EQ_SLDR18 = 28,

		AIMP_STS_REPEAT = 29,
		AIMP_STS_ON_TOPMOST = 30,
		AIMP_STS_POS = 31,
		AIMP_STS_LENGTH = 32,
		AIMP_STS_REPEATPLS = 33,
		AIMP_STS_REP_PLS_1 = 34,
		AIMP_STS_KBPS = 35,
		AIMP_STS_KHZ = 36,
		AIMP_STS_MODE = 37,
		AIMP_STS_RADIO = 38,
		AIMP_STS_STREAM_TYPE = 39, // Music / CDA / Radio
		AIMP_STS_TIMER = 40, // Reverse / Normal
		AIMP_STS_SHUFFLE = 41,

		AIMP_STS_MAIN_HWND = 42,
		AIMP_STS_TC_HWND = 43,
		AIMP_STS_APP_HWND = 44,
		AIMP_STS_PL_HWND = 45,
		AIMP_STS_EQ_HWND = 46,

		AIMP_STS_TRAY = 47
	};

    /// <summary>
    /// Playing state
    /// </summary>
	public enum AIMPPlayingState: uint
	{
        /// <summary>
        /// Stopped
        /// </summary>
		Stoped = 0,
        /// <summary>
        /// Currently playing
        /// </summary>
		Playing = 1,
        /// <summary>
        /// Pause
        /// </summary>
		Paused = 2
	};

    /// <summary>
    /// Timer display style
    /// </summary>
	public enum AIMPTimerDisplayStyle: uint
	{
        /// <summary>
        /// Normal
        /// </summary>
		Normal = 0,
        /// <summary>
        /// Reverse
        /// </summary>
		Reverse = 1
	};

    /// <summary>
    /// Stream type
    /// </summary>
    public enum AIMPStreamType : uint
	{
        /// <summary>
        /// Music
        /// </summary>
		Music = 0,
        /// <summary>
        /// CD audio
        /// </summary>
		CDA = 1,
        /// <summary>
        /// Radio
        /// </summary>
		Radio = 2
	};

    /// <summary>
    /// Action, then playlist was finished
    /// </summary>
    public enum AIMPOnPlaylistEndAction : uint
    {
        /// <summary>
        /// Play Next
        /// </summary>
        PlayNext = 0,
        /// <summary>
        /// Repeate current
        /// </summary>
        RepeateCurrent = 1,
        /// <summary>
        /// Stop playing
        /// </summary>
        StopPlaying = 2
    };

    /// <summary>
    /// Type of file or directory for getting path 
    /// </summary>
    public enum AIMPPathToFile : uint
    {
        /// <summary>
        /// Path to configuration file
        /// </summary>
        AIMP_CFG_DATA = 0,
        /// <summary>
        /// Path to playlists
        /// </summary>
        AIMP_CFG_PLS = 1,
        /// <summary>
        /// Language file
        /// </summary>
        AIMP_CFG_LNG = 2,
        /// <summary>
        /// Skin file
        /// </summary>
        AIMP_CFG_SKINS = 3,
        /// <summary>
        /// Plugins directory
        /// </summary>
        AIMP_CFG_PLUGINS = 4,
        /// <summary>
        /// Path to icons
        /// </summary>
        AIMP_CFG_ICONS = 5,
        /// <summary>
        /// Path to audiolibrary database
        /// </summary>
        AIMP_CFG_ML = 6
    }

    /// <summary>
    /// Sort type for playlist
    /// </summary>
    public enum AIMPPlaylistSortType : uint
    {
        /// <summary>
        /// By track title
        /// </summary>
        ByTitle = 1,
        /// <summary>
        /// By file names
        /// </summary>
        ByFileName = 2,
        /// <summary>
        /// By track duration
        /// </summary>
        ByDuration = 3,
        /// <summary>
        /// By artist
        /// </summary>
        ByArtist = 4,
        /// <summary>
        /// Invert order of files
        /// </summary>
        Inverse = 5,
        /// <summary>
        /// Shuffle tracks
        /// </summary>
        Randomize = 6
    }

    /// <summary>
    /// Type of supported file extensions
    /// </summary>
    public enum AIMPExtensionType : uint
    {
        /// <summary>
        /// Playlist files
        /// </summary>
        PlaylistExts = 1,
        /// <summary>
        /// Audio files
        /// </summary>
        AudioExts = 2
    }

    /// <summary>
    /// Player window
    /// </summary>
    public enum AIMPPlayerWindow: uint
    {
        MainWindow   = 42,
        AIMP_STS_TC_HWND     = 43,
        AIMP_STS_APP_HWND    = 44,
        PlaylistWindow     = 45,
        EqualizerWindow     = 46
    }

    /// <summary>
    /// Type of AIMP Menu Item
    /// </summary>
    public enum AIMPMenuItemType
    {
        /// <summary>
        /// Standart
        /// </summary>
        Normal,
        /// <summary>
        /// Checkbox
        /// </summary>
        CheckBox,
        /// <summary>
        /// Radiobutton
        /// </summary>
        RadioButton
    }

    /// <summary>
    /// Category of root menu item
    /// </summary>
    public enum AIMPPlayerMenu : uint
    {
        AIMP_MAIN_MENU_OPN   = 0,
        //AIMP_MAIN_MENU_UTILS = 1,
        AIMP_MAIN_MENU_FNC   = 2,
        AIMP_MAIN_MENU_CFG   = 3,
        AIMP_UTILS_MENU      = 4,
        AIMP_PLS_MENU_ADD    = 5,
        AIMP_PLS_MENU_JUMP   = 6,
        AIMP_PLS_MENU_FNC    = 7,
        AIMP_PLS_MENU_SEND   = 8,
        AIMP_PLS_MENU_DEL    = 9,
        AIMP_ADD_MENU        = 10,
        AIMP_DEL_MENU        = 11,
        AIMP_FND_MENU        = 12,
        AIMP_SRT_MENU        = 13,
        AIMP_MSC_MENU        = 14,
        AIMP_PLS_MENU        = 15,
        //AIMP_TRAY_UTILS      = 16,
        AIMP_TRAY            = 17,
        AIMP_EQ_LIB          = 18
    }

    /// <summary>
    /// Option frame category
    /// </summary>
    public enum AIMPOptionFramePosition: uint
    {
        AIMP_FRAME_POS_PLAY     = 1,
        AIMP_FRAME_POS_PLAYLIST = 2,
        AIMP_FRAME_POS_PLAYER   = 3,
        AIMP_FRAME_POS_TEMPLATE = 4,
        AIMP_FRAME_POS_SYSTEM   = 5,
        AIMP_FRAME_POS_SKINS    = 6,
        AIMP_FRAME_POS_LANGS    = 7
    }


    /// <summary>
    /// Function for calling
    /// </summary>
    public enum AIMPCallFunction: uint
    {
        AIMP_OPEN_FILES      = 0,
        AIMP_OPEN_DIR        = 1,
        AIMP_ABOUT           = 2,
        AIMP_SLEEP_TIMER     = 3,
        AIMP_UTILS_AC        = 4,
        AIMP_UTILS_SR        = 5,
        AIMP_UTILS_TE        = 6,
        AIMP_UTILS_CDB       = 7,
        AIMP_OPTIONS         = 8,
        AIMP_PLUGINS         = 9,
        AIMP_QUIT            = 10,
        AIMP_NEXT_VIS        = 11,
        AIMP_PREV_VIS        = 12,
        IMP_EQ_ANALOG        = 13,
        AIMP_TO_TRAY         = 14,
        AIMP_PLAY            = 15,
        AIMP_PAUSE           = 16,
        AIMP_STOP            = 17,
        AIMP_NEXT            = 18,
        AIMP_PREV            = 19,
        AIMP_ADD_FILES       = 20,
        AIMP_ADD_DIR         = 21,
        AIMP_ADD_PLS         = 22,
        AIMP_ADD_URL         = 23,
        AIMP_DEL_FILES       = 24,
        AIMP_DEL_BAD         = 25,
        AIMP_DEL_FROMHDD     = 26,
        AIMP_DEL_OFF         = 27,
        AIMP_DEL_OFF_HDD     = 28,
        AIMP_RESCAN_PLS      = 29,
        AIMP_SHOW_CURFILE    = 30,
        AIMP_SORT_INVERT     = 31,
        AIMP_SORT_RANDOM     = 32,
        AIMP_SORT_TITLE      = 33,
        AIMP_SORT_ARTIST     = 34,
        AIMP_SORT_FOLDER     = 35,
        AIMP_SORT_LENGTH     = 36,
        AIMP_SORT_RATING     = 37,
        AIMP_SEARCH          = 38,
        AIMP_OPEN_PLS        = 39,
        AIMP_SAVE_PLS        = 40,
        AIMP_PLAY_LAST       = 41,
        AIMP_OFF_SELECTED    = 42,
        AIMP_ON_SELECTED     = 43,
        AIMP_ADD2BOOKMARK    = 44,
        AIMP_EDITBOOKMARK    = 45
    }
}
