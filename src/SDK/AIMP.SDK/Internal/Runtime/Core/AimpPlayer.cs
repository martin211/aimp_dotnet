using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.AlbumArt;
using AIMP.Internal.Native.Core;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Lyrics;
using AIMP.Internal.Native.MenuManager;
using AIMP.Internal.Native.MessageDispatcher;
using AIMP.Internal.Native.MUIManager;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Options;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Native.TagEditor;
using AIMP.Internal.Native.Threading;
using AIMP.Internal.Runtime.Actions;
using AIMP.Internal.Runtime.AlbumArt;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.Lyrics;
using AIMP.Internal.Runtime.MenuManager;
using AIMP.Internal.Runtime.Player;
using AIMP.Internal.Runtime.TagEditor;
using AIMP.Internal.Runtime.Threading;
using AIMP.SDK;
using AIMP.SDK.Actions;
using AIMP.SDK.AlbumArt.Services;
using AIMP.SDK.Configuration;
using AIMP.SDK.Core;
using AIMP.SDK.FileManager;
using AIMP.SDK.Internet;
using AIMP.SDK.Lyrics;
using AIMP.SDK.MenuManager;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.MUIManager;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.Options;
using AIMP.SDK.Player;
using AIMP.SDK.PlayList;
using AIMP.SDK.TagEditor;
using AIMP.SDK.Threading;
using AIMP.SDK.Win32;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpPlayer"/>: access to the services of the player.
    /// </summary>
    internal sealed class AimpPlayer : AimpObjectWrapper, IAimpPlayer
    {
        private readonly AimpCore _core;
        private readonly AimpCoreWrapper _coreWrapper;
        private readonly List<object> _owned = new List<object>();

        private IAimpServiceMenuManager _menuManager;
        private IAimpServiceLog _serviceLog;
        private IAimpServiceMusicLibrary _musicLibrary;
        private IAimpServiceMusicLibraryUI _musicLibraryUi;
        private IAimpServicePlaylistManager _playlistManager;
        private IAimpServiceFileSystems _fileSystems;
        private IAimpServiceFileInfo _fileInfo;
        private IAimpServiceConfig _config;
        private IWin32Manager _win32;
        private IAimpServiceVersionInfo _versionInfo;
        private IAimpServiceMessageDispatcher _messageDispatcher;
        private IAimpServiceActionManager _actionManager;
        private IAimpServiceShutdown _shutdown;
        private IAimpServiceFileFormats _fileFormats;
        private IAimpServiceFileStreaming _fileStreaming;
        private IAimpServiceFileInfoFormatter _fileInfoFormatter;
        private IAimpServiceFileInfoFormatterUtils _fileInfoFormatterUtils;
        private IAimpServiceFileURI _fileUri;
        private IAimpServiceFileURI2 _fileUri2;
        private IAimpServiceFileURI3 _fileUri3;
        private IAimpServiceConnectionSettings _connectionSettings;
        private IAimpServiceMUI _mui;
        private IAimpServiceOptionsDialog _optionsDialog;
        private IAimpServiceWaveform _waveform;
        private IAimpServiceThreads _threads;
        private IAimpServiceThreadPool _threadPool;
        private IAimpServiceSynchronizer _synchronizer;
        private IAimpServicePlayer _player;
        private IAimpServicePlaybackQueue _playbackQueue;
        private IAimpServicePlayerEqualizer _equalizer;
        private IAimpServicePlayerEqualizerPresets _equalizerPresets;
        private IAimpServiceFileTagEditor _fileTagEditor;
        private IAimpServiceLyrics _lyrics;
        private IAimpServiceAlbumArt _albumArt;
        private IAimpServiceAlbumArtCache _albumArtCache;

        public AimpPlayer(AimpCore core)
        {
            _core = core ?? throw new ArgumentNullException(nameof(core));
            _coreWrapper = Own(new AimpCoreWrapper(core));
        }

        private T Own<T>(T value)
        {
            if (value != null)
            {
                _owned.Add(value);
            }

            return value;
        }

        private TService Service<TNative, TService>(Guid iid, Func<IntPtr, TService> factory)
            where TNative : class
            where TService : class
        {
            var native = _core.GetService<TNative>(iid);
            if (native == null)
            {
                return null;
            }

            var unknown = Marshal.GetIUnknownForObject(native);
            try
            {
                return Own(factory(unknown));
            }
            finally
            {
                Marshal.Release(unknown);
                Marshal.ReleaseComObject(native);
            }
        }

        public IAimpCore Core => _coreWrapper;

        public AimpVersion Version => AimpRuntime.Version;

        public IAimpServiceLog ServiceLog
        {
            get
            {
                AimpApiGuard.Require(6, 0, "IAimpServiceLog");
                return _serviceLog ?? (_serviceLog = Service<IAIMPServiceLogNative, IAimpServiceLog>(
                    AimpIids.IAIMPServiceLog,
                    pointer => new AimpServiceLog(pointer)));
            }
        }

        public IAimpServiceMenuManager ServiceMenuManager =>
            _menuManager ?? (_menuManager = Service<IAIMPServiceMenuManagerNative, IAimpServiceMenuManager>(
                AimpIids.IAIMPServiceMenuManager,
                pointer => new AimpMenuService(pointer)));

        public IAimpServiceMusicLibrary ServiceMusicLibrary =>
            _musicLibrary ?? (_musicLibrary = Service<IAIMPServiceMusicLibraryNative, IAimpServiceMusicLibrary>(
                AimpIids.IAIMPServiceMusicLibrary,
                pointer => new AimpMusicLibraryService(pointer)));

        public IAimpServiceMusicLibraryUI ServiceMusicLibraryUi =>
            _musicLibraryUi ?? (_musicLibraryUi =
                Service<IAIMPServiceMusicLibraryUINative, IAimpServiceMusicLibraryUI>(
                    AimpIids.IAIMPServiceMusicLibraryUI,
                    pointer => new AimpMusicLibraryUiService(pointer)));

        public IAimpServicePlaylistManager ServicePlaylistManager =>
            _playlistManager ?? (_playlistManager =
                Service<IAIMPServicePlaylistManager2Native, IAimpServicePlaylistManager>(
                    AimpIids.IAIMPServicePlaylistManager2,
                    pointer => new AimpPlaylistManagerService(pointer)));

        public IAimpServiceFileSystems ServiceFileSystems =>
            _fileSystems ?? (_fileSystems = Service<IAIMPServiceFileSystemsNative, IAimpServiceFileSystems>(
                AimpIids.IAIMPServiceFileSystems,
                pointer => new AimpFileSystemsService(pointer)));

        public IAimpServiceFileInfo ServiceFileInfo =>
            _fileInfo ?? (_fileInfo = Service<IAIMPServiceFileInfoNative, IAimpServiceFileInfo>(
                AimpIids.IAIMPServiceFileInfo,
                pointer => new AimpFileInfoService(pointer)));

        public IAimpServiceConfig ServiceConfig =>
            _config ?? (_config = Own<IAimpServiceConfig>(new AimpConfigService(_core)));

        public IWin32Manager Win32Manager => _win32 ?? (_win32 = Own<IWin32Manager>(new AimpWin32Manager()));

        public IAimpServiceVersionInfo ServiceVersionInfo =>
            _versionInfo ?? (_versionInfo =
                Service<IAIMPServiceVersionInfoNative, IAimpServiceVersionInfo>(
                    AimpIids.IAIMPServiceVersionInfo,
                    pointer => new AimpServiceVersionInfo(pointer)));

        public IAimpServiceMessageDispatcher ServiceMessageDispatcher =>
            _messageDispatcher ?? (_messageDispatcher =
                Service<IAIMPServiceMessageDispatcherNative, IAimpServiceMessageDispatcher>(
                    AimpIids.IAIMPServiceMessageDispatcher,
                    pointer => new AimpServiceMessageDispatcher(pointer)));

        // Services that are not projected yet.
        public IAimpServiceActionManager ServiceActionManager =>
            _actionManager ?? (_actionManager =
                Own<IAimpServiceActionManager>(new AimpActionService(_core)));

        public IAimpServiceShutdown ServiceShutdown =>
            _shutdown ?? (_shutdown = Service<IAIMPServiceShutdownNative, IAimpServiceShutdown>(
                AimpIids.IAIMPServiceShutdown,
                pointer => new AimpServiceShutdown(pointer)));

        public IAimpServiceFileFormats ServiceFileFormats =>
            _fileFormats ?? (_fileFormats = Service<IAIMPServiceFileFormatsNative, IAimpServiceFileFormats>(
                AimpIids.IAIMPServiceFileFormats,
                pointer => new AimpServiceFileFormats(pointer)));

        public IAimpServiceFileStreaming ServiceFileStreaming =>
            _fileStreaming ?? (_fileStreaming = Service<IAIMPServiceFileStreamingNative, IAimpServiceFileStreaming>(
                AimpIids.IAIMPServiceFileStreaming,
                pointer => new AimpServiceFileStreaming(pointer)));

        public IAimpServiceFileInfoFormatter ServiceFileInfoFormatter =>
            _fileInfoFormatter ?? (_fileInfoFormatter =
                Service<IAIMPServiceFileInfoFormatterNative, IAimpServiceFileInfoFormatter>(
                    AimpIids.IAIMPServiceFileInfoFormatter,
                    pointer => new AimpServiceFileInfoFormatter(pointer)));

        public IAimpServiceFileInfoFormatterUtils ServiceFileInfoFormatterUtils =>
            _fileInfoFormatterUtils ?? (_fileInfoFormatterUtils =
                Service<IAIMPServiceFileInfoFormatterUtilsNative, IAimpServiceFileInfoFormatterUtils>(
                    AimpIids.IAIMPServiceFileInfoFormatterUtils,
                    pointer => new AimpServiceFileInfoFormatterUtils(pointer)));

        public IAimpServiceFileURI ServiceFileUri =>
            _fileUri ?? (_fileUri = Service<IAIMPServiceFileURI2Native, IAimpServiceFileURI>(
                AimpIids.IAIMPServiceFileURI2,
                pointer => new AimpServiceFileUri(pointer)));

        public IAimpServiceFileURI2 ServiceFileUri2 =>
            _fileUri2 ?? (_fileUri2 = Service<IAIMPServiceFileURI2Native, IAimpServiceFileURI2>(
                AimpIids.IAIMPServiceFileURI2,
                pointer => new AimpServiceFileUri(pointer)));

        public IAimpServiceFileURI3 ServiceFileUri3
        {
            get
            {
                AimpApiGuard.Require(6, 0, "IAimpServiceFileURI3");
                return _fileUri3 ?? (_fileUri3 = Service<IAIMPServiceFileURI3Native, IAimpServiceFileURI3>(
                    AimpIids.IAIMPServiceFileURI3,
                    pointer => new AimpServiceFileUri(pointer)));
            }
        }

        public IAimpServiceConnectionSettings ServiceConnectionSettings =>
            _connectionSettings ?? (_connectionSettings =
                Service<IAIMPPropertyListNative, IAimpServiceConnectionSettings>(
                    AimpIids.IAIMPServiceConnectionSettings,
                    pointer => new AimpServiceConnectionSettings(pointer)));

        public IAimpServiceMUI ServiceMui =>
            _mui ?? (_mui = Service<IAIMPServiceMUINative, IAimpServiceMUI>(
                AimpIids.IAIMPServiceMUI,
                pointer => new AimpServiceMui(pointer)));

        public IAimpServiceOptionsDialog ServiceOptionsDialog =>
            _optionsDialog ?? (_optionsDialog = Service<IAIMPServiceOptionsDialogNative, IAimpServiceOptionsDialog>(
                AimpIids.IAIMPServiceOptionsDialog,
                pointer => new AimpServiceOptionsDialog(pointer)));

        public IAimpServiceWaveform ServiceWaveform =>
            _waveform ?? (_waveform = Own<IAimpServiceWaveform>(new AimpServiceWaveform()));

        public IAimpServiceAlbumArt ServiceAlbumArt =>
            _albumArt ?? (_albumArt = Service<IAIMPServiceAlbumArtNative, IAimpServiceAlbumArt>(
                AimpIids.IAIMPServiceAlbumArt,
                pointer => new AimpServiceAlbumArt(pointer)));

        public IAimpServiceAlbumArtCache ServiceAlbumArtCache =>
            _albumArtCache ?? (_albumArtCache = Service<IAIMPServiceAlbumArtCacheNative, IAimpServiceAlbumArtCache>(
                AimpIids.IAIMPServiceAlbumArtCache,
                pointer => new AimpServiceAlbumArtCache(pointer)));

        public IAimpServicePlaybackQueue ServicePlaybackQueue =>
            _playbackQueue ?? (_playbackQueue = Service<IAIMPServicePlaybackQueue2Native, IAimpServicePlaybackQueue>(
                AimpIids.IAIMPServicePlaybackQueue2,
                pointer => new AimpServicePlaybackQueue(pointer)));

        public IAimpServicePlayer ServicePlayer =>
            _player ?? (_player = Service<IAIMPServicePlayer2Native, IAimpServicePlayer>(
                AimpIids.IAIMPServicePlayer2,
                pointer => new AimpPlayerService(pointer)));

        public IAimpServiceSynchronizer ServiceSynchronizer =>
            _synchronizer ?? (_synchronizer = Service<IAIMPServiceSynchronizerNative, IAimpServiceSynchronizer>(
                AimpIids.IAIMPServiceSynchronizer,
                pointer => new AimpServiceSynchronizer(pointer)));

        public IAimpServiceThreadPool ServiceThreadPool =>
            _threadPool ?? (_threadPool = Service<IAIMPServiceThreadPoolNative, IAimpServiceThreadPool>(
                AimpIids.IAIMPServiceThreadPool,
                pointer => new AimpServiceThreadPool(pointer)));

        public IAimpServiceFileTagEditor ServiceFileTagEditor =>
            _fileTagEditor ?? (_fileTagEditor = Service<IAIMPServiceFileTagEditorNative, IAimpServiceFileTagEditor>(
                AimpIids.IAIMPServiceFileTagEditor,
                pointer => new AimpServiceFileTagEditor(pointer)));

        public IAimpServiceLyrics ServiceLyrics =>
            _lyrics ?? (_lyrics = Service<IAIMPServiceLyricsNative, IAimpServiceLyrics>(
                AimpIids.IAIMPServiceLyrics,
                pointer => new AimpServiceLyrics(pointer)));

        public IAimpServiceThreads ServiceThreads =>
            _threads ?? (_threads = Service<IAIMPServiceThreadsNative, IAimpServiceThreads>(
                AimpIids.IAIMPServiceThreads,
                pointer => new AimpServiceThreads(pointer)));

        public IAimpServicePlayerEqualizer ServicePlayerEqualizer =>
            _equalizer ?? (_equalizer = Service<IAIMPServicePlayerEqualizerNative, IAimpServicePlayerEqualizer>(
                AimpIids.IAIMPServicePlayerEqualizer,
                pointer => new AimpServicePlayerEqualizer(pointer)));

        public IAimpServicePlayerEqualizerPresets ServicePlayerEqualizerPresets =>
            _equalizerPresets ?? (_equalizerPresets =
                Service<IAIMPServicePlayerEqualizerPresetsNative, IAimpServicePlayerEqualizerPresets>(
                    AimpIids.IAIMPServicePlayerEqualizerPresets,
                    pointer => new AimpServicePlayerEqualizerPresets(pointer)));


        protected override void OnDispose()
        {
            for (var i = _owned.Count - 1; i >= 0; i--)
            {
                try
                {
                    (_owned[i] as IDisposable)?.Dispose();
                }
                catch (Exception exception)
                {
                    AimpLog.Write(exception);
                }
            }

            _owned.Clear();
        }
    }
}