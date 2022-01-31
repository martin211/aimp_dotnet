#include "stdafx.h"
#include "AimpServicePlayer.h"

#include "SDK/FileManager/AimpFileInfo.h"
#include "SDK/PlayList/AimpPlayListItem.h"
#include "AIMPSDK/AIMPSDK.h"
#include "SDK/Playback/AimpPlaybackQueueItem.h"
#include "SDK/PlayList/AimpPlayList.h"

AimpServicePlayer::AimpServicePlayer(ManagedAimpCore^ core) : BaseAimpService<IAIMPServicePlayer2>(core) {
}

AIMP::AimpPlayerState AimpServicePlayer::State::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        int state = static_cast<IAIMPServicePlayer*>(service)->GetState();
        return static_cast<AimpPlayerState>(state);
    }
    finally {
        ReleaseObject(service);
    }
}

double AimpServicePlayer::Duration::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    double value = 0;
    try {
        if (CheckResult(static_cast<IAIMPServicePlayer*>(service)->GetDuration(&value)) == ActionResultType::OK) {
            return value;
        }

        return 0;
    }
    finally {
        ReleaseObject(service);
    }
}

double AimpServicePlayer::Position::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    double value = 0;
    try {
        if (CheckResult(static_cast<IAIMPServicePlayer*>(service)->GetPosition(&value)) == ActionResultType::OK) {
            return value;
        }

        return 0;
    }
    finally {
        ReleaseObject(service);
    }
}

void AimpServicePlayer::Position::set(double position) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        static_cast<IAIMPServicePlayer*>(service)->SetPosition(position);
    }
    finally {
        ReleaseObject(service);
    }
}

float AimpServicePlayer::Volume::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    float value = 0;
    try {
        if (CheckResult(static_cast<IAIMPServicePlayer*>(service)->GetVolume(&value)) == ActionResultType::OK) {
            return value;
        }

        return 0;
    }
    finally {
        ReleaseObject(service);
    }
}

void AimpServicePlayer::Volume::set(float volume) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        static_cast<IAIMPServicePlayer*>(service)->SetVolume(volume);
    }
    finally {
        ReleaseObject(service);
    }
}

bool AimpServicePlayer::IsMute::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    bool value = false;
    try {
        if (CheckResult(static_cast<IAIMPServicePlayer*>(service)->GetMute(&value)) == ActionResultType::OK) {
            return value;
        }

        return false;
    }
    finally {
        ReleaseObject(service);
    }
}

void AimpServicePlayer::IsMute::set(bool value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        static_cast<IAIMPServicePlayer*>(service)->SetMute(value);
    }
    finally {
        ReleaseObject(service);
    }
}

IAimpFileInfo^ AimpServicePlayer::CurrentFileInfo::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPFileInfo* fi = nullptr;
    try {
        if (CheckResult(static_cast<IAIMPServicePlayer*>(service)->GetInfo(&fi)) == ActionResultType::OK && fi != nullptr) {
            return gcnew AimpFileInfo(fi);
        }

        return nullptr;
    }
    finally {
        ReleaseObject(service);
    }
}

IAimpPlaylistItem^ AimpServicePlayer::CurrentPlaylistItem::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPlaylistItem* item = nullptr;
    try {
        if (CheckResult(static_cast<IAIMPServicePlayer*>(service)->GetPlaylistItem(&item)) == ActionResultType::OK && item != nullptr) {
            return gcnew AimpPlaylistItem(item);
        }

        return nullptr;
    }
    finally {
        ReleaseObject(service);
    }
}

ActionOnTrackEnd AimpServicePlayer::ActionOnEndOfTrack::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        int value = PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_STOP_AFTER_TRACK);
        return static_cast<ActionOnTrackEnd>(value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::ActionOnEndOfTrack::set(ActionOnTrackEnd value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_STOP_AFTER_TRACK, static_cast<int>(value));
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

bool AimpServicePlayer::AutoJumpToNextTrack::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetBool(prop, AIMP_PLAYER_PROPID_AUTO_JUMP_TO_NEXT_TRACK);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::AutoJumpToNextTrack::set(bool value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetBool(prop, AIMP_PLAYER_PROPID_AUTO_JUMP_TO_NEXT_TRACK, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

bool AimpServicePlayer::AutoSwitching::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetBool(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::AutoSwitching::set(bool value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetBool(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::AutoSwitchingPauseBetweenTracks::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_PAUSE_BETWEEN_TRACKS);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::AutoSwitchingPauseBetweenTracks::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_PAUSE_BETWEEN_TRACKS, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::AutoSwitchingCrossFade::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_CROSSFADE);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::AutoSwitchingCrossFade::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_CROSSFADE, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::AutoSwitchingFadeIn::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_FADEIN);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::AutoSwitchingFadeIn::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_FADEIN, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::AutoSwitchingFadeOut::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_FADEOUT);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::AutoSwitchingFadeOut::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_AUTOSWITCHING_FADEOUT, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

bool AimpServicePlayer::ManualSwitching::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetBool(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::ManualSwitching::set(bool value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetBool(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::ManualSwitchingCrossFade::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING_CROSSFADE);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::ManualSwitchingCrossFade::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING_CROSSFADE, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::ManualSwitchingFadeIn::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING_FADEIN);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::ManualSwitchingFadeIn::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING_FADEIN, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

int AimpServicePlayer::ManualSwitchingFadeOut::get() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        return PropertyListExtension::GetInt32(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING_FADEOUT);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

void AimpServicePlayer::ManualSwitchingFadeOut::set(int value) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    IAIMPPropertyList* prop = nullptr;
    try {
        service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
        PropertyListExtension::SetInt32(prop, AIMP_PLAYER_PROPID_MANUALSWITCHING_FADEOUT, value);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(prop);
    }
}

AimpActionResult^ AimpServicePlayer::Play(IAimpPlaybackQueueItem^ item, int offset, Player::PlayFlags flags) {
    const auto service = GetAimpService();
    try {
        if (service == nullptr) {
            return ACTION_RESULT(ActionResultType::Fail);
        }

        return ACTION_RESULT(
            CheckResult(service->Play(static_cast<AimpPlaybackQueueItem^>(item)->InternalAimpObject, offset, static_cast
                <DWORD>(flags))));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Play(IAimpPlaylistItem^ item, int offset, Player::PlayFlags flags) {
    const auto service = GetAimpService();
    try {
        if (service == nullptr) {
            return ACTION_RESULT(ActionResultType::Fail);
        }

        return ACTION_RESULT(
            CheckResult(service->Play2(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject, offset, static_cast<
                DWORD>(flags))));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Play(String^ fileUri, int offset, Player::PlayFlags flags) {
    const auto service = GetAimpService();
    try {
        if (service == nullptr) {
            return ACTION_RESULT(ActionResultType::Fail);
        }

        return ACTION_RESULT(
            CheckResult(service->Play4(AimpConverter::ToAimpString(fileUri), offset, static_cast<DWORD>(flags))));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Play(IAimpPlaybackQueueItem^ queueItem) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(
            CheckResult(static_cast<IAIMPServicePlayer*>(service)->Play(static_cast<AimpPlaybackQueueItem^>(queueItem)->InternalAimpObject)));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Play(IAimpPlaylistItem^ playlistItem) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(
            CheckResult(static_cast<IAIMPServicePlayer*>(service)->Play2(static_cast<AimpPlaylistItem^>(playlistItem)->InternalAimpObject)));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Play(IAimpPlaylist^ playList) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->Play3(static_cast<AimpPlayList^>(playList)->InternalAimpObject)));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Play(String^ fileUri, Player::PlayFlags flags) {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(
            CheckResult(static_cast<IAIMPServicePlayer*>(service)->Play4(AimpConverter::ToAimpString(fileUri), static_cast<DWORD>(flags))));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::GoToNext() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->GoToNext()));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::GoToPrev() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->GoToPrev()));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Pause() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->Pause()));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Resume() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->Resume()));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::Stop() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->Stop()));
    }
    finally {
        ReleaseObject(service);
    }
}

AimpActionResult^ AimpServicePlayer::StopAfterTrack() {
    IUnknown* service = GetAimpService();
    if (service == nullptr) {
        service = GetService();
    }

    try {
        return ACTION_RESULT(CheckResult(static_cast<IAIMPServicePlayer*>(service)->StopAfterTrack()));
    }
    finally {
        ReleaseObject(service);
    }
}

IAIMPServicePlayer2* AimpServicePlayer::GetAimpService() {
    IAIMPServicePlayer2* service = nullptr;
    const auto result = GetService(IID_IAIMPServicePlayer2, &service);
    return service;
}

IAIMPServicePlayer* AimpServicePlayer::GetService() {
    IAIMPServicePlayer* service = nullptr;
    _core->GetService(IID_IAIMPServicePlayer, reinterpret_cast<void**>(&service));
    return service;
}
