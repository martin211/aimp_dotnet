#include "..\Stdafx.h"
#include "ManagedAimpCore.h"
#include "..\IUnknownInterfaceImpl.h"
#include "PlayList\AimpPlayList.h"
#include "Converter.h"
#include "..\AimpSdk.h"
#include "..\Extensions\OptionsDialogFrameExtension.h"
#include "..\Extensions\AimpExtensionAlbumArtCatalog.h"

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
            explicit AIMPMessageHook(gcroot<ManagedAimpCore^> aimp36_manager)
                :
                aimp36_manager_(aimp36_manager)
            {}

            virtual void WINAPI CoreMessage(DWORD AMessage, int AParam1, void *AParam2, HRESULT *AResult) {
                aimp36_manager_->OnCoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)AMessage, AParam1);
            }

        private:
            gcroot<ManagedAimpCore^> aimp36_manager_;
        };

        ManagedAimpCore::ManagedAimpCore(IAIMPCore* core)
        {
            _core = core;
            _nativeEventHelper = new EventHelper();

            IAIMPServiceMessageDispatcher* aimp_service_message_dispatcher;
            core->QueryInterface(IID_IAIMPServiceMessageDispatcher, reinterpret_cast<void**>(&aimp_service_message_dispatcher));
            _hook = new AIMPMessageHook(this);
            aimp_service_message_dispatcher->Hook(_hook);
            _messageDispatcher = aimp_service_message_dispatcher;
        }

        ManagedAimpCore::~ManagedAimpCore()
        {
            System::Diagnostics::Debug::WriteLine("Dispose ManagedAimpCore");
            _messageDispatcher->Unhook(_hook);
            _messageDispatcher->Release();
            
            if (_optionsFrame != nullptr)
            {
                _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = NULL;
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
            IAIMPString_ptr path(res, false);
            pathResult = gcnew System::String(std::wstring(path->GetData(), path->GetLength()).c_str());
            //res->Release();
            return AIMP::SDK::AimpActionResult::Ok;
        }

        /// <summary>
        /// Registers the extension.
        /// </summary>
        /// <param name="extensionId">The extension identifier.</param>
        /// <param name="extension">The extension.</param>
        /// <returns></returns>
        bool ManagedAimpCore::RegisterExtension(GUID extensionId, AIMP::IAimpExtension^ extension)
        {
            AIMP::SDK::Options::IAimpOptionsDialogFrame^ optionsFrameExtension = dynamic_cast<AIMP::SDK::Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr)
            {
                OptionsDialogFrameExtension* odfp = new OptionsDialogFrameExtension(this->GetAimpCore(), optionsFrameExtension);
                _optionsFrame = odfp;
                HRESULT result = _core->RegisterExtension(IID_IAIMPServiceOptionsDialog, static_cast<OptionsDialogFrameExtension::Base*>(odfp));
                return result == S_OK;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^ albumArtCatalogExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr)
            {
                AimpExtensionAlbumArtCatalog *cat = new AimpExtensionAlbumArtCatalog(this->GetAimpCore(), albumArtCatalogExtension);
                _albumArtCatalogExtension = cat;
                HRESULT result = _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtCatalog::Base*>(cat));
                return result == S_OK;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^ albumArtProviderExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr)
            {
                AimpExtensionAlbumArtProvider *ext = new AimpExtensionAlbumArtProvider(this->GetAimpCore(), albumArtProviderExtension);
                _albumArtProviderExtension = ext;
                HRESULT result = _core->RegisterExtension(IID_IAIMPServiceAlbumArt, static_cast<AimpExtensionAlbumArtProvider::Base*>(ext));
                return result == S_OK;
            }

            return false;
        }

        void ManagedAimpCore::UnregisterExtension(IAimpExtension^ extension)
        {
            AIMP::SDK::Options::IAimpOptionsDialogFrame^ optionsFrameExtension = dynamic_cast<AIMP::SDK::Options::IAimpOptionsDialogFrame^>(extension);
            if (optionsFrameExtension != nullptr)
            {
                _core->UnregisterExtension(static_cast<IAIMPOptionsDialogFrame*>(_optionsFrame));
                _optionsFrame->Release();
                _optionsFrame = NULL;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^ albumArtCatalogExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtCatalog^>(extension);
            if (albumArtCatalogExtension != nullptr)
            {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtCatalog::Base*>(_albumArtCatalogExtension));
                _albumArtCatalogExtension->Release();
                _albumArtCatalogExtension = nullptr;
            }

            AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^ albumArtProviderExtension = dynamic_cast<AIMP::SDK::AlbumArtManager::IAimpExtensionAlbumArtProvider^>(extension);
            if (albumArtProviderExtension != nullptr)
            {
                _core->UnregisterExtension(static_cast<AimpExtensionAlbumArtProvider::Base*>(_albumArtProviderExtension));
                _albumArtProviderExtension->Release();
                _albumArtProviderExtension = nullptr;
            }
        }

        void ManagedAimpCore::UnregisterExtension(IUnknown* extension)
        {
            _core->UnregisterExtension(extension);
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

        void ManagedAimpCore::OnPlaylistActivated(IAIMPPlaylist *playlist)
        {
            AimpPlayList ^pl = gcnew AimpPlayList(playlist);
            this->PlaylistActivated(pl->Name, pl->Id);
            pl = nullptr;
        }

        void ManagedAimpCore::OnPlayListAdded(IAIMPPlaylist *playlist)
        {
            AimpPlayList ^pl = gcnew AimpPlayList(playlist);
            this->PlaylistAdded(pl->Name, pl->Id);
            pl = nullptr;
        }

        void ManagedAimpCore::OnPlayListRemoved(IAIMPPlaylist *playlist)
        {
            AimpPlayList ^pl = gcnew AimpPlayList(playlist);
            this->PlaylistRemoved(pl->Name, pl->Id);
            pl = nullptr;
        }

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
            return _core->QueryInterface(iid, service);
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
            IAIMPString *str = Converter::MakeAimpString(_core, notification);
            return _messageDispatcher->Send((DWORD)AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_SHOW_NOTIFICATION, autoHide ? 0 : 1, str->GetData());
        }

        /// <summary>
        /// Creates the new AIMP stream.
        /// </summary>
        IAIMPStream* ManagedAimpCore::CreateStream()
        {
            IAIMPStream* stream;
            _core->CreateObject(IID_IAIMPMemoryStream, (void**)&stream);
            return stream;
        }

        IAIMPCore* ManagedAimpCore::GetAimpCore()
        {
            return _core;
        }


        OptionsDialogFrameExtension* ManagedAimpCore::GetOptionsFrame()
        {
            return _optionsFrame;
        }
    }
}