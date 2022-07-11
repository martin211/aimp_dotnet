// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageManager.h"
#include "SDK/Action/AimpActionEvent.h"

using namespace AIMP::SDK;
using namespace Actions;
using namespace Actions::Objects;

AimpDataStorageManager::AimpDataStorageManager(IAIMPMLDataStorageManager* manager) : AimpObject(manager) {
}

ActionResult AimpDataStorageManager::BackgroundTaskStarted(int id, System::String^ caption, IAimpActionEvent^ cancelEvent) {
    AimpActionEvent* action = nullptr;
    auto str = AimpConverter::ToAimpString(caption);
    auto result = ActionResultType::Fail;

    if (cancelEvent != nullptr) {
        action = new AimpActionEvent(cancelEvent);
    }

    try {
        result = Utils::CheckResult(this->InternalAimpObject->BackgroundTaskStarted(id, str, action));
    }
    finally {
        RELEASE(str)
    }

    return ACTION_RESULT(result);
}

ActionResult AimpDataStorageManager::BackgroundTaskFinished(int id) {
    return ACTION_RESULT(Utils::CheckResult(this->InternalAimpObject->BackgroundTaskFinished(id)));
}

void AimpDataStorageManager::Changed() {
    this->InternalAimpObject->Changed();
}
