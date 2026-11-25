using System;

namespace AIMP.Internal
{
    /// <summary>
    /// Well known interface identifiers. Any other IID can be declared by the
    /// plugin itself and used with <see cref="AimpCore.GetService{T}"/>.
    /// </summary>
    internal static class AimpIids
    {
        public static readonly Guid IUnknown = new Guid("00000000-0000-0000-C000-000000000046");
        public static readonly Guid IAIMPCore = new Guid("41494D50-436F-7265-0000-000000000000");
        public static readonly Guid IAIMPString = new Guid("41494D50-5374-7269-6E67-000000000000");
        public static readonly Guid IAIMPPropertyList = new Guid("41494D50-5072-6F70-4C69-737400000000");
        public static readonly Guid IAIMPPropertyList2 = new Guid("41494D50-5072-6F70-4C69-737432000000");
        public static readonly Guid IAIMPObjectList = new Guid("41494D50-4F62-6A4C-6973-740000000000");
        public static readonly Guid IAIMPObjectList2 = new Guid("41494D50-4F62-6A4C-6973-743200000000");
        public static readonly Guid IAIMPStream = new Guid("41494D50-5374-7265-616D-000000000000");
        public static readonly Guid IAIMPMemoryStream = new Guid("41494D50-4D65-6D53-7472-65616D000000");
        public static readonly Guid IAIMPConfig = new Guid("41494D50-436F-6E66-6967-000000000000");
        public static readonly Guid IAIMPActionEvent = new Guid("41494D50-4163-7469-6F6E-4576656E7400");
        public static readonly Guid IAIMPAction = new Guid("41494D50-4163-7469-6F6E-000000000000");
        public static readonly Guid IAIMPServiceActionManager = new Guid("41494D50-5372-7641-6374-696F6E4D616E");
        public static readonly Guid IAIMPTask = new Guid("41494D50-5461-736B-3200-000000000000");
        public static readonly Guid IAIMPTaskPriority = new Guid("41494D50-5461-736B-5072-696F72697479");
        public static readonly Guid IAIMPServiceThreads = new Guid("41494D50-5372-7654-6872-656164730000");
        public static readonly Guid IAIMPServiceVersionInfo = new Guid("41494D50-5372-7656-6572-496E666F0000");
        public static readonly Guid IAIMPServiceLog = new Guid("41494D50-5372-764C-6F67-000000000000");
        public static readonly Guid IAIMPServiceMessageDispatcher = new Guid("41494D50-5372-764D-7367-447370720000");
        public static readonly Guid IAIMPMessageHook = new Guid("FC6FB524-A959-4089-AA0A-EA40AB7374CD");

        // Client services
        public static readonly Guid IAIMPServiceShutdown = new Guid("41494D50-5372-7653-6875-74646F776E00");
        public static readonly Guid IAIMPServiceFileFormats = new Guid("41494D50-5372-7646-696C-65466D747300");
        public static readonly Guid IAIMPServiceFileInfoFormatter = new Guid("41494D50-5372-7646-6C49-6E66466D7400");

        public static readonly Guid IAIMPServiceFileInfoFormatterUtils =
            new Guid("41494D50-5372-7646-6C49-6E66466D7455");

        public static readonly Guid IAIMPServiceFileStreaming = new Guid("41494D50-5372-7646-696C-655374726D00");
        public static readonly Guid IAIMPServiceFileURI = new Guid("41494D50-5372-7646-696C-655552490000");
        public static readonly Guid IAIMPServiceFileURI2 = new Guid("41494D50-5372-7646-696C-655552493200");
        public static readonly Guid IAIMPServiceFileURI3 = new Guid("41494D50-5372-7646-696C-655552493300");
        public static readonly Guid IAIMPExtensionExternalCatalog = new Guid("41494D50-4578-7445-7874-726E43617400");
        public static readonly Guid IAIMPServiceFileManager = new Guid("41494D50-5372-7646-696C-654D616E0000");
        public static readonly Guid IAIMPServiceConnectionSettings = new Guid("4941494D-5053-7276-436F-6E6E43666700");
        public static readonly Guid IAIMPServiceHTTPClient = new Guid("41494D50-5372-7648-7474-70436C740000");
        public static readonly Guid IAIMPServiceHTTPClient2 = new Guid("41494D50-5372-7648-7474-70436C743200");
        public static readonly Guid IAIMPServiceHTTPClient3 = new Guid("41494D50-5372-7648-7474-70436C743300");
        public static readonly Guid IAIMPHTTPClientEvents = new Guid("41494D50-4874-7470-436C-744576747300");
        public static readonly Guid IAIMPHTTPClientEvents2 = new Guid("41494D50-4874-7470-436C-744576747332");
        public static readonly Guid IAIMPServiceMUI = new Guid("41494D50-5372-764D-5549-000000000000");
        public static readonly Guid IAIMPServiceOptionsDialog = new Guid("41494D50-5372-764F-7074-446C67000000");
        public static readonly Guid IAIMPServiceThreadPool = new Guid("41494D50-5372-7654-6872-64506F6F6C00");
        public static readonly Guid IAIMPServiceSynchronizer = new Guid("41494D50-5372-7653-796E-637200000000");
        public static readonly Guid IAIMPServicePlayer = new Guid("41494D50-5372-7650-6C61-796572000000");
        public static readonly Guid IAIMPServicePlayer2 = new Guid("41494D50-5372-7650-6C61-796572320000");
        public static readonly Guid IAIMPServicePlaybackQueue = new Guid("41494D50-5372-7650-6C62-61636B510000");
        public static readonly Guid IAIMPServicePlaybackQueue2 = new Guid("41494D50-5372-7650-6C62-61636B513200");
        public static readonly Guid IAIMPServicePlayerEqualizer = new Guid("41494D50-5372-7645-5132-000000000000");

        public static readonly Guid IAIMPServicePlayerEqualizerPresets =
            new Guid("41494D50-5372-7645-5150-727374733200");

        public static readonly Guid IAIMPServiceWaveform = new Guid("41494D50-5372-7657-6176-650000000000");
        public static readonly Guid IAIMPServiceFileTagEditor = new Guid("41494D50-5372-7654-6167-456469740000");
        public static readonly Guid IAIMPServiceLyrics = new Guid("41494D50-5372-764C-7972-697800000000");
        public static readonly Guid IAIMPServiceAlbumArt = new Guid("41494D50-5372-7641-6C62-417274000000");
        public static readonly Guid IAIMPServiceAlbumArtCache = new Guid("41494D50-5372-7641-6C62-417274434300");

        // Client objects
        public static readonly Guid IAIMPPlaybackQueueItem = new Guid("41494D50-506C-6179-6261-636B5149746D");
        public static readonly Guid IAIMPEqualizerBands = new Guid("41494D50-4571-4261-6E64-730000000000");
        public static readonly Guid IAIMPEqualizerPreset = new Guid("41494D50-4571-5072-7374-320000000000");
        public static readonly Guid IAIMPFileTagEditor = new Guid("41494D50-4669-6C65-5461-674564697400");
        public static readonly Guid IAIMPFileTag = new Guid("41494D50-4669-6C65-5461-670000000000");
        public static readonly Guid IAIMPLyrics = new Guid("41494D50-4C79-7269-6373-46696C650000");
        public static readonly Guid IAIMPOptionsDialogFrame = new Guid("41494D50-4F70-7444-6C67-4672616D6500");

        public static readonly Guid IAIMPOptionsDialogFrameKeyboardHelper =
            new Guid("41494D50-4F70-7444-6C67-46726D4B4870");

        public static readonly Guid IAIMPOptionsDialogFrameKeyboardHelper2 =
            new Guid("41494D50-4F70-7444-6C67-46726D4B4832");

        public static readonly Guid IAIMPExternalSettingsDialog = new Guid("41494D50-4578-7472-6E4F-7074446C6700");
        public static readonly Guid IAIMPAlbumArtRequest = new Guid("41494D50-416C-6241-7274-526571737400");
        public static readonly Guid IAIMPImageContainer = new Guid("41494D50-496D-6167-6543-6F6E746E7200");
        public static readonly Guid IAIMPImage = new Guid("41494D50-496D-6167-6500-000000000000");
        public static readonly Guid IAIMPErrorInfo = new Guid("41494D50-4572-7249-6E66-6F0000000000");
        public static readonly Guid IAIMPImage3 = new Guid("41494D50-496D-6167-6533-000000000000");
        public static readonly Guid IAIMPConfigFile = new Guid("41494D50-436F-6E66-6967-46696C650000");
        public static readonly Guid IAIMPNamedContainer = new Guid("41494D50-4E61-6D65-6443-6E7472000000");
        public static readonly Guid IAIMPHashCode = new Guid("41494D50-4861-7368-436F-646500000000");

        // File manager
        public static readonly Guid IAIMPFileInfo = new Guid("41494D50-4669-6C65-496E-666F00000000");
        public static readonly Guid IAIMPExtensionFileSystem = new Guid("41494D50-4578-7446-5300-000000000000");
        public static readonly Guid IAIMPExtensionFileInfoProvider = new Guid("41494D50-4578-7446-696C-65496E666F00");
        public static readonly Guid IAIMPExtensionFileInfoProviderEx = new Guid("41494D50-4578-7446-696C-65496E666F45");

        public static readonly Guid IAIMPFileSystemCommandOpenFileFolder =
            new Guid("41465343-6D64-4669-6C65-466C64720000");

        public static readonly Guid IAIMPFileSystemCommandCopyToClipboard =
            new Guid("41465343-6D64-436F-7079-32436C706264");

        public static readonly Guid IAIMPFileSystemCommandDelete = new Guid("41465343-6D64-4465-6C65-746500000000");
        public static readonly Guid IAIMPFileSystemCommandDropSource = new Guid("41465343-6D64-4472-6F70-537263000000");
        public static readonly Guid IAIMPFileSystemCommandFileInfo = new Guid("41465343-6D64-4669-6C65-457869737470");

        public static readonly Guid IAIMPFileSystemCommandFileInfoLegacy =
            new Guid("41494D50-4578-7446-696C-65496E666F00");

        public static readonly Guid IAIMPFileSystemCommandStreaming = new Guid("41465343-6D64-5374-7265-616D696E6700");
        public static readonly Guid IAIMPServiceFileSystems = new Guid("41494D50-5372-7646-5300-000000000000");
        public static readonly Guid IAIMPServiceFileInfo = new Guid("41494D50-5372-7646-696C-65496E666F00");

        // Menu
        public static readonly Guid IAIMPMenuItem = new Guid("41494D50-4D65-6E75-4974-656D00000000");
        public static readonly Guid IAIMPServiceMenuManager = new Guid("41494D50-5372-764D-656E-754D6E677200");

        // Music library
        public static readonly Guid IAIMPMLDataField = new Guid("41494D50-4D4C-4461-7461-466C64000000");
        public static readonly Guid IAIMPMLDataFieldFilter = new Guid("41494D50-4D4C-466C-6446-6C7400000000");
        public static readonly Guid IAIMPMLDataFieldFilterByArray = new Guid("41494D50-4D4C-466C-6446-6C7441727200");
        public static readonly Guid IAIMPMLDataFilter = new Guid("41494D50-4D4C-4669-6C74-657200000000");
        public static readonly Guid IAIMPMLDataFilterGroup = new Guid("41494D50-4D4C-466C-7447-727000000000");
        public static readonly Guid IAIMPMLDataProvider = new Guid("41494D50-4D4C-4461-7461-507276000000");
        public static readonly Guid IAIMPMLDataProvider2 = new Guid("41494D50-4D4C-4461-7461-507276320000");
        public static readonly Guid IAIMPMLDataProviderSelection = new Guid("41494D50-4D4C-4461-7461-50727653656C");
        public static readonly Guid IAIMPMLDataStorage = new Guid("41494D50-4D4C-4461-7461-537467000000");
        public static readonly Guid IAIMPMLDataStorage2 = new Guid("41494D50-4D4C-4461-7461-537467320000");
        public static readonly Guid IAIMPMLDataStorageManager = new Guid("41494D50-4D4C-4453-4D6E-677200000000");

        public static readonly Guid IAIMPMLDataStorageCommandAddFiles =
            new Guid("41494D50-4D4C-4453-436D-644164640000");

        public static readonly Guid IAIMPMLDataStorageCommandAddFilesDialog =
            new Guid("41494D50-4D4C-4453-436D-644164644400");

        public static readonly Guid IAIMPMLDataStorageCommandDeleteFiles =
            new Guid("41494D50-4D4C-4453-436D-6444656C0000");

        public static readonly Guid IAIMPMLDataStorageCommandDeleteFiles2 =
            new Guid("41494D50-4D4C-4453-436D-6444656C3200");

        public static readonly Guid IAIMPMLDataStorageCommandDropData =
            new Guid("41494D50-4D4C-4453-436D-6444726F7000");

        public static readonly Guid IAIMPMLDataStorageCommandReloadTags =
            new Guid("41494D50-4D4C-4453-436D-645570546167");

        public static readonly Guid IAIMPMLDataStorageCommandReportDialog =
            new Guid("41494D50-4D4C-4453-436D-645270727400");

        public static readonly Guid IAIMPMLDataStorageCommandUserMark =
            new Guid("41494D50-4D4C-4453-436D-644D61726B00");

        public static readonly Guid IAIMPMLFileList = new Guid("41494D50-4D4C-4669-6C65-4C6973740000");
        public static readonly Guid IAIMPMLGroupingPreset = new Guid("41494D50-4D4C-4772-7050-737400000000");
        public static readonly Guid IAIMPMLGroupingPresetStandard = new Guid("41494D50-4D4C-4772-7050-737453746400");
        public static readonly Guid IAIMPMLGroupingPresets = new Guid("41494D50-4D4C-4772-5072-737473000000");
        public static readonly Guid IAIMPMLSortDirection = new Guid("41494D50-4D4C-536F-7274-446972746E00");
        public static readonly Guid IAIMPMLGroupingTreeDataProvider = new Guid("41494D50-4D4C-4772-7044-617461507276");
        public static readonly Guid IAIMPMLGroupingTreeDataProvider2 = new Guid("41494D50-4D4C-4772-7044-617461507232");

        public static readonly Guid IAIMPMLGroupingTreeDataProviderSelection =
            new Guid("41494D50-4D4C-4772-4474-50727653656C");

        public static readonly Guid IAIMPMLGroupingTreeSelection = new Guid("41494D50-4D4C-4770-5472-656553656C00");
        public static readonly Guid IAIMPMLPlaylistPreimage = new Guid("414D4C53-6D50-6C73-5372-630000000000");
        public static readonly Guid IAIMPMLExtensionDataStorage = new Guid("41494D50-4578-744D-4C44-530000000000");
        public static readonly Guid IAIMPServiceMusicLibrary = new Guid("41494D50-5372-764D-4C00-000000000000");
        public static readonly Guid IAIMPServiceMusicLibraryUI = new Guid("41494D50-5372-764D-4C55-490000000000");

        // Playlists
        public static readonly Guid IAIMPPlaylist = new Guid("41494D50-506C-7300-0000-000000000000");
        public static readonly Guid IAIMPPlaylistItem = new Guid("41494D50-506C-7349-7465-6D0000000000");
        public static readonly Guid IAIMPPlaylistGroup = new Guid("41494D50-506C-7347-726F-757000000000");
        public static readonly Guid IAIMPPlaylistListener = new Guid("41494D50-506C-734C-7374-6E7200000000");
        public static readonly Guid IAIMPPlaylistListener2 = new Guid("41494D50-506C-734C-7374-6E7232000000");
        public static readonly Guid IAIMPPlaylistQueue = new Guid("41494D50-506C-7351-7565-756500000000");
        public static readonly Guid IAIMPPlaylistQueue2 = new Guid("41494D50-506C-7351-7565-756532000000");
        public static readonly Guid IAIMPExtensionPlaybackQueue = new Guid("41494D50-4578-7450-6C61-796261636B51");
        public static readonly Guid IAIMPExtensionPlaybackQueue2 = new Guid("41494D50-4578-7450-6C61-7962636B5132");
        public static readonly Guid IAIMPPlaylistPreimageFolders = new Guid("41494D50-536D-504C-5372-63466C647273");
        public static readonly Guid IAIMPTaskOwner = new Guid("41494D50-5461-736B-4F77-6E6572320000");
        public static readonly Guid IAIMPPlaylistPreimage = new Guid("41494D50-536D-504C-5372-630000000000");

        public static readonly Guid IAIMPExtensionPlaylistManagerListener =
            new Guid("41494D50-4578-7450-6C73-4D616E4C7472");

        public static readonly Guid IAIMPPlaylistProperties = new Guid("41494D50-506C-7350-726F-707300000000");
        public static readonly Guid IAIMPExtensionPlaylistShuffler = new Guid("41494D50-4578-7450-6C73-536875666C72");

        public static readonly Guid IAIMPExtensionPlaylistPreimageFactory =
            new Guid("41494D50-4578-7453-6D50-6C7346637400");

        public static readonly Guid IAIMPPlaylistPreimageListener = new Guid("41494D50-536D-504C-4D6E-677200000000");

        public static readonly Guid IAIMPPlaylistPreimageDataProvider =
            new Guid("41494D50-536D-506C-7344-617461507276");

        public static readonly Guid IAIMPServicePlaylistManager = new Guid("41494D50-5372-7650-6C73-4D616E000000");
        public static readonly Guid IAIMPServicePlaylistManager2 = new Guid("41494D50-536D-504C-4D6E-677232000000");
        public static readonly Guid IAIMPVisualizationDirectOutput = new Guid("41494D50-5669-7344-4F00-000000000000");
    }
}