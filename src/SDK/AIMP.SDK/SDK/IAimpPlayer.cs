//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
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
using AIMP.SDK.Playlist;
using AIMP.SDK.TagEditor;
using AIMP.SDK.Threading;
using AIMP.Win32;

namespace AIMP.SDK
{
    /// <summary>
    /// Interface IAimpPlayer
    /// Implements the <see cref="System.IDisposable" />
    /// </summary>
    /// <seealso cref="System.IDisposable" />
    public interface IAimpPlayer : IDisposable
    {
        /// <summary>
        /// Gets Player core.
        /// </summary>
        /// <value>The core.</value>
        IAimpCore Core { get; }

        /// <summary>
        /// Gets player menu manager.
        /// </summary>
        /// <value>The menu manager.</value>
        IAimpServiceMenuManager ServiceMenuManager { get; }

        /// <summary>
        /// Gets player action manager.
        /// </summary>
        /// <value>The action manager.</value>
        IAimpServiceActionManager ServiceActionManager { get; }

        /// <summary>
        /// Gets the MUI manager.
        /// </summary>
        /// <value>The MUI manager.</value>
        // ReSharper disable InconsistentNaming
        IAimpServiceMUI ServiceMui { get; }
        // ReSharper restore InconsistentNaming

        /// <summary>
        /// Gets the album art manager.
        /// </summary>
        /// <value>The service album art.</value>
        IAimpServiceAlbumArt ServiceAlbumArt { get; }

        /// <summary>
        /// Gets the service album art cache.
        /// </summary>
        /// <value>The service album art cache.</value>
        IAimpServiceAlbumArtCache ServiceAlbumArtCache { get; }

        /// <summary>
        /// Gets the configuration manager.
        /// </summary>
        /// <value>The service configuration.</value>
        IAimpServiceConfig ServiceConfig { get; }

        /// <summary>
        /// Gets the play list manager.
        /// </summary>
        /// <value>The playlist manager.</value>
        IAimpServicePlaylistManager ServicePlaylistManager { get; }

        /// <summary>
        /// Gets the playback queue manager.
        /// </summary>
        /// <value>The service playback queue.</value>
        IAimpServicePlaybackQueue ServicePlaybackQueue { get; }

        /// <summary>
        /// Gets the service options dialog.
        /// </summary>
        /// <value>The service options dialog.</value>
        IAimpServiceOptionsDialog ServiceOptionsDialog { get; }

        /// <summary>
        /// Gets the service message dispatcher.
        /// </summary>
        /// <value>The service message dispatcher.</value>
        IAimpServiceMessageDispatcher ServiceMessageDispatcher { get; }

        /// <summary>
        /// Gets the service shutdown.
        /// </summary>
        /// <value>The service shutdown.</value>
        IAimpServiceShutdown ServiceShutdown { get; }

        IAimpServicePlayer ServicePlayer { get; }

        /// <summary>
        /// Gets the win32 manager.
        /// </summary>
        /// <value>The win32 manager.</value>
        IWin32Manager Win32Manager { get; }

        /// <summary>
        /// Gets the service synchronizer.
        /// </summary>
        /// <value>The service synchronizer.</value>
        IAimpServiceSynchronizer ServiceSynchronizer { get; }

        /// <summary>
        /// Gets the service thread pool.
        /// </summary>
        /// <value>The service thread pool.</value>
        IAimpServiceThreadPool ServiceThreadPool { get; }

        /// <summary>
        /// Gets the service music library.
        /// </summary>
        /// <value>The service music library.</value>
        IAimpServiceMusicLibrary ServiceMusicLibrary { get; }

        /// <summary>
        /// Gets the service music library UI.
        /// </summary>
        /// <value>The service music library UI.</value>
        IAimpServiceMusicLibraryUI ServiceMusicLibraryUi { get; }

        /// <summary>
        /// Gets the service file formats.
        /// </summary>
        /// <value>The service file formats.</value>
        IAimpServiceFileFormats ServiceFileFormats { get; }

        /// <summary>
        /// Gets the service file information.
        /// </summary>
        /// <value>The service file information.</value>
        IAimpServiceFileInfo ServiceFileInfo { get; }

        /// <summary>
        /// Gets the service file systems.
        /// </summary>
        /// <value>The service file systems.</value>
        IAimpServiceFileSystems ServiceFileSystems { get; }

        /// <summary>
        /// Gets the service file streaming.
        /// </summary>
        /// <value>The service file streaming.</value>
        IAimpServiceFileStreaming ServiceFileStreaming { get; }

        /// <summary>
        /// Gets the file information formatter service.
        /// </summary>
        IAimpServiceFileInfoFormatter ServiceFileInfoFormatter { get; }

        /// <summary>
        /// Gets the service file tag editor.
        /// </summary>
        IAimpServiceFileTagEditor ServiceFileTagEditor { get; }

        /// <summary>
        /// Gets the lyrics service.
        /// </summary>
        IAimpServiceLyrics ServiceLyrics { get; }

        /// <summary>
        /// Gets the service threads.
        /// </summary>
        IAimpServiceThreads ServiceThreads { get; }

        /// <summary>
        /// Gets the version information service.
        /// </summary>
        IAimpServiceVersionInfo ServiceVersionInfo { get; }

        /// <summary>
        /// Gets the equalizer service.
        /// </summary>
        IAimpServicePlayerEqualizer ServicePlayerEqualizer { get; }

        /// <summary>
        /// Gets the equalizer presets service.
        /// </summary>
        IAimpServicePlayerEqualizerPresets ServicePlayerEqualizerPresets { get; }

        /// <summary>
        /// Gets the waveform service.
        /// </summary>
        IAimpServiceWaveform ServiceWaveform { get; }

        /// <summary>
        /// 
        /// </summary>
        IAimpServiceFileInfoFormatterUtils ServiceFileInfoFormatterUtils { get; }

        IAimpServiceFileURI ServiceFileUri { get; }

        IAimpServiceFileURI2 ServiceFileUri2 { get; }

        /// <summary>
        /// Gets the service connection settings.
        /// </summary>
        IAimpServiceConnectionSettings ServiceConnectionSettings { get; }
    }
}
