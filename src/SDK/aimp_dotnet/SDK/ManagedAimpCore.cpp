//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "ManagedAimpCore.h"
#include "IUnknownInterfaceImpl.h"
#include "AimpSdk.h"
#include "FileManager/Extensions/InternalAimpExtensionFileExpander.h"
#include "FileManager/Extensions/InternalAimpExtensionFileFormat.h"
#include "FileManager/Extensions/InternalAimpExtensionFileInfoProvider.h"
#include "FileManager/Extensions/InternalAimpExtensionFileSystem.h"
#include "SDK\Options\OptionsDialogFrameExtension.h"
#include "SDK\AlbumArt\AimpExtensionAlbumArtCatalog.h"
#include "SDK\PlayList\AimpExtensionPlaylistManagerListener.h"


namespace AIMP {
    /// <summary>
    /// 
    /// </summary>
    namespace SDK {
        using namespace System;
        using namespace Runtime::InteropServices;
        using namespace AlbumArt::Extensions;
        using namespace Lyrics::Extensions;

        class AIMPMessageHook : public IUnknownInterfaceImpl<IAIMPMessageHook> {
        public:
            explicit AIMPMessageHook(gcroot<ManagedAimpCore^> managedCore) : _managedCore(managedCore) {
            }

            virtual void WINAPI CoreMessage(DWORD AMessage, int AParam1, void* AParam2, HRESULT* AResult) {
            }

        private:
            gcroot<ManagedAimpCore^> _managedCore;
        };

        //class AimpExtensionPlayerHook : public IUnknownInterfaceImpl<IAIMPExtensionPlayerHook>
        //{
        //public:
        //    typedef IUnknownInterfaceImpl<IAIMPExtensionPlayerHook> Base;

        //    explicit AimpExtensionPlayerHook(gcroot<ManagedAimpCore^> managedCore) : _managedCore(managedCore)
        //    {
        //    }

        //    virtual HRESULT WINAPI OnCheckURL(IAIMPString* URL, BOOL* Handled)
        //    {
        //        String^ url = AimpConverter::ToManagedString(URL);
        //        bool handled = _managedCore->OnCheckUrl(*&url);

        //        if (handled)
        //        {
        //            // TODO: Optimize it
        //            *Handled = 1;
        //            IAIMPString* str = AimpConverter::ToAimpString(url);
        //            URL->SetData(str->GetData(), str->GetLength());
        //            str->Release();
        //            str = nullptr;
        //        }
        //        else
        //            *Handled = 0;

        //        return S_OK;
        //    }

        //    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj)
        //    {
        //        if (!ppvObj)
        //        {
        //            return E_POINTER;
        //        }

        //        if (riid == IID_IAIMPExtensionPlayerHook)
        //        {
        //            *ppvObj = this;
        //            AddRef();
        //            return S_OK;
        //        }

        //        return E_NOINTERFACE;
        //    }

        //    virtual ULONG WINAPI AddRef(void)
        //    {
        //        return Base::AddRef();
        //    }

        //    virtual ULONG WINAPI Release(void)
        //    {
        //        return Base::Release();
        //    }

        //private:
        //    gcroot<ManagedAimpCore^> _managedCore;
        //};

        ManagedAimpCore::ManagedAimpCore(IAIMPCore* core) {
            _core = core;
            //AimpExtensionPlayerHook* playerHook = new AimpExtensionPlayerHook(this);
            //core->RegisterExtension(IID_IAIMPServicePlayer, playerHook);

            IAIMPServiceMessageDispatcher* aimp_service_message_dispatcher;
            core->QueryInterface(IID_IAIMPServiceMessageDispatcher,
                                 reinterpret_cast<void**>(&aimp_service_message_dispatcher));
            _hook = new AIMPMessageHook(this);
            aimp_service_message_dispatcher->Hook(_hook);
            _messageDispatcher = aimp_service_message_dispatcher;
        }

        ManagedAimpCore::~ManagedAimpCore() {
            if (_optionsFrame != nullptr) {
                _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = nullptr;
            }

            if (_albumArtCatalogExtension != nullptr) {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = nullptr;
            }

            if (_albumArtProviderExtension != nullptr) {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = nullptr;
            }

            if (_albumArtProviderExtension3 != nullptr) {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider3::Base*>(_albumArtProviderExtension3));
                _albumArtProviderExtension3->Release();
                _albumArtProviderExtension3 = nullptr;
            }

            if (_embeddedVisualization != nullptr) {
                _core->UnregisterExtension(_embeddedVisualization);
                _embeddedVisualization->Release();
                _embeddedVisualization = nullptr;
            }

            if (_customVisualization != nullptr) {
                _core->UnregisterExtension(_customVisualization);
                _customVisualization->Release();
                _customVisualization = nullptr;
            }

            if (_playlistManagerListener != nullptr) {
                _core->UnregisterExtension(this->_playlistManagerListener);
                _playlistManagerListener->Release();
                _playlistManagerListener = nullptr;
            }

            if (_musicLibraryDataStorage != nullptr) {
                _core->UnregisterExtension(this->_musicLibraryDataStorage);
                _musicLibraryDataStorage->Release();
                _musicLibraryDataStorage = nullptr;
            }

            if (_extensionPlaylistPreimageFactory != nullptr) {
                _core->UnregisterExtension(
                    static_cast<InternalAimpExtensionPlaylistPreimageFactory::Base*>(_extensionPlaylistPreimageFactory
                    ));
                _extensionPlaylistPreimageFactory->Release();
                _extensionPlaylistPreimageFactory = nullptr;
            }

            if (_extensionLyricsProvider != nullptr) {
                _core->UnregisterExtension(
                    static_cast<AimpExtensionLyricsProvider::Base*>(_extensionLyricsProvider)
                );
                _extensionLyricsProvider->Release();
                _extensionLyricsProvider = nullptr;
            }

            if (_extensionPlaybackQueue != nullptr) {
                _core->UnregisterExtension(static_cast<AimpExtensionPlaybackQueue::Base*>(_extensionPlaybackQueue)
                );
                _extensionPlaybackQueue->Release();
                delete _extensionPlaybackQueue;
            }

            if (_extensionPlaybackQueue2 != nullptr) {
                _core->UnregisterExtension(static_cast<AimpExtensionPlaybackQueue2::Base2*>(_extensionPlaybackQueue2)
                );
                _extensionPlaybackQueue2->Release();
                delete _extensionPlaybackQueue2;
            }

            if (_extensionPlayerHook != nullptr) {
                _core->UnregisterExtension(static_cast<AimpExtensionPlayerHook::Base*>(_extensionPlayerHook));
                _extensionPlayerHook->Release();
                _extensionPlayerHook = nullptr;
            }

            if (_extensionWaveFormProvider != nullptr) {
                _core->UnregisterExtension(_extensionWaveFormProvider);
                _extensionWaveFormProvider->Release();
                delete _extensionWaveFormProvider;
            }

            UnregisterFileManagerExtensions();

            if (_extensionTagsProvider != nullptr) {
                _core->UnregisterExtension(static_cast<InternalExtensionTagsProvider::Base*>(_extensionTagsProvider));
                _extensionTagsProvider->Release();
                _extensionTagsProvider = nullptr;
            }

            _core->Release();
            _core = nullptr;
        }

        /// <summary>
        /// Gets the specified AIMP path.
        /// </summary>
        /// <param name="pathType">Path type.</param>
        /// <param name="pathResult"></param>
        /// <returns></returns>
        ActionResultType ManagedAimpCore::GetPath(MessageDispatcher::AimpCorePathType pathType,
                                                  String^% pathResult) {
            IAIMPString* res;
            _core->GetPath((int)pathType, &res);
            pathResult = AimpConverter::ToManagedString(res);
            res->Release();
            return ActionResultType::OK;
        }

        /// <summary>
        /// Registers the extension.
        /// </summary>
        /// <param name="extensionId">The extension identifier.</param>
        /// <param name="extension">The extension.</param>
        /// <returns>HRESULT.</returns>
        HRESULT ManagedAimpCore::RegisterExtension(GUID extensionId, AIMP::IAimpExtension^ extension) {
            auto optionsFrameExtension = dynamic_cast<Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr) {
                if (_optionsFrame != nullptr) {
                    return E_FAIL;
                }

                OptionsDialogFrameExtension* odfp = new OptionsDialogFrameExtension(this->GetAimpCore(), optionsFrameExtension);
                _optionsFrame = odfp;
                return _core->RegisterExtension(IID_IAIMPServiceOptionsDialog, static_cast<OptionsDialogFrameExtension::Base*>(odfp));
            }

            IAimpExtensionAlbumArtCatalog^ albumArtCatalogExtension = dynamic_cast<IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr) {
                if (_albumArtCatalogExtension != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionAlbumArtCatalog* cat = new AimpExtensionAlbumArtCatalog(
                    this->GetAimpCore(), albumArtCatalogExtension);
                _albumArtCatalogExtension = cat;
                return _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtCatalog::Base*>(cat));
            }

            IAimpExtensionAlbumArtProvider^ albumArtProviderExtension = dynamic_cast<IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr) {
                if (_albumArtProviderExtension != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionAlbumArtProvider* ext = new AimpExtensionAlbumArtProvider(albumArtProviderExtension);
                _albumArtProviderExtension = ext;
                return _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtProvider::Base*>(ext));
            }

            IAimpExtensionAlbumArtProvider3^ albumArtProviderExtension3 = dynamic_cast<IAimpExtensionAlbumArtProvider3^>(extension);
            if (albumArtProviderExtension3 != nullptr) {
                if (_albumArtProviderExtension3 != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionAlbumArtProvider3* ext = new AimpExtensionAlbumArtProvider3(albumArtProviderExtension3);
                _albumArtProviderExtension3 = ext;
                return _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtProvider3::Base*>(ext));
            }

            const auto embeddedVisualization = dynamic_cast<Visuals::IAimpExtensionEmbeddedVisualization^>(extension);
            if (embeddedVisualization != nullptr) {
                if (_embeddedVisualization != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionEmbeddedVisualization* ext = new AimpExtensionEmbeddedVisualization(
                    this->GetAimpCore(), embeddedVisualization);
                _embeddedVisualization = ext;
                return _core->RegisterExtension(IID_IAIMPServiceVisualizations, ext);
            }

            const auto customVisualization = dynamic_cast<Visuals::IAimpExtensionCustomVisualization^>(extension);
            if (customVisualization != nullptr) {
                if (_customVisualization != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionCustomVisualization* ext = new AimpExtensionCustomVisualization(
                    this->GetAimpCore(), customVisualization);
                _customVisualization = ext;
                return _core->RegisterExtension(IID_IAIMPServiceVisualizations, ext);
            }

            auto dataStorageExtension = dynamic_cast<MusicLibrary::Extension::IAimpExtensionDataStorage^>(extension);
            if (dataStorageExtension != nullptr) {
                if (_musicLibraryDataStorage != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionDataStorage* ext = new AimpExtensionDataStorage(_core, dataStorageExtension);
                _musicLibraryDataStorage = ext;
                return _core->RegisterExtension(IID_IAIMPServiceMusicLibrary, ext);
            }


            #pragma region PlaylistExtension
            IAimpExtensionPlaylistPreimageFactory^ extensionPlaylistPreImageFactory = dynamic_cast<
                IAimpExtensionPlaylistPreimageFactory^>(extension);
            if (extensionPlaylistPreImageFactory != nullptr) {
                if (_extensionPlaylistPreimageFactory != nullptr) {
                    return E_FAIL;
                }

                InternalAimpExtensionPlaylistPreimageFactory* ext = new InternalAimpExtensionPlaylistPreimageFactory(
                    extensionPlaylistPreImageFactory);
                return _core->RegisterExtension(IID_IAIMPServicePlaylistManager, static_cast<InternalAimpExtensionPlaylistPreimageFactory::Base*>(ext));
            }

            IAimpExtensionPlaylistManagerListener^ playlistManagerListener = dynamic_cast<
                IAimpExtensionPlaylistManagerListener^>(extension);
            if (playlistManagerListener != nullptr) {
                if (_playlistManagerListener != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionPlaylistManagerListener* ext = new AimpExtensionPlaylistManagerListener((IAimpExtensionPlaylistManagerListener^)extension);
                _playlistManagerListener = ext;
                return _core->RegisterExtension(IID_IAIMPServicePlaylistManager, _playlistManagerListener);
            }
            #pragma endregion PlaylistExtension

            IAimpExtensionLyricsProvider^ lyricsProviderExtension = dynamic_cast<
                IAimpExtensionLyricsProvider^>(extension);
            if (lyricsProviderExtension != nullptr) {
                if (_extensionLyricsProvider != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionLyricsProvider* ext = new AimpExtensionLyricsProvider(lyricsProviderExtension);
                _extensionLyricsProvider = ext;
                return _core->RegisterExtension(IID_IAIMPExtensionLyricsProvider, static_cast<AimpExtensionLyricsProvider::Base*>(ext));
            }

            IAimpExtensionPlaybackQueue^ extensionPlaybackQueue = dynamic_cast<IAimpExtensionPlaybackQueue^>(extension);
            if (extensionPlaybackQueue != nullptr) {
                if (_extensionPlaybackQueue != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionPlaybackQueue* ext = new AimpExtensionPlaybackQueue(extensionPlaybackQueue);
                _extensionPlaybackQueue = ext;
                return _core->RegisterExtension(IID_IAIMPServicePlaybackQueue, static_cast<AimpExtensionPlaybackQueue::Base*>(ext)
                );
            }

            IAimpExtensionPlaybackQueue2^ extensionPlaybackQueue2 = dynamic_cast<IAimpExtensionPlaybackQueue2^>(extension);
            if (extensionPlaybackQueue2 != nullptr) {
                if (_extensionPlaybackQueue != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionPlaybackQueue2* ext = new AimpExtensionPlaybackQueue2(extensionPlaybackQueue2);
                _extensionPlaybackQueue2 = ext;
                return _core->RegisterExtension(IID_IAIMPServicePlaybackQueue2, static_cast<AimpExtensionPlaybackQueue2::Base2*>(ext)
                );
            }

            auto extensionPlayerHook = dynamic_cast<IAimpExtensionPlayerHook^>(extension);
            if (extensionPlayerHook != nullptr) {
                if (_extensionPlayerHook != nullptr) {
                    return E_FAIL;
                }

                AimpExtensionPlayerHook* ext = new AimpExtensionPlayerHook(extensionPlayerHook);
                _extensionPlayerHook = ext;
                return _core->RegisterExtension(IID_IAIMPServicePlayer, static_cast<AimpExtensionPlayerHook::Base*>(ext));
            }

            auto extensionTagsProvider = dynamic_cast<TagEditor::Extensions::IAimpExtensionTagsProvider^>(extension);
            if (extensionTagsProvider != nullptr) {
                if (_extensionTagsProvider != nullptr) {
                    return E_FAIL;
                }

                InternalExtensionTagsProvider* ext = new InternalExtensionTagsProvider(extensionTagsProvider);
                _extensionTagsProvider = ext;
                return _core->RegisterExtension(IID_IAIMPServiceFindTagsOnline, static_cast<InternalExtensionTagsProvider::Base*>(ext));
            }

            IAimpExtensionWaveFormProvider^ waveFormProvider = dynamic_cast<IAimpExtensionWaveFormProvider^>(extension);
            if (waveFormProvider != nullptr) {
                if (_extensionWaveFormProvider != nullptr) {
                    return E_FAIL;
                }

                const auto ext = new InternalAimpExtensionWaveFormProvider(waveFormProvider);
                _extensionWaveFormProvider = ext;
                return _core->RegisterExtension(IID_IAIMPExtensionWaveformProvider, ext);
            }

            HRESULT result = RegisterFileManagerExtensions(extension);

            return result;
        }

        HRESULT ManagedAimpCore::UnregisterExtension(IAimpExtension^ extension) {
            const auto optionsFrameExtension = dynamic_cast<Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr) {
                HRESULT r = _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = nullptr;
                return r;
            }

            const auto albumArtCatalogExtension = dynamic_cast<IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr) {
                HRESULT r = _core->UnregisterExtension(
                    static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = nullptr;
                return r;
            }

            const auto albumArtProviderExtension = dynamic_cast<IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr) {
                HRESULT r = _core->UnregisterExtension(
                    static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = nullptr;
                return r;
            }

            const auto embeddedVisualization = dynamic_cast<Visuals::IAimpExtensionEmbeddedVisualization^>(extension);
            if (embeddedVisualization != nullptr) {
                HRESULT r = _core->UnregisterExtension(_embeddedVisualization);
                _embeddedVisualization->Release();
                _embeddedVisualization = nullptr;
                return r;
            }

            Visuals::IAimpExtensionCustomVisualization^ customVisualization = dynamic_cast<Visuals::IAimpExtensionCustomVisualization^>(extension);
            if (customVisualization != nullptr) {
                HRESULT r = _core->UnregisterExtension(_customVisualization);
                _customVisualization->Release();
                _customVisualization = nullptr;
                return r;
            }

            const auto playlistManagerListener = dynamic_cast<IAimpExtensionPlaylistManagerListener^>(extension);
            if (playlistManagerListener != nullptr) {
                HRESULT r = _core->UnregisterExtension(_playlistManagerListener);
                _playlistManagerListener->Release();
                _playlistManagerListener = nullptr;
                return r;
            }

            const auto extensionPlaylistPreImageFactory = dynamic_cast<IAimpExtensionPlaylistPreimageFactory^>(extension);
            if (extensionPlaylistPreImageFactory != nullptr) {
                HRESULT r = _core->UnregisterExtension(
                    static_cast<InternalAimpExtensionPlaylistPreimageFactory::Base*>(_extensionPlaylistPreimageFactory
                    ));
                _extensionPlaylistPreimageFactory->Release();
                _extensionPlaylistPreimageFactory = nullptr;
                return r;
            }

            const auto extensionLyricsProvider = dynamic_cast<IAimpExtensionLyricsProvider^>(extension);
            if (extensionLyricsProvider != nullptr) {
                HRESULT r = _core->UnregisterExtension(
                    static_cast<AimpExtensionLyricsProvider::Base*>(_extensionLyricsProvider));
                _extensionLyricsProvider->Release();
                _extensionLyricsProvider = nullptr;
                return r;
            }

            const auto extensionPlaybackQueue = dynamic_cast<IAimpExtensionPlaybackQueue^>(extension);
            if (extensionPlaybackQueue != nullptr) {
                HRESULT r = _core->UnregisterExtension(static_cast<AimpExtensionPlaybackQueue::Base*>(_extensionPlaybackQueue));
                _extensionPlaybackQueue->Release();
                _extensionPlaybackQueue = nullptr;
                return r;
            }

            const auto extensionPlaybackQueue2 = dynamic_cast<IAimpExtensionPlaybackQueue2^>(extension);
            if (extensionPlaybackQueue2 != nullptr) {
                HRESULT r = _core->UnregisterExtension(static_cast<AimpExtensionPlaybackQueue2::Base2*>(_extensionPlaybackQueue2));
                _extensionPlaybackQueue2->Release();
                _extensionPlaybackQueue2 = nullptr;
                return r;
            }

            const auto extensionPlayerHook = dynamic_cast<IAimpExtensionPlayerHook^>(extension);
            if (extensionPlayerHook != nullptr) {
                HRESULT r = _core->UnregisterExtension(
                    static_cast<AimpExtensionPlayerHook::Base*>(_extensionPlayerHook));
                _extensionPlayerHook->Release();
                _extensionPlayerHook = nullptr;
                return r;
            }

            FileManager::Extensions::IAimpExtensionFileExpander^ extensionFileExpander = dynamic_cast<FileManager::Extensions::IAimpExtensionFileExpander^>(extension);
            if (extensionFileExpander != nullptr) {
                HRESULT r = _core->UnregisterExtension(
                    static_cast<InternalAimpExtensionFileExpander::Base*>(_extensionFileExpander));
                _extensionFileExpander->Release();
                _extensionFileExpander = nullptr;
                return r;
            }

            auto extensionTagsProvider = dynamic_cast<TagEditor::Extensions::IAimpExtensionTagsProvider^>(extension);
            if (extensionTagsProvider != nullptr) {
                HRESULT r = _core->UnregisterExtension(static_cast<InternalExtensionTagsProvider::Base*>(_extensionTagsProvider));
                _extensionTagsProvider->Release();
                _extensionTagsProvider = nullptr;
                return r;
            }

            auto extensionWaveFormProvider = dynamic_cast<IAimpExtensionWaveFormProvider^>(extension);
            if (extensionWaveFormProvider != nullptr) {
                HRESULT r = _core->UnregisterExtension(_extensionWaveFormProvider);
                _extensionWaveFormProvider->Release();
                _extensionWaveFormProvider = nullptr;
                return r;
            }

            return E_NOTIMPL;
        }

        HRESULT ManagedAimpCore::UnregisterExtension(IUnknown* extension) {
            return _core->UnregisterExtension(extension);
        }


        //******** IAimpExtensionPlaylistManagerListenerExecutor ********

        void ManagedAimpCore::OnPlaylistActivated(IAIMPPlaylist* playlist) {
        }

        void ManagedAimpCore::OnPlaylistAdded(IAIMPPlaylist* playlist) {
        }

        void ManagedAimpCore::OnPlaylistRemoved(IAIMPPlaylist* playlist) {
        }

        //******** IAimpExtensionPlaylistManagerListenerExecutor ********

        /// <summary>
        /// Gets the service.
        /// </summary>
        /// <param name="iid">The iid.</param>
        /// <param name="service">The service.</param>
        /// <returns></returns>
        HRESULT ManagedAimpCore::GetService(REFIID iid, void** service) {
            //return _core->QueryInterface(iid, service);

            IUnknown* _service = nullptr;
            HRESULT result = _core->QueryInterface(iid, reinterpret_cast<void**>(&_service));
            if (result == S_OK) {
                *service = _service;
            }

            return result;
        }

        IUnknown* ManagedAimpCore::QueryInterface(REFIID iid) {
            IUnknown* service = nullptr;
            HRESULT result = _core->QueryInterface(iid, reinterpret_cast<void**>(&service));
            if (result != S_OK) {
                return nullptr;
            }

            return service;
        }

        /// <summary>
        /// Creates the action event.
        /// </summary>
        /// <returns></returns>
        IAIMPActionEvent* ManagedAimpCore::CreateActionEvent() {
            IAIMPActionEvent* actionEvent = nullptr;
            _core->CreateObject(IID_IAIMPActionEvent, reinterpret_cast<void**>(&actionEvent));
            return actionEvent;
        }

        HRESULT ManagedAimpCore::SendMessage(MessageDispatcher::AimpCoreMessageType message, int value, Object^ obj) {
            HRESULT r;

            if (message == MessageDispatcher::AimpCoreMessageType::CmdShowNotification) {
                r = ShowNotification(value == 0, static_cast<String^>(obj));
            }
            else {
                r = _messageDispatcher->Send(DWORD(message), value, static_cast<void*>(&obj));
            }

            return r;
        }

        HRESULT ManagedAimpCore::ShowNotification(bool autoHide, String^ notification) {
            IAIMPString* str = AimpConverter::ToAimpString(notification);
            HRESULT r = _messageDispatcher->Send(
                DWORD(MessageDispatcher::AimpCoreMessageType::CmdShowNotification), autoHide ? 0 : 1,
                str->GetData());
            str->Release();
            return r;
        }

        /// <summary>
        /// Creates the new AIMP stream.
        /// </summary>
        ActionResultType ManagedAimpCore::CreateStream(IAIMPStream** stream) {
            IAIMPStream* s = nullptr;
            ActionResultType result = Utils::CheckResult(
                _core->CreateObject(IID_IAIMPMemoryStream, reinterpret_cast<void**>(&s)));
            *stream = s;
            return result;
        }

        AIMP::SDK::ActionResultType ManagedAimpCore::CreateAction(IAIMPAction** action) {
            IAIMPAction* a = nullptr;
            ActionResultType result = Utils::CheckResult(
                _core->CreateObject(IID_IAIMPAction, reinterpret_cast<void**>(&a)));
            *action = a;
            return result;
        }

        IAIMPCore* ManagedAimpCore::GetAimpCore() {
            return _core;
        }

        HRESULT ManagedAimpCore::CreateMenuItem(IAIMPMenuItem** item) {
            IAIMPMenuItem* i;
            HRESULT r = _core->CreateObject(IID_IAIMPMenuItem, reinterpret_cast<void**>(&i));
            *item = i;
            return r;
        }

        OptionsDialogFrameExtension* ManagedAimpCore::GetOptionsFrame() {
            return _optionsFrame;
        }

        HRESULT ManagedAimpCore::RegisterFileManagerExtensions(IAimpExtension^ extension) {
            FileManager::Extensions::IAimpExtensionFileInfoProvider^ fileInfoProviderExtension = dynamic_cast<
                FileManager::Extensions::IAimpExtensionFileInfoProvider^>(extension);
            if (fileInfoProviderExtension != nullptr) {
                if (_fileInfoExtensionProvider != nullptr) {
                    return E_FAIL;
                }

                InternalAimpExtensionFileInfoProvider* ext = new InternalAimpExtensionFileInfoProvider(
                    fileInfoProviderExtension);
                _fileInfoExtensionProvider = ext;
                return _core->RegisterExtension(IID_IAIMPServiceFileInfo,
                    static_cast<InternalAimpExtensionFileInfoProvider::Base*>(ext));
            }

            FileManager::Extensions::IAimpExtensionFileSystem^ extensionFileSystem = dynamic_cast<FileManager::Extensions::IAimpExtensionFileSystem^>(extension);
            if (extensionFileSystem != nullptr) {
                if (_extensionFileSystem != nullptr) {
                    return E_FAIL;
                }

                InternalAimpExtensionFileSystem* ext = new InternalAimpExtensionFileSystem(extensionFileSystem, _core);
                _extensionFileSystem = ext;
                return _core->RegisterExtension(IID_IAIMPServiceFileSystems,
                    static_cast<IAIMPExtensionFileSystem*>(ext));
            }

            FileManager::Extensions::IAimpExtensionFileFormat^ extensionFileFormat = dynamic_cast<FileManager::Extensions::IAimpExtensionFileFormat^>(extension);
            if (extensionFileFormat != nullptr) {
                if (_extensionFileFormat != nullptr) {
                    return E_FAIL;
                }

                const auto ext = new InternalAimpExtensionFileFormat(extensionFileFormat);
                _extensionFileFormat = ext;
                return _core->RegisterExtension(IID_IAIMPExtensionFileFormat, static_cast<IAIMPExtensionFileFormat*>(ext));
            }

            FileManager::Extensions::IAimpExtensionFileExpander^ extensionFileExpander = dynamic_cast<FileManager::Extensions::IAimpExtensionFileExpander^>(extension);
            if (extensionFileExpander != nullptr) {
                if (_extensionFileExpander != nullptr) {
                    return E_FAIL;
                }

                const auto ext = new InternalAimpExtensionFileExpander(extensionFileExpander);
                _extensionFileExpander = ext;
                return _core->RegisterExtension(IID_IAIMPExtensionFileExpander, static_cast<IAIMPExtensionFileExpander*>(ext));
            }

            MusicLibrary::Extension::IAimpAlbumArtProvider2^ aimpAlbumArtProvider2 = dynamic_cast<MusicLibrary::Extension::IAimpAlbumArtProvider2^>(extension);
            if (aimpAlbumArtProvider2 != nullptr) {
                if (_extensionMLAlbumArtProvider != nullptr) {
                    return E_FAIL;
                }

                const auto ext = new InternalAimpAlbumArtProvider2(aimpAlbumArtProvider2);
                _extensionMLAlbumArtProvider = ext;
                return _core->RegisterExtension(IID_IAIMPExtensionFileExpander, ext);
            }

            return E_UNEXPECTED;
        }

        void ManagedAimpCore::UnregisterFileManagerExtensions() {
            if (_extensionFileSystem != nullptr) {
                _core->UnregisterExtension(_extensionFileSystem);
                _extensionFileSystem->Release();
                _extensionFileSystem = nullptr;
            }

            if (_fileInfoExtensionProvider != nullptr) {
                _core->UnregisterExtension(static_cast<InternalAimpExtensionFileInfoProvider::Base*>(_fileInfoExtensionProvider));
                _fileInfoExtensionProvider->Release();
                _fileInfoExtensionProvider = nullptr;
            }

            if (_extensionFileFormat != nullptr) {
                _core->UnregisterExtension(static_cast<InternalAimpExtensionFileFormat::Base*>(_extensionFileFormat));
                _extensionFileFormat->Release();
                delete _extensionFileFormat;
            }

            if (_extensionFileExpander != nullptr) {
                _core->UnregisterExtension(static_cast<InternalAimpExtensionFileExpander::Base*>(_extensionFileExpander));
                _extensionFileExpander->Release();
                delete _extensionFileExpander;
            }
        }
    }
}
