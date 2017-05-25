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
                    str = NULL;
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
            IAIMPServiceMessageDispatcher* aimp_service_message_dispatcher;
            core->QueryInterface(IID_IAIMPServiceMessageDispatcher, reinterpret_cast<void**>(&aimp_service_message_dispatcher));
            _hook = new AIMPMessageHook(this);
            aimp_service_message_dispatcher->Hook(_hook);
            _messageDispatcher = aimp_service_message_dispatcher;

            AimpExtensionPlayerHook *playerHook = new AimpExtensionPlayerHook(this);
            core->RegisterExtension(IID_IAIMPServicePlayer, playerHook);
        }

        ManagedAimpCore::~ManagedAimpCore()
        {
            System::Diagnostics::Debug::WriteLine("Dispose ManagedAimpCore");
            _messageDispatcher->Unhook(_hook);
            _messageDispatcher->Release();
            
            if (_optionsFrame != NULL)
            {
                _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = NULL;
            }

            if (_albumArtCatalogExtension != NULL)
            {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = NULL;
            }

            if (_albumArtProviderExtension != NULL)
            {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = NULL;
            }

            if (_embeddedVisualization != NULL)
            {
                _core->UnregisterExtension(_embeddedVisualization);
                _embeddedVisualization->Release();
                _embeddedVisualization = NULL;
            }

            if (_customVisualization != NULL)
            {
                _core->UnregisterExtension(_customVisualization);
                _customVisualization->Release();
                _customVisualization = NULL;
            }

            if (_playlistManagerListener != NULL)
            {
                _core->UnregisterExtension(this->_playlistManagerListener);
                _playlistManagerListener->Release();
                _playlistManagerListener = NULL;
            }

            if (_musicLibraryDataStorage != NULL)
            {
                _core->UnregisterExtension(this->_musicLibraryDataStorage);
                _musicLibraryDataStorage->Release();
                _musicLibraryDataStorage = NULL;
            }

            if (_fileInfoExtensionProvider != NULL)
            {
                _core->UnregisterExtension(static_cast<InternalAimpExtensionFileInfoProvider::Base*>(_fileInfoExtensionProvider));
                _fileInfoExtensionProvider->Release();
                _fileInfoExtensionProvider = NULL;
            }

            if (_extensionFileSystem != NULL)
            {
                _extensionFileSystem->Release();
                _extensionFileSystem = NULL;
            }

            _core->Release();
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
            return AIMP::SDK::AimpActionResult::Ok;
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
                if (_optionsFrame != NULL)
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
                if (_albumArtCatalogExtension != NULL)
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
                if (_albumArtProviderExtension != NULL)
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
                if (_embeddedVisualization != NULL)
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
                if (_customVisualization != NULL)
                {
                    return E_FAIL;
                }

                AimpExtensionCustomVisualization *ext = new AimpExtensionCustomVisualization(this->GetAimpCore(), customVisualization);
                _customVisualization = ext;
                return _core->RegisterExtension(IID_IAIMPServiceVisualizations, ext);
            }

            AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener ^playlistManagerListener = dynamic_cast<AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener^>(extension);
            if (playlistManagerListener != nullptr)
            {
                if (_playlistManagerListener != NULL)
                {
                    return E_FAIL;
                }

                AimpExtensionPlaylistManagerListener *ext = new AimpExtensionPlaylistManagerListener((IAimpExtensionPlaylistManagerListenerExecutor^)extension);
                _playlistManagerListener = ext;
                return _core->RegisterExtension(IID_IAIMPServicePlaylistManager, _playlistManagerListener);
            }

            AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage ^dataStorageExtension = dynamic_cast<AIMP::SDK::MusicLibrary::Extension::IAimpExtensionDataStorage^>(extension);
            if (dataStorageExtension != nullptr)
            {
                if (_musicLibraryDataStorage != NULL)
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
                if (_fileInfoExtensionProvider != NULL)
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
                if (_extensionFileSystem != NULL)
                {
                    return E_FAIL;
                }

                InternalAimpExtensionFileSystem *ext = new InternalAimpExtensionFileSystem(extensionFileSystem, _core);

                return _core->RegisterExtension(IID_IAIMPServiceFileSystems, (IAIMPExtensionFileSystem*)ext);
            }

            return E_UNEXPECTED;
        }

        HRESULT ManagedAimpCore::UnregisterExtension(IAimpExtension^ extension)
        {
            AIMP::SDK::Options::IAimpOptionsDialogFrame^ optionsFrameExtension = dynamic_cast<AIMP::SDK::Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = NULL;
                return r;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^ albumArtCatalogExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = NULL;
                return r;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^ albumArtProviderExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = NULL;
                return r;
            }

            AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization ^embeddedVisualization = dynamic_cast<AIMP::SDK::Visuals::IAimpExtensionEmbeddedVisualization^>(extension);
            if (embeddedVisualization != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(_embeddedVisualization);
                _embeddedVisualization->Release();
                _embeddedVisualization = NULL;
                return r;
            }

            AIMP::SDK::Visuals::IAimpExtensionCustomVisualization ^customVisualization = dynamic_cast<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^>(extension);
            if (customVisualization != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(_customVisualization);
                _customVisualization->Release();
                _customVisualization = NULL;
                return r;
            }

            AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener ^playlistManagerListener = dynamic_cast<AIMP::SDK::Playlist::IAimpExtensionPlaylistManagerListener^>(extension);
            if (customVisualization != nullptr)
            {
                HRESULT r = _core->UnregisterExtension(_playlistManagerListener);
                _playlistManagerListener->Release();
                _playlistManagerListener = NULL;
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
        void ManagedAimpCore::OnCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
        {
            CoreMessage(param1, param2);
        }

        void ManagedAimpCore::OnInternalCoreMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
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
            This->OnCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)param, param1);
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
            HRESULT result = _core->QueryInterface(iid, (void**) &_service);
            if (result == S_OK)
            {
                *service = _service;
            }

            return result;
        }

        IUnknown* ManagedAimpCore::QueryInterface(REFIID iid)
        {
            IUnknown* service;
            HRESULT result = _core->QueryInterface(iid, (void**)&service);
            if (result != S_OK)
            {
                return NULL;
            }

            return service;
        }

        /// <summary>
        /// Creates the action event.
        /// </summary>
        /// <returns></returns>
        IAIMPActionEvent* ManagedAimpCore::CreateActionEvent()
        {
            IAIMPActionEvent* actionEvent = NULL;
            _core->CreateObject(IID_IAIMPActionEvent, (void**)&actionEvent);
            return actionEvent;
        }

        HRESULT ManagedAimpCore::SendMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType message, int value, Object ^obj)
        {
            HRESULT r;

            if (message == AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION)
            {
                r = ShowNotification(value == 0, (String^)obj);
            }
            else
            {
                r = _messageDispatcher->Send((DWORD)message, value, (void*)&obj);
            }

            return r;
        }

        HRESULT ManagedAimpCore::ShowNotification(bool autoHide, String ^notification)
        {
            IAIMPString *str = AimpConverter::ToAimpString(notification);
            HRESULT r = _messageDispatcher->Send((DWORD)AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION, autoHide ? 0 : 1, str->GetData());
            str->Release();
            return r;
        }

        /// <summary>
        /// Creates the new AIMP stream.
        /// </summary>
        AimpActionResult ManagedAimpCore::CreateStream(IAIMPStream **stream)
        {
            IAIMPStream* s = NULL;
            AimpActionResult result = Utils::CheckResult(_core->CreateObject(IID_IAIMPMemoryStream, (void**)&s));
            *stream = s;
            return result;
        }

        AIMP::SDK::AimpActionResult ManagedAimpCore::CreateAction(IAIMPAction **action)
        {
            IAIMPAction *a = NULL;
            AimpActionResult result = Utils::CheckResult(_core->CreateObject(IID_IAIMPAction, (void**)&a));
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
            HRESULT r = _core->CreateObject(IID_IAIMPMenuItem, (void**)&i);
            *item = i;
            return r;
        }

        OptionsDialogFrameExtension* ManagedAimpCore::GetOptionsFrame()
        {
            return _optionsFrame;
        }
    }
}
