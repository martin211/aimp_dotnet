// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlayListQueue.h"

AimpPlaylistQueue::AimpPlaylistQueue(IAIMPPlaylistQueue* queue, IAIMPPlaylistQueue2* queue2) : AimpObject(queue) {
    _listner = new AimpPlaylistQueueListener(this);
    queue2->ListenerAdd(_listner);
}

bool AimpPlaylistQueue::IsSuspended::get() {
    IAIMPPropertyList* properties = nullptr;
    try {
        InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&properties));
        return PropertyListExtension::GetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED);
    }
    finally {
        if (properties != nullptr) {
            properties->Release();
        }
    }
}

void AimpPlaylistQueue::IsSuspended::set(bool value) {
    IAIMPPropertyList* properties = nullptr;
    InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&properties));
    PropertyListExtension::SetBool(properties, AIMP_PLAYLISTQUEUE_PROPID_SUSPENDED, value);
    properties->Release();
}

ActionResult AimpPlaylistQueue::Add(IAimpPlaylistItem^ item, bool insertAtBeginning) {
    const auto internalObj = static_cast<AimpPlaylistItem^>(item)->InternalAimpObject;
    if (internalObj == nullptr) {
        NULL_REFERENCE()
    }

    return ACTION_RESULT(CheckResult(InternalAimpObject->Add(internalObj, insertAtBeginning)));
}

ActionResult AimpPlaylistQueue::AddList(Generic::IList<IAimpPlaylistItem^>^ items, bool insertAtBeginning) {
    ActionResultType result = ActionResultType::Fail;
    if (items->Count > 0) {
        IAIMPObjectList* list = nullptr;
        result = CheckResult(
            ManagedAimpCore::GetAimpCore()->CreateObject(IID_IAIMPObjectList, reinterpret_cast<void**>(&list)));
        if (result == ActionResultType::OK && list != nullptr) {
            for (int i = 0; i < items->Count; i++) {
                result = CheckResult(list->Add(static_cast<AimpPlaylistItem^>(items[i])->InternalAimpObject));

                if (result != ActionResultType::OK) {
                    return ACTION_RESULT(result);
                }
            }

            result = CheckResult(InternalAimpObject->AddList(list, insertAtBeginning));
        }
    }

    return ACTION_RESULT(result);
}

int AimpPlaylistQueue::GetItemCount() {
    return InternalAimpObject->GetItemCount();
}

ActionResult AimpPlaylistQueue::Delete(IAimpPlaylist^ playList) {
    return ACTION_RESULT(
        CheckResult(InternalAimpObject->Delete2(static_cast<AimpPlayList^>(playList)->InternalAimpObject)));
}

ActionResult AimpPlaylistQueue::Delete(IAimpPlaylistItem^ item) {
    return ACTION_RESULT(
        CheckResult(InternalAimpObject->Delete(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject)));
}

ActionResult AimpPlaylistQueue::Move(IAimpPlaylistItem^ item, int index) {
    return ACTION_RESULT(
        CheckResult(InternalAimpObject->Move(static_cast<AimpPlaylistItem^>(item)->InternalAimpObject, index)));
}

ActionResult AimpPlaylistQueue::Move(int index, int targetIndex) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Move2(index, targetIndex)));
}

AimpActionResult<IAimpPlaylistItem^>^ AimpPlaylistQueue::GetItem(int index) {
    IAIMPPlaylistItem* aimpItem = nullptr;
    IAimpPlaylistItem^ item = nullptr;

    const auto res = CheckResult(InternalAimpObject->GetItem(
            index,
            IID_IAIMPPlaylistItem,
            reinterpret_cast<void**>(&aimpItem))
    );

    if (res == ActionResultType::OK && aimpItem != nullptr) {
        item = gcnew AimpPlaylistItem(aimpItem);
    }

    return gcnew AimpActionResult<IAimpPlaylistItem^>(res, item);
}


void AimpPlaylistQueue::ContentChanged::add(AimpPlaylistQueueListenerHandler^ onEvent) {
    if (_contentChanged == nullptr) {
        _contentChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Combine(_contentChanged, onEvent));
    }
}

void AimpPlaylistQueue::ContentChanged::remove(AimpPlaylistQueueListenerHandler^ onEvent) {
    if (_contentChanged != nullptr) {
        _contentChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Remove(_contentChanged, onEvent));
    }
}

void AimpPlaylistQueue::ContentChanged::raise(IAimpPlaylistQueue^ sender) {
    if (_contentChanged != nullptr) {
        _contentChanged(sender);
    }
}


void AimpPlaylistQueue::StateChanged::add(AimpPlaylistQueueListenerHandler^ onEvent) {
    if (_stateChanged == nullptr) {
        _stateChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Combine(_stateChanged, onEvent));
    }
}

void AimpPlaylistQueue::StateChanged::remove(AimpPlaylistQueueListenerHandler^ onEvent) {
    if (_stateChanged != nullptr) {
        _stateChanged = static_cast<AimpPlaylistQueueListenerHandler^>(Delegate::Remove(_stateChanged, onEvent));
    }
}

void AimpPlaylistQueue::StateChanged::raise(IAimpPlaylistQueue^ sender) {
    if (_stateChanged != nullptr) {
        _stateChanged(sender);
    }
}
