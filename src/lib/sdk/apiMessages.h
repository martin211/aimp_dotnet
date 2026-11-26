////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   Messages API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiMessagesH
#define apiMessagesH

#include "apiTypes.h"
#include "apiFileManager.h"
#include "apiPlayer.h"

// -----------------------------------------------------------------------------
// Commands
// -----------------------------------------------------------------------------

const int AIMP_MSG_CMD_BASE = 0;

// AParam1: Command ID (see AIMP_MSG_CMD_XXX)
// Result: S_OK, if enabled
const int AIMP_MSG_CMD_STATE_GET = AIMP_MSG_CMD_BASE + 1;

// Show "Quick File Info" card for now playing file
// Param1:
//    LoWord: DisplayTime (in milliseconds), 0 - default
//    HiWord: 0 - Popup near system tray,
//            1 - Popup near mouse cursor
// Param2: unused
const int AIMP_MSG_CMD_QFI_PLAYING_TRACK = AIMP_MSG_CMD_BASE + 2;

// Show custom text in display of RunningLine or Text elements
// Param1: 0 - Hide text automaticly after 2 seconds
//         1 - Text will be hidden manually (put nil to Param2 to hide previous text)
// Param2: Pointer to TChar-array (nullable)
const int AIMP_MSG_CMD_SHOW_NOTIFICATION = AIMP_MSG_CMD_BASE + 3;

const int AIMP_MSG_CMD_TOGGLE_PARTREPEAT = AIMP_MSG_CMD_BASE + 5;

// Show the "About" Dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_ABOUT = AIMP_MSG_CMD_BASE + 6;

// Show the "Options" Dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_OPTIONS = AIMP_MSG_CMD_BASE + 7;

// Show the "Options" Dialog with active "plugins" sheet
// Param1: page index (starts from 1), 0 is for previous user choice (default)
// Param2: unused
const int AIMP_MSG_CMD_PLUGINS = AIMP_MSG_CMD_BASE + 8;

// Close the App
// Param1, Param2: unused
const int AIMP_MSG_CMD_QUIT = AIMP_MSG_CMD_BASE + 9;

// Show Simple Scheduler Options Dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_SCHEDULER = AIMP_MSG_CMD_BASE + 11;

// Switch to next visualization
// Param1, Param2: unused
const int AIMP_MSG_CMD_VISUAL_NEXT = AIMP_MSG_CMD_BASE + 12;

// Switch to previous visualization
// Param1, Param2: unused
const int AIMP_MSG_CMD_VISUAL_PREV = AIMP_MSG_CMD_BASE + 13;

// Start / Resume playback
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLAY = AIMP_MSG_CMD_BASE + 14;

// Pause / Start playback
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLAYPAUSE = AIMP_MSG_CMD_BASE + 15;

// Start playback of previous playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLAY_PREV_PLAYLIST = AIMP_MSG_CMD_BASE + 16;

// Resume / Pause playback
// Param1, Param2: unused
const int AIMP_MSG_CMD_PAUSE = AIMP_MSG_CMD_BASE + 17;

// Stop playback
// Param1, Param2: unused
const int AIMP_MSG_CMD_STOP = AIMP_MSG_CMD_BASE + 18;

// Next Track
// Param1, Param2: unused
const int AIMP_MSG_CMD_NEXT = AIMP_MSG_CMD_BASE + 19;

// Previous Track
// Param1, Param2: unused
const int AIMP_MSG_CMD_PREV = AIMP_MSG_CMD_BASE + 20;

// Execute "Open Files" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_OPEN_FILES = AIMP_MSG_CMD_BASE + 21;

// Execute "Open Folders" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_OPEN_FOLDERS = AIMP_MSG_CMD_BASE + 22;

// Execute "Open Playlist" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_OPEN_PLAYLISTS  = AIMP_MSG_CMD_BASE + 23;

// Execute "Save Playlist" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_SAVE_PLAYLISTS  = AIMP_MSG_CMD_BASE + 24;

// Execute "Bookmarks" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_BOOKMARKS = AIMP_MSG_CMD_BASE + 25;

// Add file to Bookmarks
// Param1: 0 - add playing file, 1 - add selected files from active playlist
// Param2: unused
const int AIMP_MSG_CMD_BOOKMARKS_ADD = AIMP_MSG_CMD_BASE + 26;

// Rescan tags in active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_RESCAN  = AIMP_MSG_CMD_BASE + 27;

// Jump focus in playlist to playing file
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_FOCUS_PLAYING = AIMP_MSG_CMD_BASE + 28;

// Delete all items from active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_ALL = AIMP_MSG_CMD_BASE + 29;

// Delete non exists items from active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_NON_EXISTS = AIMP_MSG_CMD_BASE + 30;

// Delete non selected items from active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_NON_SELECTED = AIMP_MSG_CMD_BASE + 31;

// Delete Playing Item from playlist and disk
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_PLAYING_FROM_HDD = AIMP_MSG_CMD_BASE + 32;

// Delete selected items from active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_SELECTED = AIMP_MSG_CMD_BASE + 33;

// Delete selected items from active playlist and disk
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_SELECTED_FROM_HDD = AIMP_MSG_CMD_BASE + 34;

// Delete switched off items from active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_SWITCHEDOFF = AIMP_MSG_CMD_BASE + 35;

// Delete switched off items from active playlist and disk
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_SWITCHEDOFF_FROM_HDD = AIMP_MSG_CMD_BASE + 36;

// Delete duplicates from active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_DUPLICATES = AIMP_MSG_CMD_BASE + 37;

// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SORT_BY_ARTIST = AIMP_MSG_CMD_BASE + 38;

// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SORT_BY_TITLE = AIMP_MSG_CMD_BASE + 39;

// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SORT_BY_PATH = AIMP_MSG_CMD_BASE + 40;

// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SORT_BY_DURATION = AIMP_MSG_CMD_BASE + 41;

// Param1:
//   0 - all
//   1 - groups
//   2 - items inside groups
//   3 - groups and it items
// Param2: unused
const int AIMP_MSG_CMD_PLS_SORT_RANDOMIZE = AIMP_MSG_CMD_BASE + 42;

// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SORT_INVERT = AIMP_MSG_CMD_BASE + 43;

// Switch on autoplaying markers for selected items in active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SWITCH_ON = AIMP_MSG_CMD_BASE + 44;

// Switch on autoplaying markers for selected items in active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_SWITCH_OFF = AIMP_MSG_CMD_BASE + 45;

// Execute "Add files" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_ADD_FILES = AIMP_MSG_CMD_BASE + 46;

// Execute "Add folders" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_ADD_FOLDERS = AIMP_MSG_CMD_BASE + 47;

// Execute "Add Playlists" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_ADD_PLAYLISTS = AIMP_MSG_CMD_BASE + 48;

// Execute "Add URL" dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_ADD_URL = AIMP_MSG_CMD_BASE + 49;

// Execute "Quick Tag Editor" for playing file
// Param1, Param2: unused
const int AIMP_MSG_CMD_QTE_PLAYING_TRACK = AIMP_MSG_CMD_BASE + 51;

// Show Advanced Search Dialog
// Param1, Param2: unused
const int AIMP_MSG_CMD_SEARCH = AIMP_MSG_CMD_BASE + 52;

// Show DSP Manager Dialog
// Param1: Active tab sheet index [0..3]
// Param2: unused
const int AIMP_MSG_CMD_DSPMANAGER = AIMP_MSG_CMD_BASE + 53;

// Sync active playlist with preimage
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_RELOAD_FROM_PREIMAGE = AIMP_MSG_CMD_BASE + 55;

// Starts first visualization
// Param1, Param2: unused
const int AIMP_MSG_CMD_VISUAL_START = AIMP_MSG_CMD_BASE + 57;

// Switch off the visualization
// Param1, Param2: unused
const int AIMP_MSG_CMD_VISUAL_STOP = AIMP_MSG_CMD_BASE + 58;

// Rescan tags for selected files in active playlist
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_RESCAN_SELECTED  = AIMP_MSG_CMD_BASE + 59;

// Extended control of "Quick File Info" card that displaying information about playing file
// Param2: pointer to TAIMPQuickFileInfoParams
const int AIMP_MSG_CMD_QFI = AIMP_MSG_CMD_BASE + 60;

// Delete selected items with folders from active playlist and disk
// Param1, Param2: unused
const int AIMP_MSG_CMD_PLS_DELETE_SELECTED_FROM_HDD_W_FOLDERS = AIMP_MSG_CMD_BASE + 61;

// Brings the main window to top.
// Restores the window from tray or taskbar if it was minimized
const int AIMP_MSG_CMD_BRING_TO_TOP = AIMP_MSG_CMD_BASE + 62; // v6.0

// -----------------------------------------------------------------------------
// Properties
// -----------------------------------------------------------------------------

const int AIMP_MSG_PROPERTY_BASE = 0x1000;

// Flags for Param1
const int AIMP_MSG_PROPVALUE_GET = 0;
const int AIMP_MSG_PROPVALUE_SET = 1;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to 32-bit floating-point variable, Range [0.0 .. 1.0]
const int AIMP_MSG_PROPERTY_VOLUME = AIMP_MSG_PROPERTY_BASE + 1;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit Boolean) variable
const int AIMP_MSG_PROPERTY_MUTE = AIMP_MSG_PROPERTY_BASE + 2;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [-1.0 .. +1.0], Default: 0.0
const int AIMP_MSG_PROPERTY_BALANCE = AIMP_MSG_PROPERTY_BASE + 3;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.0 .. 1.0], Default: 0.0 (switched off)
const int AIMP_MSG_PROPERTY_CHORUS = AIMP_MSG_PROPERTY_BASE + 4;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.0 .. 1.0], Default: 0.0 (switched off)
const int AIMP_MSG_PROPERTY_ECHO = AIMP_MSG_PROPERTY_BASE + 5;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [1.0 .. 4.0], Default: 1.0 (switched off)
const int AIMP_MSG_PROPERTY_ENHANCER = AIMP_MSG_PROPERTY_BASE + 6;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.0 .. 1.0], Default: 0.0 (switched off)
const int AIMP_MSG_PROPERTY_FLANGER = AIMP_MSG_PROPERTY_BASE + 7;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.0 .. 1.0], Default: 0.0 (switched off)
const int AIMP_MSG_PROPERTY_REVERB = AIMP_MSG_PROPERTY_BASE + 8;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [-10.0 .. +10.0], Default: 0.0 (switched off)
const int AIMP_MSG_PROPERTY_PITCH = AIMP_MSG_PROPERTY_BASE + 9;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.5 .. 1.5], Default: 1.0 (switched off)
const int AIMP_MSG_PROPERTY_SPEED = AIMP_MSG_PROPERTY_BASE + 10;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.8 .. 1.5], Default: 1.0 (switched off)
const int AIMP_MSG_PROPERTY_TEMPO = AIMP_MSG_PROPERTY_BASE + 11;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.0 .. 2.0], Default: 0.0 (switched off)
const int AIMP_MSG_PROPERTY_TRUEBASS = AIMP_MSG_PROPERTY_BASE + 12;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          [0.5 .. 1.5], Default: 1.0 (switched off)
const int AIMP_MSG_PROPERTY_PREAMP = AIMP_MSG_PROPERTY_BASE + 13;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
//          Default: False (switched off)
const int AIMP_MSG_PROPERTY_EQUALIZER = AIMP_MSG_PROPERTY_BASE + 14;

// Param1: LoWord: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
//          HiWord: Slider Index [0..18]
// Param2: Pointer to Single (32-bit floating point value) variable
//          [-15.0 .. 15.0] (in db), Default: 0.0 (switched off)
// !!!NOTE: Param2 in AIMP_MSG_EVENT_PROPERTY_VALUE will be nil;
const int AIMP_MSG_PROPERTY_EQUALIZER_BAND = AIMP_MSG_PROPERTY_BASE + 15;

// !!!ReadOnly property
// Param1: AIMP_MSG_PROPVALUE_GET
// Param2: Pointer to Integer variable
//			One of the AIMP_PLAYER_STATE_XXX
// See AIMP_MSG_EVENT_PLAYER_STATE event
const int AIMP_MSG_PROPERTY_PLAYER_STATE = AIMP_MSG_PROPERTY_BASE + 16;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Single (32-bit floating point value) variable
//          New position in Seconds
// See AIMP_MSG_EVENT_PROPERTY_VALUE and AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION
const int AIMP_MSG_PROPERTY_PLAYER_POSITION = AIMP_MSG_PROPERTY_BASE + 17;

// !!!ReadOnly property
// Param1: AIMP_MSG_PROPVALUE_GET
// Param2: Pointer to Single (32-bit floating point value) variable, in Seconds
const int AIMP_MSG_PROPERTY_PLAYER_DURATION = AIMP_MSG_PROPERTY_BASE + 18;

// !!!ReadOnly property
// Param1: AIMP_MSG_PROPVALUE_GET
// Param2: Pointer to Integer variable
//    0 = Disabled,
//    1 = Point A assigned,
//    2 = Point B assigned, repeat started
const int AIMP_MSG_PROPERTY_PARTREPEAT = AIMP_MSG_PROPERTY_BASE + 19;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_REPEAT = AIMP_MSG_PROPERTY_BASE + 20;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_SHUFFLE = AIMP_MSG_PROPERTY_BASE + 21;

// !!!ReadOnly property
// Param1: One of AIMP_MPH_XXX flags
// Param2: Pointer to HWND
const int AIMP_MSG_PROPERTY_HWND = AIMP_MSG_PROPERTY_BASE + 22;
	const int AIMP_MPH_MAINFORM      = 0;
    const int AIMP_MPH_APPLICATION   = 1;
    const int AIMP_MPH_TRAYCONTROL   = 2;
    const int AIMP_MPH_PLAYLISTFORM  = 3;
    const int AIMP_MPH_EQUALIZERFORM = 4;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_STAYONTOP = AIMP_MSG_PROPERTY_BASE + 23;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_REVERSETIME = AIMP_MSG_PROPERTY_BASE + 24;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_MINIMIZED_TO_TRAY = AIMP_MSG_PROPERTY_BASE + 25;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_REPEAT_SINGLE_FILE_PLAYLISTS = AIMP_MSG_PROPERTY_BASE + 26;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Integer variable
//   0 - Jump to next playlist
//   1 - Repeat playlist
//   2 - Do nothing
const int AIMP_MSG_PROPERTY_ACTION_ON_END_OF_PLAYLIST = AIMP_MSG_PROPERTY_BASE + 27;

// WARNING: DEPRECATED, USE THE AIMP_MSG_PROPERTY_ACTION_ON_END_OF_TRACK INSTEAD
const int AIMP_MSG_PROPERTY_STOP_AFTER_TRACK = AIMP_MSG_PROPERTY_BASE + 28;

// Start / Stop Internet Radio capture
// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_RADIOCAP = AIMP_MSG_PROPERTY_BASE + 29;

// See AIMP_MSG_EVENT_LOADED
// Param1: AIMP_MSG_PROPVALUE_GET (ReadOnly)
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_LOADED = AIMP_MSG_PROPERTY_BASE + 30;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_VISUAL_FULLSCREEN = AIMP_MSG_PROPERTY_BASE + 31;

// !!!ReadOnly property
// Param1: AIMP_MSG_PROPVALUE_GET
// Param2: Pointer to Single (32-bit floating point value) variable, [0..100]%
const int AIMP_MSG_PROPERTY_PLAYER_BUFFERING = AIMP_MSG_PROPERTY_BASE + 32;

// Toggles the Internet Radio capture mode - single track only / all tracks
// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_RADIOCAP_SINGLE_TRACK = AIMP_MSG_PROPERTY_BASE + 33;

// State of cross-mixing feature
// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_CROSSMIXING = AIMP_MSG_PROPERTY_BASE + 34;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Integer variable
//   0 - Default Action
//   1 - Jump to next track and stop playback
//   2 - Jump to next track and pause playback
const int AIMP_MSG_PROPERTY_ACTION_ON_END_OF_TRACK = AIMP_MSG_PROPERTY_BASE + 35;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
//          Default: False (switched off)
const int AIMP_MSG_PROPERTY_EQUALIZER_AUTO = AIMP_MSG_PROPERTY_BASE + 36;

// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to first element of array of two Single (32-bit floating point value) values
// 1st element is position of the A point (in seconds) of part-repeat range or -1 if point is not specified
// 2nd element is position of the B point (in seconds) of part-repeat range or -1 if point is not specified
const int AIMP_MSG_PROPERTY_PARTREPEAT_RANGE = AIMP_MSG_PROPERTY_BASE + 37;

// State of the "automatically jump to next track" option
// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_JUMP_TO_NEXT_TRACK = AIMP_MSG_PROPERTY_BASE + 38;

// State of "the "previous track" action jumps to track beginning" option
// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to LongBool (32-bit boolean value) variable
const int AIMP_MSG_PROPERTY_JUMP_TO_BEGINNING_ON_PREV_TRACK = AIMP_MSG_PROPERTY_BASE + 39;

// Playback Repeat Mode
// Param1: AIMP_MSG_PROPVALUE_GET / AIMP_MSG_PROPVALUE_SET
// Param2: Pointer to Integer variable
//   0 - none
//   1 - repeat single track
//   2 - repeat playlist
const int AIMP_MSG_PROPERTY_REPEAT_MODE = AIMP_MSG_PROPERTY_BASE + 40; // v6.0

// -----------------------------------------------------------------------------
// Events
// -----------------------------------------------------------------------------

const int AIMP_MSG_EVENT_BASE = 0x2000;

// Called, when Command state changed; Param1: Command ID (see AIMP_MSG_CMD_XXX)
const int AIMP_MSG_EVENT_CMD_STATE = AIMP_MSG_EVENT_BASE + 1;

// Called, when Options has been changed
const int AIMP_MSG_EVENT_OPTIONS = AIMP_MSG_EVENT_BASE + 2;

// Called, when audio stream starts playing
const int AIMP_MSG_EVENT_STREAM_START = AIMP_MSG_EVENT_BASE + 3;
// Similar to AIMP_MSG_EVENT_STREAM_START event, but called when an Internet radio station changes the track
const int AIMP_MSG_EVENT_STREAM_START_SUBTRACK = AIMP_MSG_EVENT_BASE + 4;
// Called, when audio stream has been finished
const int AIMP_MSG_EVENT_STREAM_END = AIMP_MSG_EVENT_BASE + 5;
  // Param1 contains combination of next flags:
    const int AIMP_MES_END_OF_QUEUE    = 1;
    const int AIMP_MES_END_OF_PLAYLIST = 2;
	const int AIMP_MES_HAS_NEXT_TRACK  = 4;

// Called, when player state has been changed (Played / Paused / Stopped)
// Param1: One of the AIMP_PLAYER_STATE_XXX
const int AIMP_MSG_EVENT_PLAYER_STATE = AIMP_MSG_EVENT_BASE + 6;

// Called, when property value has been changed
// Param1: PropertyID (see AIMP_MSG_PROPERTY_XXX)
// Param2: like Param2 for each PropertyID
const int AIMP_MSG_EVENT_PROPERTY_VALUE = AIMP_MSG_EVENT_BASE + 7;

// Called, when options frame added / removed
// Param1, Param2: unused
const int AIMP_MSG_EVENT_OPTIONS_FRAME_LIST = AIMP_MSG_EVENT_BASE + 8;

// Called, when options frame content changed
// Param1, Param2: unused
const int AIMP_MSG_EVENT_OPTIONS_FRAME_MODIFIED = AIMP_MSG_EVENT_BASE + 9;

// Called, when swithing between visual plugins
// Param1, Param2: unused
const int AIMP_MSG_EVENT_VISUAL_PLUGIN = AIMP_MSG_EVENT_BASE + 11;

// Called, when mark of file has been changed
// Param1: New Mark Value (0..5)
// Param2: FileName (Pointer to TChar)
// !!!WARNING: You must not fire this event manually!
const int AIMP_MSG_EVENT_FILEMARK = AIMP_MSG_EVENT_BASE + 12;

// Called, when statistics of the file changed
// Param2: FileName (Pointer to TChar),
// !!!Note: If filename is empty or Param2 is null - statistics for all files has been changed
// !!!WARNING: You must not fire this event manually!
const int AIMP_MSG_EVENT_STATISTICS_CHANGED = AIMP_MSG_EVENT_BASE + 14;

// Called, when app skin (our hue) has been changed
// Param1, Param2: unused
const int AIMP_MSG_EVENT_SKIN = AIMP_MSG_EVENT_BASE + 15;

// Called every second by timer
//    (Unlike AIMP_MSG_EVENT_PROPERTY_VALUE event for AIMP_MSG_PROPERTY_PLAYER_POSITION property,
//     Which fires only if user change position of the track)
// Param1, Param2: unused
const int AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION = AIMP_MSG_EVENT_BASE + 16;

// Called, when inteface language has been changed
// Param1, Param2: unused
const int AIMP_MSG_EVENT_LANGUAGE = AIMP_MSG_EVENT_BASE + 17;

// Called, when AIMP completely loaded
// Param1, Param2: unused
const int AIMP_MSG_EVENT_LOADED = AIMP_MSG_EVENT_BASE + 18;

// Called, when AIMP is preparing to terminate
// Param1, Param2: unused
const int AIMP_MSG_EVENT_TERMINATING = AIMP_MSG_EVENT_BASE + 19;

// Called, when information about playing file changed (album, title, album art and etc)
// Param1, Param2: unused
const int AIMP_MSG_EVENT_PLAYING_FILE_INFO = AIMP_MSG_EVENT_BASE + 20;

// High resolution version of the AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION event
// Called few times per second by a timer (~10 fps, real FPS depends from external factors)
// Param1, Param2: unused
const int AIMP_MSG_EVENT_PLAYER_UPDATE_POSITION_HR = AIMP_MSG_EVENT_BASE + 21;

// Called, when name of equalizer preset has been changed
// Param1: Unused
// Param2: Pointer to TChar-array, can be = nil (ReadOnly!)
const int AIMP_MSG_EVENT_EQUALIZER_PRESET_NAME = AIMP_MSG_EVENT_BASE + 22;

// Callen, when playback queue changed
// Param1: Unused
// Param2: Unused
const int AIMP_MSG_EVENT_PLAYBACK_QUEUE = AIMP_MSG_EVENT_BASE + 23;

// Callen, when list of DSP/VST plugins is changed
// Param1: Unused
// Param2: Unused
const int AIMP_MSG_EVENT_DSP = AIMP_MSG_EVENT_BASE + 24;

// Called, after chaning the accent color or night/day mode
const int AIMP_MSG_EVENT_UI_MODE = AIMP_MSG_EVENT_BASE + 25;

// Called, when skin hue/accent is changed (skin may not be reloaded)
// Param1, Param2: unused
const int AIMP_MSG_EVENT_SKIN_ACCENT = AIMP_MSG_EVENT_BASE + 26; // v6.0

// ---------------------------------------------------------------------------------------------------------------------
// Quick File Info
// ---------------------------------------------------------------------------------------------------------------------

const int AIMP_QFI_ANIMATION_NONE = 0;
const int AIMP_QFI_ANIMATION_FADE = 1;
const int AIMP_QFI_SW_HIDE = 0;
const int AIMP_QFI_SW_SHOW = 1;

#pragma pack(push, 1)
struct TAIMPQuickFileInfoParams
{
	INT32 cbSize; // struct size
	INT32 CmdShow; // refer to AIMP_QFI_SW_XXX
	INT32 AnimationType; // show / hide animation type, refer to AIMP_QFI_ANIMATION_XXX
	INT32 AnimationTime; // animation time in milliseconds
	INT32 DisplayTime; // in milliseconds, 0 - use default display time
	BYTE Opacity; // 0..100%
	IAIMPFileInfo* FileInfo; // file information to display
};
#pragma pack(pop)
typedef TAIMPQuickFileInfoParams* PAIMPQuickFileInfoParams;

// ---------------------------------------------------------------------------------------------------------------------
// General
// ---------------------------------------------------------------------------------------------------------------------

static const GUID IID_IAIMPMessageHook = {0xFC6FB524, 0xA959, 0x4089, 0xAA, 0x0A, 0xEA, 0x40, 0xAB, 0x73, 0x74, 0xCD};
static const GUID IID_IAIMPServiceMessageDispatcher = {0x41494D50, 0x5372, 0x764D, 0x73, 0x67, 0x44, 0x73, 0x70, 0x72, 0x00, 0x00};

/* IAIMPMessageHook */
  
class IAIMPMessageHook: public IUnknown
{
	public:
		virtual void WINAPI CoreMessage(DWORD AMessage, INT32 Param1, void *Param2, HRESULT *AResult) = 0;
};

/* IAIMPServiceMessageDispatcher */

class IAIMPServiceMessageDispatcher: public IUnknown
{
	public:
		virtual HRESULT WINAPI Send(DWORD AMessage, INT32 Param1, void *Param2) = 0;
		// Custom Messages
		virtual DWORD WINAPI Register(PChar AMessageName) = 0;
		// Hook
		virtual HRESULT WINAPI Hook(IAIMPMessageHook *AHook) = 0;
		virtual HRESULT WINAPI Unhook(IAIMPMessageHook *AHook) = 0;
};

#endif // !apiMessagesH
