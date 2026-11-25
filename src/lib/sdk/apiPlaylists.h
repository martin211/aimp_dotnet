////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   Playlists API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiPlaylistsH
#define apiPlaylistsH

#include "apiTypes.h"
#include "apiObjects.h"
#include "apiThreading.h"

static const GUID IID_IAIMPPlaylist = {0x41494D50, 0x506C, 0x7300, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistGroup = {0x41494D50, 0x506C, 0x7347, 0x72, 0x6F, 0x75, 0x70, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistItem = {0x41494D50, 0x506C, 0x7349, 0x74, 0x65, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistListener = {0x41494D50, 0x506C, 0x734C, 0x73, 0x74, 0x6E, 0x72, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistListener2 = {0x41494D50, 0x506C, 0x734C, 0x73, 0x74, 0x6E, 0x72, 0x32, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistQueue = {0x41494D50, 0x506C, 0x7351, 0x75, 0x65, 0x75, 0x65, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistQueue2 = {0x41494D50, 0x506C, 0x7351, 0x75, 0x65, 0x75, 0x65, 0x32, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistQueueListener = {0x41494D50, 0x506C, 0x7351, 0x75, 0x65, 0x75, 0x65, 0x4C, 0x73, 0x74, 0x00};
static const GUID IID_IAIMPExtensionPlaylistManagerListener = {0x41494D50, 0x4578, 0x7450, 0x6C, 0x73, 0x4D, 0x61, 0x6E, 0x4C, 0x74, 0x72};
static const GUID IID_IAIMPServicePlaylistManager = {0x41494D50, 0x5372, 0x7650, 0x6C, 0x73, 0x4D, 0x61, 0x6E, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPServicePlaylistManager2 = {0x41494D50, 0x536D, 0x504C, 0x4D, 0x6E, 0x67, 0x72, 0x32, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistProperties = {0x41494D50, 0x506C, 0x7350, 0x72, 0x6F, 0x70, 0x73, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistPreimageFolders = {0x41494D50, 0x536D, 0x504C, 0x53, 0x72, 0x63, 0x46, 0x6C, 0x64, 0x72, 0x73};
static const GUID IID_IAIMPPlaylistPreimageDataProvider = {0x41494D50, 0x536D, 0x506C, 0x73, 0x44, 0x61, 0x74, 0x61, 0x50, 0x72, 0x76};
static const GUID IID_IAIMPPlaylistPreimageListener = {0x41494D50, 0x536D, 0x504C, 0x4D, 0x6E, 0x67, 0x72, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPlaylistPreimage = {0x41494D50, 0x536D, 0x504C, 0x53, 0x72, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPExtensionPlaylistPreimageFactory = {0x41494D50, 0x4578, 0x7453, 0x6D, 0x50, 0x6C, 0x73, 0x46, 0x63, 0x74, 0x00};
static const GUID IID_IAIMPExtensionPlaylistShuffler = {0x41494D50, 0x4578, 0x7450, 0x6C, 0x73, 0x53, 0x68, 0x75, 0x66, 0x6C, 0x72};

// Property IDs for IAIMPPlaylistItem
const int AIMP_PLAYLISTITEM_PROPID_CUSTOM             = 0;
const int AIMP_PLAYLISTITEM_PROPID_DISPLAYTEXT        = 1;
const int AIMP_PLAYLISTITEM_PROPID_FILEINFO           = 2;
const int AIMP_PLAYLISTITEM_PROPID_FILENAME           = 3;
const int AIMP_PLAYLISTITEM_PROPID_GROUP              = 4;
const int AIMP_PLAYLISTITEM_PROPID_INDEX              = 5;
const int AIMP_PLAYLISTITEM_PROPID_MARK               = 6;
const int AIMP_PLAYLISTITEM_PROPID_PLAYINGSWITCH      = 7;
const int AIMP_PLAYLISTITEM_PROPID_PLAYLIST           = 8;
const int AIMP_PLAYLISTITEM_PROPID_SELECTED           = 9;
const int AIMP_PLAYLISTITEM_PROPID_PLAYBACKQUEUEINDEX = 10;
const int AIMP_PLAYLISTITEM_PROPID_DEADSTATE          = 11; // v6.0

// Property IDs for IAIMPPlaylistGroup
const int AIMP_PLAYLISTGROUP_PROPID_NAME      = 1;
const int AIMP_PLAYLISTGROUP_PROPID_EXPANDED  = 2;
const int AIMP_PLAYLISTGROUP_PROPID_DURATION  = 3;
const int AIMP_PLAYLISTGROUP_PROPID_INDEX     = 4;
const int AIMP_PLAYLISTGROUP_PROPID_SELECTED  = 5;

// Property IDs for IAIMPPropertyList from IAIMPPlaylistQueue
const int AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED = 1;

// Property IDs for IAIMPPropertyList from IAIMPPlaylist
const int AIMP_PLAYLIST_PROPID_NAME                     = 1;
const int AIMP_PLAYLIST_PROPID_READONLY                 = 2;
const int AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT           = 3;
const int AIMP_PLAYLIST_PROPID_ID                       = 4;
const int AIMP_PLAYLIST_PROPID_GROUPNAME				= 5;
const int AIMP_PLAYLIST_PROPID_GROUPPING                = 10;
const int AIMP_PLAYLIST_PROPID_GROUPPING_OVERRIDEN      = 11;
const int AIMP_PLAYLIST_PROPID_GROUPPING_TEMPLATE       = 12;
const int AIMP_PLAYLIST_PROPID_GROUPPING_AUTOMERGING    = 13;
const int AIMP_PLAYLIST_PROPID_FORMATING_OVERRIDEN      = 20;
const int AIMP_PLAYLIST_PROPID_FORMATING_LINE1_TEMPLATE = 21;
const int AIMP_PLAYLIST_PROPID_FORMATING_LINE2_TEMPLATE = 22;
const int AIMP_PLAYLIST_PROPID_VIEW_OVERRIDEN           = 30;
const int AIMP_PLAYLIST_PROPID_VIEW_DURATION            = 31;
const int AIMP_PLAYLIST_PROPID_VIEW_EXPAND_BUTTONS      = 32;
const int AIMP_PLAYLIST_PROPID_VIEW_MARKS               = 33;
const int AIMP_PLAYLIST_PROPID_VIEW_NUMBERS             = 34;
const int AIMP_PLAYLIST_PROPID_VIEW_NUMBERS_ABSOLUTE    = 35;
const int AIMP_PLAYLIST_PROPID_VIEW_SECOND_LINE         = 36;
const int AIMP_PLAYLIST_PROPID_VIEW_SWITCHES            = 37;
const int AIMP_PLAYLIST_PROPID_VIEW_THUMBNAILS			= 38; // v6.00
const int AIMP_PLAYLIST_PROPID_FOCUSINDEX               = 50;
const int AIMP_PLAYLIST_PROPID_PLAYBACKCURSOR           = 51;
const int AIMP_PLAYLIST_PROPID_PLAYINGINDEX             = 52;
const int AIMP_PLAYLIST_PROPID_SIZE                     = 53;
const int AIMP_PLAYLIST_PROPID_DURATION                 = 54;
const int AIMP_PLAYLIST_PROPID_DURATION_REMAINING       = 55; // v5.40
const int AIMP_PLAYLIST_PROPID_PREIMAGE                 = 60;

// Flags for IAIMPPlaylist.Add & IAIMPPlaylist.AddList
const int AIMP_PLAYLIST_ADD_FLAGS_NOCHECKFORMAT = 1;
const int AIMP_PLAYLIST_ADD_FLAGS_NOEXPAND      = 2;
const int AIMP_PLAYLIST_ADD_FLAGS_NOTHREADING   = 4;
const int AIMP_PLAYLIST_ADD_FLAGS_FILEINFO      = 8;

// Flags for IAIMPPlaylist.Delete3
const int AIMP_PLAYLIST_DELETE_FLAGS_PHYSICALLY     = 1;
const int AIMP_PLAYLIST_DELETE_FLAGS_NOCONFIRMATION = 2;

// Flags for IAIMPPlaylist.Sort
const int AIMP_PLAYLIST_SORTMODE_TITLE                         = 1;
const int AIMP_PLAYLIST_SORTMODE_FILENAME                      = 2;
const int AIMP_PLAYLIST_SORTMODE_DURATION                      = 3;
const int AIMP_PLAYLIST_SORTMODE_ARTIST                        = 4;
const int AIMP_PLAYLIST_SORTMODE_INVERSE                       = 5;
const int AIMP_PLAYLIST_SORTMODE_RANDOMIZE                     = 6;
const int AIMP_PLAYLIST_SORTMODE_RANDOMIZE_GROUPS              = 7; // v5.10
const int AIMP_PLAYLIST_SORTMODE_RANDOMIZE_GROUPITEMS          = 8; // v5.10
const int AIMP_PLAYLIST_SORTMODE_RANDOMIZE_GROUPS_AND_IT_ITEMS = 9; // v5.10

// Flags for IAIMPPlaylist.Close
const int AIMP_PLAYLIST_CLOSE_FLAGS_FORCE_REMOVE = 1;
const int AIMP_PLAYLIST_CLOSE_FLAGS_FORCE_UNLOAD = 2;

// Flags for IAIMPPlaylist.GetFiles
const int AIMP_PLAYLIST_GETFILES_FLAGS_SELECTED_ONLY    = 0x1;
const int AIMP_PLAYLIST_GETFILES_FLAGS_VISIBLE_ONLY     = 0x2;
const int AIMP_PLAYLIST_GETFILES_FLAGS_COLLAPSE_VIRTUAL = 0x4;

// Flags for IAIMPPlaylist.ReloadInfo
const int AIMP_PLAYLIST_RELOADINFO_FLAGS_DEFAULT  = 0;
const int AIMP_PLAYLIST_RELOADINFO_FLAGS_FULL     = 1;
const int AIMP_PLAYLIST_RELOADINFO_FLAGS_SELECTED = 2;

// Flags for IAIMPPlaylistListener.Changed
const int AIMP_PLAYLIST_NOTIFY_NAME             = 0x00000001;
const int AIMP_PLAYLIST_NOTIFY_SELECTION        = 0x00000002;
const int AIMP_PLAYLIST_NOTIFY_PLAYBACKCURSOR   = 0x00000004;
const int AIMP_PLAYLIST_NOTIFY_READONLY         = 0x00000008;
const int AIMP_PLAYLIST_NOTIFY_FOCUSINDEX       = 0x00000010;
const int AIMP_PLAYLIST_NOTIFY_CONTENT          = 0x00000020;
const int AIMP_PLAYLIST_NOTIFY_FILEINFO         = 0x00000040;
const int AIMP_PLAYLIST_NOTIFY_STATISTICS       = 0x00000080;
const int AIMP_PLAYLIST_NOTIFY_PLAYINGSWITCHS   = 0x00000100;
const int AIMP_PLAYLIST_NOTIFY_PREIMAGE         = 0x00000200;
const int AIMP_PLAYLIST_NOTIFY_MODIFIED         = 0x00000400;
const int AIMP_PLAYLIST_NOTIFY_DEADSTATE        = 0x00000800;
const int AIMP_PLAYLIST_NOTIFY_MAKEVISIBLE      = 0x00001000;
const int AIMP_PLAYLIST_NOTIFY_PLAYBACKQUEUE    = 0x00002000;
const int AIMP_PLAYLIST_NOTIFY_PLAYBACKBOOKMARK = 0x00004000; // v5.40
const int AIMP_PLAYLIST_NOTIFY_GROUPNAME        = 0x00008000; // v5.40
const int AIMP_PLAYLIST_NOTIFY_SETTINGS			= 0x00010000; // v6.00

// Properties IDS for IAIMPPlaylistPreimage
const int AIMP_PLAYLISTPREIMAGE_PROPID_FACTORYID = 1;
const int AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC = 2;
const int AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG = 3;
const int AIMP_PLAYLISTPREIMAGE_PROPID_SORTTEMPLATE = 4;
const int AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP = 5;

// Properties Ids for AIMP_PREIMAGEFACTORY_PLAYLIST_ID
const int AIMP_PLAYLISTPREIMAGE_PLAYLISTBASED_PROPID_URI = 100;

// Flags for IAIMPExtensionPlaylistPreimageFactory.GetFlags
const int AIMP_PREIMAGEFACTORY_FLAG_CONTEXTDEPENDENT = 1;

// Built-in Preimage Factories
static const TChar AIMP_PREIMAGEFACTORY_FOLDERS_ID[] 		= TEXT("TAIMPPlaylistFoldersPreimage");
static const TChar AIMP_PREIMAGEFACTORY_MUSICLIBRARY_ID[] 	= TEXT("TAIMPMLPlaylistPreimage");
static const TChar AIMP_PREIMAGEFACTORY_PLAYLIST_ID[] 		= TEXT("TAIMPPlaylistBasedPreimage");

/* IAIMPPlaylistItem */

class IAIMPPlaylistItem: public IAIMPPropertyList
{
	public:
		virtual HRESULT WINAPI ReloadInfo() = 0;
};

/* IAIMPPlaylistGroup */

class IAIMPPlaylistGroup: public IAIMPPropertyList
{
	public:
		virtual HRESULT WINAPI GetItem(INT32 Index, CONSTIID IID, void **Obj) = 0;
		virtual INT32 WINAPI GetItemCount() = 0;
};

/* IAIMPPlaylistListener */

class IAIMPPlaylistListener: public IUnknown
{
	public:
		virtual void WINAPI Activated() = 0;
		virtual void WINAPI Changed(DWORD Flags) = 0;
		virtual void WINAPI Removed() = 0;
};

/* IAIMPPlaylistListener2 */

class IAIMPPlaylistListener2: public IUnknown
{
	public:
		virtual void WINAPI ScanningBegin() = 0;
		virtual void WINAPI ScanningProgress(const DOUBLE Progress) = 0;
		virtual void WINAPI ScanningEnd(BOOL HasChanges, BOOL Canceled) = 0;
};

typedef INT32 (WINAPI TAIMPPlaylistCompareProc)(IAIMPPlaylistItem* Item1, IAIMPPlaylistItem* Item2, void* UserData);
typedef BOOL  (WINAPI TAIMPPlaylistDeleteProc)(IAIMPPlaylistItem* Item, void* UserData);


/* IAIMPPlaylist */

class IAIMPPlaylist: public IUnknown
{
	public:
		// Adding
		virtual HRESULT WINAPI Add(IUnknown* Obj, DWORD Flags, INT32 InsertIn) = 0;
		virtual HRESULT WINAPI AddList(IAIMPObjectList* ObjList, DWORD Flags, INT32 InsertIn) = 0;

		// Deleting
		virtual HRESULT WINAPI Delete(IAIMPPlaylistItem* Item) = 0;
		virtual HRESULT WINAPI Delete2(INT32 ItemIndex) = 0;
		virtual HRESULT WINAPI Delete3(DWORD Flags, TAIMPPlaylistDeleteProc Proc, void* UserData) = 0;
		virtual HRESULT WINAPI DeleteAll() = 0;

		// Sorting
		virtual HRESULT WINAPI Sort(INT32 Mode) = 0;
		virtual HRESULT WINAPI Sort2(IAIMPString* Template) = 0;
		virtual HRESULT WINAPI Sort3(TAIMPPlaylistCompareProc* Proc, void* UserData) = 0;

		// Locking
		virtual HRESULT WINAPI BeginUpdate() = 0;
		virtual HRESULT WINAPI EndUpdate() = 0;

		// Other Commands
		virtual HRESULT WINAPI Close(DWORD Flags) = 0;
		virtual HRESULT WINAPI GetFiles(DWORD Flags, IAIMPObjectList **List) = 0;
		virtual HRESULT WINAPI MergeGroup(IAIMPPlaylistGroup* Group) = 0;
		virtual HRESULT WINAPI ReloadFromPreimage() = 0;
		virtual HRESULT WINAPI ReloadInfo(DWORD Flags) = 0;

		// Items
		virtual HRESULT WINAPI GetItem(INT32 Index, CONSTIID IID, void **Obj) = 0;
		virtual INT32 WINAPI GetItemCount() = 0;

		// Groups
		virtual HRESULT WINAPI GetGroup(INT32 Index, CONSTIID IID, void **Obj) = 0;
		virtual INT32 WINAPI GetGroupCount() = 0;

		// Listener
		virtual HRESULT WINAPI ListenerAdd(IAIMPPlaylistListener* AListener) = 0;
		virtual HRESULT WINAPI ListenerRemove(IAIMPPlaylistListener* AListener) = 0;
};

/* IAIMPPlaylistQueue */

class IAIMPPlaylistQueue: public IUnknown
{
	public:
		// Adding
		virtual HRESULT WINAPI Add(IAIMPPlaylistItem* Item, BOOL InsertAtBeginning) = 0;
		virtual HRESULT WINAPI AddList(IAIMPObjectList* ItemList, BOOL InsertAtBeginning) = 0;
		// Deleting
		virtual HRESULT WINAPI Delete(IAIMPPlaylistItem* Item) = 0;
		virtual HRESULT WINAPI Delete2(IAIMPPlaylist* Playlist) = 0;
		// Reorder
		virtual HRESULT WINAPI Move(IAIMPPlaylistItem* Item, INT32 TargetIndex) = 0;
		virtual HRESULT WINAPI Move2(INT32 ItemIndex, INT32 TargetIndex) = 0;
		// Items
		virtual HRESULT WINAPI GetItem(INT32 Index, CONSTIID IID, void **Obj) = 0;
		virtual INT32 WINAPI GetItemCount() = 0;
};

/* IAIMPPlaylistQueueListener */

class IAIMPPlaylistQueueListener: public IUnknown
{
	public:
		virtual void WINAPI ContentChanged() = 0;
		virtual void WINAPI StateChanged() = 0;

};

/* IAIMPPlaylistQueue2 */

class IAIMPPlaylistQueue2: public IAIMPPlaylistQueue
{
	public:
		// Listener
		virtual HRESULT WINAPI ListenerAdd(IAIMPPlaylistQueueListener* AListener) = 0;
		virtual HRESULT WINAPI ListenerRemove(IAIMPPlaylistQueueListener* AListener) = 0;
};

/* IAIMPPlaylistProperties */

class IAIMPPlaylistProperties : public IAIMPPropertyList2
{
	public:
		virtual HRESULT WINAPI GetCustomValue(IAIMPString* Name, IAIMPString** Value) = 0;
		virtual HRESULT WINAPI SetCustomValue(IAIMPString* Name, IAIMPString*  Value) = 0;
};

/* IAIMPPlaylistPreimageListener */

class IAIMPPlaylistPreimageListener : public IUnknown
{
	public:
		virtual HRESULT WINAPI DataChanged() = 0;
		virtual HRESULT WINAPI SettingsChanged() = 0;
};

/* IAIMPPlaylistPreimage */

class IAIMPPlaylistPreimage: public IAIMPPropertyList
{
	public:
		virtual void WINAPI Finalize() = 0;
		virtual void WINAPI Initialize(IAIMPPlaylistPreimageListener* Listener) = 0;

		virtual HRESULT WINAPI ConfigLoad(IAIMPStream* Stream) = 0;
		virtual HRESULT WINAPI ConfigSave(IAIMPStream* Stream) = 0;
		virtual HRESULT WINAPI ExecuteDialog(HWND OwnerWndHanle) = 0;
};

/* IAIMPPlaylistPreimageDataProvider */

class IAIMPPlaylistPreimageDataProvider : public IUnknown 
{
	public:
		virtual HRESULT WINAPI GetFiles(IAIMPTaskOwner* Owner, DWORD** Flags, IAIMPObjectList** List) = 0;
};

/* IAIMPPlaylistPreimageFolders */

class IAIMPPlaylistPreimageFolders : public IAIMPPlaylistPreimage
{
	public:
		virtual HRESULT WINAPI ItemsAdd(IAIMPString* Path, BOOL Recursive) = 0;
		virtual HRESULT WINAPI ItemsDelete(INT32 Index) = 0;
		virtual HRESULT WINAPI ItemsDeleteAll() = 0;
		virtual HRESULT WINAPI ItemsGet(INT32 Index, IAIMPString* Path, BOOL* Recursive) = 0;
		virtual INT32 WINAPI ItemsGetCount() = 0;
};

//----------------------------------------------------------------------------------------------------------------------
// Extensions
//----------------------------------------------------------------------------------------------------------------------

/* IAIMPExtensionPlaylistManagerListener */

class IAIMPExtensionPlaylistManagerListener: public IUnknown
{
	public:
		virtual void WINAPI PlaylistActivated(IAIMPPlaylist* Playlist) = 0;
		virtual void WINAPI PlaylistAdded(IAIMPPlaylist* Playlist) = 0;
		virtual void WINAPI PlaylistRemoved(IAIMPPlaylist* Playlist) = 0;
};

/* IAIMPExtensionPlaylistPreimageFactory */

class IAIMPExtensionPlaylistPreimageFactory : public IUnknown 
{
	public:
		virtual HRESULT WINAPI CreatePreimage(IAIMPPlaylistPreimage** preimage) = 0;
		virtual HRESULT WINAPI GetID(IAIMPString** ID) = 0;
		virtual HRESULT WINAPI GetName(IAIMPString** Name) = 0;
		virtual DWORD WINAPI GetFlags() = 0;
};

/* IAIMPExtensionPlaylistShuffler */

class IAIMPExtensionPlaylistShuffler : public IUnknown // v6.00
{
	public:
		virtual HRESULT WINAPI Shuffle(IAIMPPlaylist* Playlist,
			IAIMPObjectList2* List, INT32 InitialPlaybackQueueIndex) = 0;
};

//----------------------------------------------------------------------------------------------------------------------
// Services
//----------------------------------------------------------------------------------------------------------------------

/* IAIMPServicePlaylistManager */

class IAIMPServicePlaylistManager: public IUnknown
{
	public:
		// Creating Playlist
    	virtual HRESULT WINAPI CreatePlaylist(IAIMPString* Name, BOOL Activate, IAIMPPlaylist **Playlist) = 0;
    	virtual HRESULT WINAPI CreatePlaylistFromFile(IAIMPString* FileName, BOOL Activate, IAIMPPlaylist **Playlist) = 0;

		// Active Playlist
    	virtual HRESULT WINAPI GetActivePlaylist(IAIMPPlaylist **Playlist) = 0;
    	virtual HRESULT WINAPI SetActivePlaylist(IAIMPPlaylist* Playlist) = 0;

		// Playable Playlist
    	virtual HRESULT WINAPI GetPlayingPlaylist(IAIMPPlaylist **Playlist) = 0;

		// Loaded Playlists
		virtual HRESULT WINAPI GetLoadedPlaylist(INT32 Index, IAIMPPlaylist** Playlist) = 0;
		virtual HRESULT WINAPI GetLoadedPlaylistByName(IAIMPString* Name, IAIMPPlaylist** Playlist) = 0;
		virtual INT32 WINAPI GetLoadedPlaylistCount() = 0;
		virtual HRESULT WINAPI GetLoadedPlaylistByID(IAIMPString* ID, IAIMPPlaylist** Playlist) = 0;
};

/* IAIMPServicePlaylistManager2 */

class IAIMPServicePlaylistManager2 : public IAIMPServicePlaylistManager 
{
	public:
		virtual HRESULT WINAPI GetPreimageFactory(INT32 Index, IAIMPExtensionPlaylistPreimageFactory** Factory) = 0;
		virtual HRESULT WINAPI GetPreimageFactoryByID(IAIMPString* ID, IAIMPExtensionPlaylistPreimageFactory** Factory) = 0;
		virtual INT32 WINAPI GetPreimageFactoryCount() = 0;
};

#endif // !apiPlaylistsH
