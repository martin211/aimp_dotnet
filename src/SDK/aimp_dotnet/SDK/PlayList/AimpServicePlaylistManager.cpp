//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServicePlaylistManager.h"
#include "AimpExtensionPlaylistPreimageFactory.h"

using namespace AIMP::SDK;

AimpServicePlaylistManager::AimpServicePlaylistManager(ManagedAimpCore^ core) : BaseAimpService<
    IAIMPServicePlaylistManager2>(core) {
}

IAimpPlaylistQueue^ AimpServicePlaylistManager::PlaylistQueue::get() {
    IAIMPServicePlaylistManager2* service = GetAimpService();

    try {
        if (service != nullptr) {
            IAIMPPlaylistQueue* playListQueue = nullptr;
            auto result = CheckResult(
                service->QueryInterface(IID_IAIMPPlaylistQueue, reinterpret_cast<void**>(&playListQueue)));

            if (result != ActionResultType::OK) {
                ACTION_ERROR(result)
            }

            IAIMPPlaylistQueue2* playListQueue2;
            result = CheckResult(
                service->QueryInterface(IID_IAIMPPlaylistQueue2, reinterpret_cast<void**>(&playListQueue2)));
            if (result != ActionResultType::OK) {
                ACTION_ERROR(result)
            }

            return gcnew AimpPlaylistQueue(playListQueue, playListQueue2);
        }
    }
    finally {
        ReleaseObject(service);
    }

    return nullptr;
}

void AimpServicePlaylistManager::PlaylistActivated::add(PlayListHandler^ onEvent) {
    _onPlaylistActivated = onEvent;
}

void AimpServicePlaylistManager::PlaylistActivated::remove(PlayListHandler^ onEvent) {
    _onPlaylistActivated = nullptr;
}

void AimpServicePlaylistManager::PlaylistActivated::raise(String^ playListName, String^ playListId) {
    if (_onPlaylistActivated != nullptr) {
        _onPlaylistActivated(playListName, playListId);
    }
}

void AimpServicePlaylistManager::PlaylistAdded::add(PlayListHandler^ onEvent) {
    if (_onPlaylistAdded == nullptr) {
        _onPlaylistAdded = onEvent;
    }
}

void AimpServicePlaylistManager::PlaylistAdded::remove(PlayListHandler^ onEvent) {
    if (_onPlaylistAdded != nullptr) {
        _onPlaylistAdded = nullptr;
    }
}

void AimpServicePlaylistManager::PlaylistAdded::raise(String^ playListName, String^ playListId) {
    if (_onPlaylistAdded != nullptr) {
        _onPlaylistAdded(playListName, playListId);
    }
}

void AimpServicePlaylistManager::PlaylistRemoved::add(PlayListHandler^ onEvent) {
    _onPlaylistRemoved = onEvent;
}

void AimpServicePlaylistManager::PlaylistRemoved::remove(PlayListHandler^ onEvent) {
    _onPlaylistRemoved = nullptr;
}

void AimpServicePlaylistManager::PlaylistRemoved::raise(String^ playListName, String^ playListId) {
    if (_onPlaylistRemoved != nullptr) {
        _onPlaylistRemoved(playListName, playListId);
    }
}

PlaylistResult AimpServicePlaylistManager::CreatePlaylist(String^ name, bool isActive) {
    IAimpPlaylist^ playList = nullptr;
    ActionResultType res = ActionResultType::Fail;

    IAIMPPlaylist* pl = nullptr;
    IAIMPString* str = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();

    try {
        if (service != nullptr) {
            if (!String::IsNullOrEmpty(name)) {
                str = AimpConverter::ToAimpString(name);
            }

            res = CheckResult(service->CreatePlaylist(str, BOOL(isActive), &pl));

            if (res == ActionResultType::OK && pl != nullptr) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

PlaylistResult AimpServicePlaylistManager::CreatePlaylistFromFile(String^ fileName, bool isActive) {
    Assert::NotNull(fileName, "fileName");

    IAimpPlaylist^ playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPString* str = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(fileName);
            res = CheckResult(service->CreatePlaylistFromFile(str, BOOL(isActive), &pl));

            if (res == ActionResultType::OK && pl != nullptr) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

PlaylistResult AimpServicePlaylistManager::GetActivePlaylist() {
    IAimpPlaylist^ playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            res = CheckResult(service->GetActivePlaylist(&pl));
            if (res == ActionResultType::OK) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

PlaylistResult AimpServicePlaylistManager::GetLoadedPlaylist(int index) {
    IAimpPlaylist^ playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            res = CheckResult(service->GetLoadedPlaylist(index, &pl));
            if (res == ActionResultType::OK) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

PlaylistResult AimpServicePlaylistManager::GetPlayingPlaylist() {
    IAimpPlaylist^ playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            res = CheckResult(service->GetPlayingPlaylist(&pl));
            if (res == ActionResultType::OK) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

PlaylistResult AimpServicePlaylistManager::GetLoadedPlaylistById(System::String^ id) {
    IAimpPlaylist^ playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPString* key = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            key = AimpConverter::ToAimpString(id);
            res = CheckResult(service->GetLoadedPlaylistByID(key, &pl));
            if (res == ActionResultType::OK) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(key);
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

PlaylistResult AimpServicePlaylistManager::GetLoadedPlaylistByName(String^ name) {
    IAimpPlaylist^ playList = nullptr;
    IAIMPPlaylist* pl = nullptr;
    IAIMPString* key = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            key = AimpConverter::ToAimpString(name);
            res = CheckResult(service->GetLoadedPlaylistByName(key, &pl));

            if (res == ActionResultType::OK) {
                playList = gcnew AimpPlayList(pl);
            }
        }
    }
    finally {
        ReleaseObject(key);
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpPlaylist^>(res, playList);
}

int AimpServicePlaylistManager::GetLoadedPlaylistCount() {
    IAIMPServicePlaylistManager2* service = GetAimpService();

    try {
        if (service != nullptr) {
            return service->GetLoadedPlaylistCount();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

ActionResult AimpServicePlaylistManager::SetActivePlaylist(IAimpPlaylist^ playList) {
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            res = CheckResult(service->SetActivePlaylist(static_cast<AimpPlayList^>(playList)->InternalAimpObject));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(res);
}

//void AimpServicePlaylistManager::OnPlaylistActivated(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList* properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistActivated(name, id);
//    properties->Release();
//    properties = nullptr;
//}
//
//void AimpServicePlaylistManager::OnPlaylistAdded(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList* properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistAdded(name, id);
//    properties->Release();
//    properties = nullptr;
//}
//
//void AimpServicePlaylistManager::OnPlaylistRemoved(IAIMPPlaylist* playlist)
//{
//    IAIMPPropertyList* properties;
//    playlist->QueryInterface(IID_IAIMPPropertyList, (void**)&properties);
//    String ^name = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_NAME);
//    String ^id = AIMP::SDK::PropertyListExtension::GetString(properties, AIMP_PLAYLIST_PROPID_ID);
//    this->PlaylistRemoved(name, id);
//    properties->Release();
//    properties = nullptr;
//}

TYPED_RESULT(IAimpExtensionPlaylistPreimageFactory) AimpServicePlaylistManager::GetPreimageFactory(int index) {
    IAimpExtensionPlaylistPreimageFactory^ factory = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            IAIMPExtensionPlaylistPreimageFactory* aimpFactory = nullptr;

            res = CheckResult(service->GetPreimageFactory(index, &aimpFactory));
            if (res == ActionResultType::OK && aimpFactory != nullptr) {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return RETURN_TYPED_RESULT(IAimpExtensionPlaylistPreimageFactory, res, factory);
}

TYPED_RESULT(IAimpExtensionPlaylistPreimageFactory) AimpServicePlaylistManager::GetPreimageFactoryById(String^ id) {
    IAimpExtensionPlaylistPreimageFactory^ factory = nullptr;
    IAIMPServicePlaylistManager2* service = GetAimpService();
    ActionResultType res = ActionResultType::Fail;
    IAIMPString* idStr = AimpConverter::ToAimpString(id);
    IAIMPExtensionPlaylistPreimageFactory* aimpFactory = nullptr;

    try {
        if (service != nullptr) {
            res = CheckResult(service->GetPreimageFactoryByID(idStr, &aimpFactory));

            if (res == ActionResultType::OK && aimpFactory != nullptr) {
                factory = gcnew AimpExtensionPlaylistPreimageFactory(aimpFactory);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(idStr);
    }

    return RETURN_TYPED_RESULT(IAimpExtensionPlaylistPreimageFactory, res, factory);
}

int AimpServicePlaylistManager::GetPreimageFactoryCount() {
    IAIMPServicePlaylistManager2* service = GetAimpService();

    try {
        if (service != nullptr) {
            return service->GetPreimageFactoryCount();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

IAIMPServicePlaylistManager2* AimpServicePlaylistManager::GetAimpService() {
    IAIMPServicePlaylistManager2* service = nullptr;
    GetService(IID_IAIMPServicePlaylistManager2, &service);
    return service;
}
