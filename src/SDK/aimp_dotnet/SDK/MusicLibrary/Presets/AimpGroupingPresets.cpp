//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpGroupingPresets.h"
#include "AimpGroupingPresetStandard.h"
#include "SDK/MusicLibrary/Internal/InternalAimpSortItem.h"

using namespace AIMP::SDK;

AimpGroupingPresets::AimpGroupingPresets(IAIMPMLGroupingPresets* aimpObject) : AimpObject(aimpObject) {
    _internalProvider = nullptr;
}

AimpActionResult<IAimpGroupingPresetStandard^>^ AimpGroupingPresets::Add(String^ id, String^ name, String^ fieldName) {
    IAIMPMLGroupingPresetStandard* standartPreset;

    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    IAIMPString* aimpName = AimpConverter::ToAimpString(name);
    IAIMPString* aimpFieldName = AimpConverter::ToAimpString(name);

    const ActionResultType result =
        CheckResult(InternalAimpObject->Add3(aimpId, aimpName, 0, aimpFieldName, &standartPreset));

    aimpId->Release();
    aimpName->Release();
    aimpFieldName->Release();

    IAimpGroupingPresetStandard^ preset = nullptr;
    if (result == ActionResultType::OK) {
        preset = gcnew AimpGroupingPresetStandard(standartPreset);
    }

    return gcnew AimpActionResult<IAimpGroupingPresetStandard^>(result, preset);
}

AimpActionResult<IAimpGroupingPreset^>^ AimpGroupingPresets::Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider) {
    IAimpGroupingPreset^ preset = nullptr;

    // create internal wrapper for grouping provider
    _internalProvider = new InternalAimpGroupingTreeDataProvider(provider);
    IAIMPMLGroupingPreset* aimpPreset = nullptr;
    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    IAIMPString* aimpName = AimpConverter::ToAimpString(name);

    const ActionResultType result = CheckResult(
        InternalAimpObject->Add(aimpId, aimpName, 0, _internalProvider, &aimpPreset));

    aimpId->Release();
    aimpName->Release();

    if (result == ActionResultType::OK) {
        preset = gcnew AimpGroupingPreset(aimpPreset);
    }

    return gcnew AimpActionResult<IAimpGroupingPreset^>(result, preset);
}

AimpActionResult<IAimpGroupingPresetStandard^>^ AimpGroupingPresets::Add(String^ id, String^ name, Generic::IList<IAimpSortItem^>^ fieldNames) {
    IAIMPObjectList* fields = AimpConverter::CreateAimpObject<IAIMPObjectList>(IID_IAIMPObjectList);

    for (int i = 0; i < fieldNames->Count; i++) {
        auto item = new InternalAimpSortItem(fieldNames[i]);
        fields->Add(reinterpret_cast<IUnknown*>(item));
    }

    IAIMPMLGroupingPresetStandard* standardPreset = nullptr;
    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    IAIMPString* aimpName = AimpConverter::ToAimpString(name);

    const ActionResultType result = CheckResult(InternalAimpObject->Add2(aimpId, aimpName, 0, fields, &standardPreset));
    IAimpGroupingPresetStandard^ preset = nullptr;

    aimpId->Release();
    aimpName->Release();

    if (result == ActionResultType::OK) {
        preset = gcnew AimpGroupingPresetStandard(standardPreset);
    }

    return gcnew AimpActionResult<IAimpGroupingPresetStandard^>(result, preset);
}

void AimpGroupingPresets::BeginUpdate() {
    InternalAimpObject->BeginUpdate();
}

void AimpGroupingPresets::EndUpdate() {
    InternalAimpObject->EndUpdate();
}

ActionResult AimpGroupingPresets::Delete(int index) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Delete(index)));
}

int AimpGroupingPresets::GetCount(void) {
    return InternalAimpObject->GetCount();
}

generic <class TAimpGroupingPreset>
AimpActionResult<TAimpGroupingPreset>^ AimpGroupingPresets::Get(int index) {
    const auto t = TAimpGroupingPreset::typeid;
    if (t == IAimpGroupingPreset::typeid) {
        IAIMPMLGroupingPreset* p = nullptr;
        IAimpGroupingPreset^ preset = nullptr;
        const ActionResultType result = CheckResult(InternalAimpObject->Get(index, IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&p)));

        if (result == ActionResultType::OK) {
            preset = gcnew AimpGroupingPreset(p);
        }

        return gcnew AimpActionResult<TAimpGroupingPreset>(result, safe_cast<TAimpGroupingPreset>(preset));
    }

    if (t == IAimpGroupingPresetStandard::typeid) {
        IAIMPMLGroupingPresetStandard* p = nullptr;
        IAimpGroupingPresetStandard^ preset = nullptr;
        const ActionResultType result = CheckResult(InternalAimpObject->Get(index, IID_IAIMPMLGroupingPresetStandard, reinterpret_cast<void**>(&p)));

        if (result == ActionResultType::OK) {
            preset = gcnew AimpGroupingPresetStandard(p);
        }

        return gcnew AimpActionResult<TAimpGroupingPreset>(result, safe_cast<TAimpGroupingPreset>(preset));
    }

    return gcnew AimpActionResult<TAimpGroupingPreset>(ActionResultType::InvalidArguments);
}

generic <class TAimpGroupingPreset>
AimpActionResult<TAimpGroupingPreset>^ AimpGroupingPresets::GetById(String^ id) {
    const auto t = TAimpGroupingPreset::typeid;
    if (t == IAimpGroupingPreset::typeid) {
        IAIMPMLGroupingPreset* p = nullptr;
        IAimpGroupingPreset^ preset = nullptr;

        IAIMPString* aimpId = AimpConverter::ToAimpString(id);
        const ActionResultType result = CheckResult(InternalAimpObject->GetByID(aimpId, IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&p)));
        RELEASE(aimpId)

        if (result == ActionResultType::OK) {
            preset = gcnew AimpGroupingPreset(p);
        }

        return gcnew AimpActionResult<TAimpGroupingPreset>(result, safe_cast<TAimpGroupingPreset>(preset));
    }

    if (t == IAimpGroupingPresetStandard::typeid) {
        IAIMPMLGroupingPresetStandard* p = nullptr;
        IAimpGroupingPresetStandard^ preset = nullptr;

        IAIMPString* aimpId = AimpConverter::ToAimpString(id);
        const ActionResultType result = CheckResult(InternalAimpObject->GetByID(aimpId, IID_IAIMPMLGroupingPresetStandard, reinterpret_cast<void**>(&p)));
        RELEASE(aimpId)

        if (result == ActionResultType::OK) {
            preset = gcnew AimpGroupingPresetStandard(p);
        }

        return gcnew AimpActionResult<TAimpGroupingPreset>(result, safe_cast<TAimpGroupingPreset>(preset));
    }

    return gcnew AimpActionResult<TAimpGroupingPreset>(ActionResultType::InvalidArguments);
}
