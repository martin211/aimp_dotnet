// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "ManagedAimpCore.h"
#include "IUnknownInterfaceImpl.h"
#include "PlayList\AimpPlayList.h"
#include "AimpSdk.h"
#include "SDK\Options\OptionsDialogFrameExtension.h"
#include "SDK\AlbumArt\AimpExtensionAlbumArtCatalog.h"
#include "SDK\PlayList\AimpExtensionPlaylistManagerListener.h"


namespace AIMP
{
    /// <summary>
    /// 
    /// </summary>
    namespace SDK
    {
        using namespace System;
        using namespace System::Runtime::InteropServices;

        class AIMPMessageHook : public IUnknownInterfaceImpl<IAIMPMessageHook>
        {
        public:
            explicit AIMPMessageHook(gcroot<ManagedAimpCore^> managedCore) : _managedCore(managedCore)
            {}

            virtual void WINAPI CoreMessage(DWORD AMessage, int AParam1, void *AParam2, HRESULT *AResult) 
            {
                _managedCore->OnCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)AMessage, AParam1);
                _managedCore->OnInternalCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)AMessage, AParam1);
            }

        private:
            gcroot<ManagedAimpCore^> _managedCore;
        };

        class AimpExtensionPlayerHook : public IUnknownInterfaceImpl<IAIMPExtensionPlayerHook>
        {
        public:
            typedef IUnknownInterfaceImpl<IAIMPExtensionPlayerHook> Base;

            explicit AimpExtensionPlayerHook(gcroot<ManagedAimpCore^> managedCore) : _managedCore(managedCore)
            {}

            virtual HRESULT WINAPI OnCheckURL(IAIMPString* URL, BOOL *Handled)
            {
                String ^url = AimpConverter::ToManagedString(URL);
                bool handled = _managedCore->OnCheckUrl(*&url);

                if (handled)
                {
                    // TODO: Optimize it
                    *Handled = 1;
                    IAIMPString *str = AimpConverter::ToAimpString(url);
                    URL->SetData(str->GetData(), str->GetLength());
                    str->Release();
                    str = nullptr;
                }
                else
                    *Handled = 0;

                return S_OK;
            }

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj)
            {
                if (!ppvObj)
                {
                    return E_POINTER;
                }

                if (riid == IID_IAIMPExtensionPlayerHook) {
                    *ppvObj = this;
                    AddRef();
                    return S_OK;
                }

                return E_NOINTERFACE;
            }

            virtual ULONG WINAPI AddRef(void)
            {
                return Base::AddRef();
            }

            virtual ULONG WINAPI Release(void)
            {
                return Base::Release();
            }

        private:
            gcroot<ManagedAimpCore^> _managedCore;
        };

        ManagedAimpCore::ManagedAimpCore(IAIMPCore* core)
        {
            _core = core;
            AimpExtensionPlayerHook *playerHook = new AimpExtensionPlayerHook(this);
            core->RegisterExtension(IID_IAIMPServicePlayer, playerHook);
        }

        ManagedAimpCore::~ManagedAimpCore()
        {
            System::Diagnostics::Debug::WriteLine("Dispose ManagedAimpCore");
            
            if (_optionsFrame != nullptr)
            {
                _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = nullptr;
            }

            if (_albumArtCatalogExtension != nullptr)
            {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = nullptr;
            }

            if (_albumArtProviderExtension != nullptr)
            {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = nullptr;
            }

            if (_embeddedVisualization != nullptr)
            {
                _core->UnregisterExtension(_embeddedVisualization);
                _embeddedVisualization->Release();
                _embeddedVisualization = nullptr;
            }

            if (_customVisualization != nullptr)
            {
                _core->UnregisterExtension(_customVisualization);
                _customVisualization->Release();
                _customVisualization = nullptr;
            }

            if (_playlistManagerListener != nullptr)
            {
                _core->UnregisterExtension(this->_playlistManagerListener);
                _playlistManagerListener->Release();
                _playlistManagerListener = nullptr;
            }

            if (_musicLibraryDataStorage != nullptr)
            {
                _core->UnregisterExtension(this->_musicLibraryDataStorage);
                _musicLibraryDataStorage->Release();
                _musicLibraryDataStorage = nullptr;
            }

            if (_fileInfoExtensionProvider != nullptr)
            {
                _core->UnregisterExtension(static_cast<InternalAimpExtensionFileInfoProvider::Base*>(_fileInfoExtensionProvider));
                _fileInfoExtensionProvider->Release();
                _fileInfoExtensionProvider = nullptr;
            }

            if (_extensionFileSystem != nullptr)
            {
                _core->UnregisterExtension(_extensionFileSystem);
                _extensionFileSystem->Release();
                _extensionFileSystem = nullptr;
            }

            if (_extensionPlaylistPreimageFactory != nullptr)
            {
                _core->UnregisterExtension(static_cast<InternalAimpExtensionPlaylistPreimageFactory::Base*>(_extensionPlaylistPreimageFactory));
                _extensionPlaylistPreimageFactory->Release();
                _extensionPlaylistPreimageFactory = nullptr;
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
        AIMP::SDK::AimpActionResult ManagedAimpCore::GetPath(AIMP::SDK::AimpMessages::AimpCorePathType pathType, String ^%pathResult)
        {
            IAIMPString* res;
            _core->GetPath((int)pathType, &res);
            pathResult = AimpConverter::ToManagedString(res);
            res->Release();
            return AIMP::SDK::AimpActionResult::OK;
        }

        /// <summary>
        /// Registers the extension.
        /// </summary>
        /// <para>
        /// Allowed only one the instance of each extension.
        /// </para>
        /// <param name="extensionId">The extension identifier.</param>
        /// <param name="extension">The extension.</param>
        /// <returns></returns>
        HRESULT ManagedAimpCore::RegisterExtension(GUID extensionId, AIMP::IAimpExtension^ extension)
        {
            AIMP::SDK::Options::IAimpOptionsDialogFrame^ optionsFrameExtension = dynamic_cast<AIMP::SDK::Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr)
            {
                if (_optionsFrame != nullptr)
                {
                    return E_FAIL;
                }

                OptionsDialogFrameExtension* odfp = new OptionsDialogFrameExtension(this->GetAimpCore(), optionsFrameExtension);
                _optionsFrame = odfp;
                return _core->RegisterExtension(IID_IAIMPServiceOptionsDialog, static_cast<OptionsDialogFrameExtension::Base*>(odfp));
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^ albumArtCatalogExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr)
            {
                if (_albumArtCatalogExtension != nullptr)
                {
                    return E_FAIL;
                }

                AimpExtensionAlbumArtCatalog *cat = new AimpExtensionAlbumArtCatalog(this->GetAimpCore(), albumArtCatalogExtension);
                _albumArtCatalogExtension = cat;
                return _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtCatalog::Base*>(cat));
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^ albumArtProviderExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr)
            {
                if (_albumArtProviderExtension != nullptr)
                {
                    return E_FAIL;
                }

                AimpExtensionAlbumArtProvider *ext = new AimpExtensionAlbumArtProvider(this->GetAimpCore(), albumArtProviderExtension);
                _albumArtProviderExtension = ext;
                return _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtProvider::Base*>(ext));
            }

            AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization ^embeddedVisualization = dynamic_cast<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^>(extension);
            if (embeddedVisualization != nullptr)
            {
                if (_embeddedVisualization != nullptr)
                {
                    return E_FAIL;
                }

                AimpExtensionEmbeddedVisualization *ext = new AimpExtensionEmbeddedVisualization(this->GetAimpCore(), embeddedVisualization);
                _embeddedVisualization = ext;
                return _core->RegisterExtension(IID_IAIMPServiceVisualizations, ext);
            }

            AIMP::SDK::Visuals::IAimpExtensionCustomVisualization ^customVisualization = dynamic_cast<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^>(extension);
            if (customVisualization != nullptr)
            {
                if (_customVisualization != nullptr)
                {
                    return E_FAIL;
                }

                AimpExtensionCustomVisualization *ext = new AimpExtensionCustomVisualization(this->GetAimpCore(), customVisualization);
                _customVisualization = ext;
                return _core->RegisterExtension(IID_IAIMPServiceVisualizations, ext);
            }

            AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage ^dataStorageExtension = dynamic_cast<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^>(extension);
            if (dataStorageExtension != nullptr)
            {
                if (_musicLibraryDataStorage != nullptr)
                {
                    return E_FAIL;
                }

                AimpExtensionDataStorage *ext = new AimpExtensionDataStorage(_core, dataStorageExtension);
                _musicLibraryDataStorage = ext;
                return _core->RegisterExtension(IID_IAIMPServiceMusicLibrary, ext);
            }

            AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider ^fileInfoProviderExtension = dynamic_cast<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileInfoProvider^>(extension);
            if (fileInfoProviderExtension != nullptr)
            {
                if (_fileInfoExtensionProvider != nullptr)
                {
                    return E_FAIL;
                }

                InternalAimpExtensionFileInfoProvider *ext = new InternalAimpExtensionFileInfoProvider(fileInfoProviderExtension);
                _fileInfoExtensionProvider = ext;
                return _core->RegisterExtension(IID_IAIMPServiceFileInfo, static_cast<InternalAimpExtensionFileInfoProvider::Base*>(ext));
            }

            AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem ^extensionFileSystem = dynamic_cast<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^>(extension);
            if (extensionFileSystem != nullptr)
            {
                if (_extensionFileSystem != nullptr)
                {
                    return E_FAIL;
                }

                InternalAimpExtensionFileSystem *ext = new InternalAimpExtensionFileSystem(extensionFileSystem, _core);
                return _core->RegisterExtension(IID_IAIMPServiceFileSystems, (IAIMPExtensionFileSystem*)ext);
            }

#pragma region PlaylistExtension
            AIMP::SDK::Playlist::IAimpExtensionPlaylistPreimageFactory^ extensionPlaylistPreImageFactory = dynamic_cast<AIMP::SDK::Playlist::IAimpExtensionPlaylistPreimageFactory^>(extension);
            if (extensionPlaylistPreImageFactory != nullptr)
            {
                if (_extensionPlaylistPreimageFactory != nullptr)
                {
                    return E_FAIL;
                }

                InternalAimpExtensionPlaylistPreimageFactory* ext = new InternalAimpExtensionPlaylistPreimageFactory(extensionPlaylistPreImageFactory);
                return _core->RegisterExtension(IID_IAIMPServicePlaylistManager, static_cast<InternalAimpExtensionPlaylistPreimageFactory::Base*>(ext));
            }

            AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener ^playlistManagerListener = dynamic_cast<AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener^>(extension);
            if (playlistManagerListener != nullptr)
            {
                if (_playlistManagerListener != nullptr)
                {
                    return E_FAIL;
                }

                AimpExtensionPlaylistManagerListener *ext = new AimpExtensionPlaylistManagerListener((IAimpExtensionPlaylistManagerListener^)extension);
                _playlistManagerListener = ext;
                return _core->RegisterExtension(IID_IAIMPServicePlaylistManager, _playlistManagerListener);
            }
#pragma endregion PlaylistExtension

            return E_UNEXPECTED;
        }

        HRESULT ManagedAimpCore::UnregisterExtension(IAimpExtension^ extension)
        {
            AIMP::SDK::Options::IAimpOptionsDialogFrame^ optionsFrameExtension = dynamic_cast<AIMP::SDK::Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = nullptr;
                return r;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^ albumArtCatalogExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = nullptr;
                return r;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^ albumArtProviderExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = nullptr;
                return r;
            }

            AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization ^embeddedVisualization = dynamic_cast<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^>(extension);
            if (embeddedVisualization != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(_embeddedVisualization);
                _embeddedVisualization->Release();
                _embeddedVisualization = nullptr;
                return r;
            }

            AIMP::SDK::Visuals::IAimpExtensionCustomVisualization ^customVisualization = dynamic_cast<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^>(extension);
            if (customVisualization != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(_customVisualization);
                _customVisualization->Release();
                _customVisualization = nullptr;
                return r;
            }

            AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener ^playlistManagerListener = dynamic_cast<AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener^>(extension);
            if (customVisualization != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(_playlistManagerListener);
                _playlistManagerListener->Release();
                _playlistManagerListener = nullptr;
                return r;
            }

            auto extensionPlaylistPreImageFactory = dynamic_cast<IAimpExtensionPlaylistPreimageFactory^>(extension);
            if (extensionPlaylistPreImageFactory != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<InternalAimpExtensionPlaylistPreimageFactory::Base*>(_extensionPlaylistPreimageFactory));
                _extensionPlaylistPreimageFactory->Release();
                _extensionPlaylistPreimageFactory = nullptr;
                return r;
            }

            return E_NOTIMPL;
        }

        HRESULT ManagedAimpCore::UnregisterExtension(IUnknown* extension)
        {
            return _core->UnregisterExtension(extension);
        }

        /// <summary>
        /// Called when [core message].
        /// </summary>
        /// <param name="param1">The param1.</param>
        /// <param name="param2">The param2.</param>
        void ManagedAimpCore::OnCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
        {
            CoreMessage(param1, param2);
        }

        void ManagedAimpCore::OnInternalCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
        {
            InternalCoreMessage(param1, param2);
        }


        //******** IAimpExtensionPlaylistManagerListenerExecutor ********

        void ManagedAimpCore::OnPlaylistActivated(IAIMPPlaylist *playlist)
        {

        }

        void ManagedAimpCore::OnPlaylistAdded(IAIMPPlaylist *playlist)
        {

        }

        void ManagedAimpCore::OnPlaylistRemoved(IAIMPPlaylist *playlist)
        {

        }

        //******** IAimpExtensionPlaylistManagerListenerExecutor ********


        bool ManagedAimpCore::OnCheckUrl(String^ %url)
        {
            return this->CheckUrl(url);
        }

        /// <summary>
        /// Core message event proxy.
        /// </summary>
        /// <param name="This">The this.</param>
        /// <param name="param">The parameter.</param>
        /// <param name="param1">The param1.</param>
        void CoreMessageEventProxy(gcroot<ManagedAimpCore^> This, DWORD param, int param1)
        {
            This->OnCoreMessage(AimpMessages::AimpCoreMessageType(param), param1);
        }

        /// <summary>
        /// Gets the service.
        /// </summary>
        /// <param name="iid">The iid.</param>
        /// <param name="service">The service.</param>
        /// <returns></returns>
        HRESULT ManagedAimpCore::GetService(REFIID iid, void** service)
        {
            //return _core->QueryInterface(iid, service);

            IUnknown* _service;
            HRESULT result = _core->QueryInterface(iid, reinterpret_cast<void**>(&_service));
            if (result == S_OK)
            {
               * service = _service;
            }

            return result;
        }

        IUnknown* ManagedAimpCore::QueryInterface(REFIID iid)
        {
            IUnknown* service;
            HRESULT result = _core->QueryInterface(iid, reinterpret_cast<void**>(&service));
            if (result != S_OK)
            {
                return nullptr;
            }

            return service;
        }

        /// <summary>
        /// Creates the action event.
        /// </summary>
        /// <returns></returns>
        IAIMPActionEvent* ManagedAimpCore::CreateActionEvent()
        {
            IAIMPActionEvent* actionEvent = nullptr;
            _core->CreateObject(IID_IAIMPActionEvent, reinterpret_cast<void**>(&actionEvent));
            return actionEvent;
        }

        HRESULT ManagedAimpCore::SendMessage(AimpMessages::AimpCoreMessageType message, int value, Object ^obj)
        {
            HRESULT r;

            if (message == AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION)
            {
                r = ShowNotification(value == 0, static_cast<String^>(obj));
            }
            else
            {
                r = _messageDispatcher->Send(DWORD(message), value, static_cast<void*>(&obj));
            }

            return r;
        }

        HRESULT ManagedAimpCore::ShowNotification(bool autoHide, String ^notification)
        {
            IAIMPString *str = AimpConverter::ToAimpString(notification);
            HRESULT r = _messageDispatcher->Send(DWORD(AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION), autoHide ? 0 : 1, str->GetData());
            str->Release();
            return r;
        }

        /// <summary>
        /// Creates the new AIMP stream.
        /// </summary>
        AimpActionResult ManagedAimpCore::CreateStream(IAIMPStream **stream)
        {
            IAIMPStream* s = nullptr;
            AimpActionResult result = Utils::CheckResult(_core->CreateObject(IID_IAIMPMemoryStream, reinterpret_cast<void**>(&s)));
            *stream = s;
            return result;
        }

        AIMP::SDK::AimpActionResult ManagedAimpCore::CreateAction(IAIMPAction **action)
        {
            IAIMPAction *a = nullptr;
            AimpActionResult result = Utils::CheckResult(_core->CreateObject(IID_IAIMPAction, reinterpret_cast<void**>(&a)));
            *action = a;
            return result;
        }

        IAIMPCore* ManagedAimpCore::GetAimpCore()
        {
            return _core;
        }

        HRESULT ManagedAimpCore::CreateMenuItem(IAIMPMenuItem **item)
        {
            IAIMPMenuItem *i;
            HRESULT r = _core->CreateObject(IID_IAIMPMenuItem, reinterpret_cast<void**>(&i));
            *item = i;
            return r;
        }

        OptionsDialogFrameExtension* ManagedAimpCore::GetOptionsFrame()
        {
            return _optionsFrame;
        }
    }
}
