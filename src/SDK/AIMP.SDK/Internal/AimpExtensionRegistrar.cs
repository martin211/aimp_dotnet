using System;
using System.Collections.Generic;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.AlbumArt;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Options;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Core;
using AIMP.SDK.AlbumArt.Extensions;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.MusicLibrary.Extension;
using AIMP.SDK.Options;
using AIMP.SDK.Player.Extensions;
using AIMP.SDK.PlayList.Extensions;

namespace AIMP.Internal
{
    /// <summary>
    /// Maps the v1 extension contracts to their COM bridges and registers the
    /// resulting objects with the matching extension point of the player.
    /// </summary>
    internal static class AimpExtensionRegistrar
    {
        private sealed class Registration
        {
            public object Extension;
            public object Bridge;
            public IntPtr Pointer;
            public Guid ServiceIid;
        }

        private static readonly object Sync = new object();
        private static readonly List<Registration> Registrations = new List<Registration>();

        public static int Register(AimpCore core, object extension)
        {
            if (core == null || extension == null)
            {
                return Safe.E_INVALIDARG;
            }

            // Validate AIMP 6-only contracts before anything is registered.
            if (extension is IAimpExtensionExternalCatalog)
            {
                AimpApiGuard.Require(6, 0, "IAimpExtensionExternalCatalog");
            }

            if (extension is IAimpExtensionPlaylistShuffler)
            {
                AimpApiGuard.Require(6, 0, "IAimpExtensionPlaylistShuffler");
            }

            var result = Safe.E_NOTIMPL;
            var registered = 0;

            var albumArtProvider = extension as IAimpExtensionAlbumArtProvider3;
            if (albumArtProvider != null)
            {
                result = Register(
                    core,
                    extension,
                    new AlbumArtProvider3Bridge(albumArtProvider),
                    AimpIids.IAIMPServiceAlbumArt,
                    typeof(IAIMPExtensionAlbumArtProvider3Native));
                registered++;
            }

            var fileExpander = extension as IAimpExtensionFileExpander;
            if (fileExpander != null)
            {
                result = Register(
                    core,
                    extension,
                    new FileExpanderBridge(fileExpander),
                    AimpIids.IAIMPServiceFileManager,
                    typeof(IAIMPExtensionFileExpanderNative));
                registered++;
            }

            var fileFormat = extension as IAimpExtensionFileFormat;
            if (fileFormat != null)
            {
                result = Register(
                    core,
                    extension,
                    new FileFormatBridge(fileFormat),
                    AimpIids.IAIMPServiceFileFormats,
                    typeof(IAIMPExtensionFileFormatNative));
                registered++;
            }

            var playerHook = extension as IAimpExtensionPlayerHook;
            if (playerHook != null)
            {
                result = Register(
                    core,
                    extension,
                    new PlayerHookBridge(playerHook),
                    AimpIids.IAIMPServicePlayer,
                    typeof(IAIMPExtensionPlayerHookNative));
                registered++;
            }

            var waveformProvider = extension as IAimpExtensionWaveFormProvider;
            if (waveformProvider != null)
            {
                result = Register(
                    core,
                    extension,
                    new WaveformProviderBridge(waveformProvider),
                    AimpIids.IAIMPServiceWaveform,
                    typeof(IAIMPExtensionWaveformProviderNative));
                registered++;
            }

            // IAIMPMLDataStorage / IAimpExtensionDataStorage
            var dataStorage = extension as IAimpExtensionDataStorage;
            if (dataStorage != null)
            {
                result = Register(
                    core,
                    extension,
                    new MlStorageBridge(dataStorage),
                    AimpIids.IAIMPServiceMusicLibrary,
                    typeof(IAIMPMLExtensionDataStorageNative));
                registered++;
            }

            var preimageFactory = extension as IAimpExtensionPlaylistPreimageFactory;
            if (preimageFactory != null)
            {
                result = Register(
                    core,
                    extension,
                    new PreimageFactoryBridge(preimageFactory),
                    AimpIids.IAIMPServicePlaylistManager,
                    typeof(IAIMPExtensionPlaylistPreimageFactoryNative));
                registered++;
            }

            var playlistListener = extension as IAimpExtensionPlaylistManagerListener;
            if (playlistListener != null)
            {
                result = Register(
                    core,
                    extension,
                    new PlaylistListenerBridge(playlistListener),
                    AimpIids.IAIMPServicePlaylistManager,
                    typeof(IAIMPExtensionPlaylistManagerListenerNative));
                registered++;
            }

            var externalCatalog = extension as IAimpExtensionExternalCatalog;
            if (externalCatalog != null)
            {
                result = Register(
                    core,
                    extension,
                    new ExternalCatalogBridge(externalCatalog),
                    AimpIids.IAIMPServiceFileManager,
                    typeof(IAIMPExtensionExternalCatalogNative));
                registered++;
            }

            var playlistShuffler = extension as IAimpExtensionPlaylistShuffler;
            if (playlistShuffler != null)
            {
                result = Register(
                    core,
                    extension,
                    new PlaylistShufflerBridge(playlistShuffler),
                    AimpIids.IAIMPServicePlaylistManager2,
                    typeof(IAIMPExtensionPlaylistShufflerNative));
                registered++;
            }

            var optionsFrame = extension as IAimpOptionsDialogFrame;
            if (optionsFrame != null)
            {
                result = Register(
                    core,
                    extension,
                    new OptionsDialogFrameBridge(optionsFrame),
                    AimpIids.IAIMPServiceOptionsDialog,
                    typeof(IAIMPOptionsDialogFrameNative));
                registered++;
            }

            var playbackQueue2 = extension as IAimpExtensionPlaybackQueue2;
            if (playbackQueue2 != null)
            {
                result = Register(
                    core,
                    extension,
                    new PlaybackQueueBridge(playbackQueue2),
                    AimpIids.IAIMPServicePlaybackQueue2,
                    typeof(IAIMPExtensionPlaybackQueue2Native));
                registered++;
            }
            else
            {
                var playbackQueue = extension as IAimpExtensionPlaybackQueue;
                if (playbackQueue != null)
                {
                    result = Register(
                        core,
                        extension,
                        new PlaybackQueueBridge(playbackQueue),
                        AimpIids.IAIMPServicePlaybackQueue,
                        typeof(IAIMPExtensionPlaybackQueueNative));
                    registered++;
                }
            }

            var fileInfoProvider = extension as IAimpExtensionFileInfoProvider;
            if (fileInfoProvider != null)
            {
                result = Register(
                    core,
                    extension,
                    new FileInfoProviderBridge(fileInfoProvider),
                    AimpIids.IAIMPServiceFileInfo,
                    typeof(IAIMPExtensionFileInfoProviderNative));
                registered++;
            }

            var fileSystem = extension as IAimpExtensionFileSystem;
            if (fileSystem != null)
            {
                result = Register(
                    core,
                    extension,
                    new FileSystemBridge(fileSystem),
                    AimpIids.IAIMPServiceFileSystems,
                    typeof(IAIMPExtensionFileSystemNative));
                registered++;
            }

            if (registered == 0)
            {
                AimpLog.Write(
                    $"Extension '{extension.GetType().FullName}' has no supported contract.");
            }
            else if (result < 0)
            {
                AimpLog.Write(
                    $"The player rejected extension '{extension.GetType().FullName}' (0x{result.ToString("X8")}).");
            }

            return registered == 0 ? Safe.E_NOTIMPL : result;
        }

        public static int Unregister(AimpCore core, object extension)
        {
            if (core == null || extension == null)
            {
                return Safe.E_INVALIDARG;
            }

            var result = Safe.E_NOTIMPL;

            lock (Sync)
            {
                for (var i = Registrations.Count - 1; i >= 0; i--)
                {
                    var registration = Registrations[i];
                    if (!ReferenceEquals(registration.Extension, extension))
                    {
                        continue;
                    }

                    result = core.UnregisterExtension(registration.Pointer);

                    if (registration.Pointer != IntPtr.Zero)
                    {
                        AimpComHelper.Release(registration.Pointer);
                    }

                    Registrations.RemoveAt(i);
                }
            }

            return result;
        }

        /// <summary>
        /// Unregisters everything that is still registered.
        /// </summary>
        public static void UnregisterAll(AimpCore core)
        {
            if (core == null)
            {
                return;
            }

            lock (Sync)
            {
                for (var i = Registrations.Count - 1; i >= 0; i--)
                {
                    var registration = Registrations[i];
                    core.UnregisterExtension(registration.Pointer);

                    if (registration.Pointer != IntPtr.Zero)
                    {
                        AimpComHelper.Release(registration.Pointer);
                    }
                }

                Registrations.Clear();
            }
        }

        private static int Register(
            AimpCore core,
            object extension,
            object bridge,
            Guid serviceIid,
            Type nativeInterface)
        {
            var pointer = AimpComHelper.GetPointer(bridge, nativeInterface);

            if (pointer == IntPtr.Zero)
            {
                return Safe.E_FAIL;
            }

            var hr = core.RegisterExtension(serviceIid, pointer);
            if (hr < 0)
            {
                AimpComHelper.Release(pointer);
                return hr;
            }

            lock (Sync)
            {
                Registrations.Add(new Registration
                {
                    Extension = extension,
                    Bridge = bridge,
                    Pointer = pointer,
                    ServiceIid = serviceIid
                });
            }

            return hr;
        }
    }
}