// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpGroupingPresets.h"
#include "AimpGroupingPresetStandard.h"

using namespace AIMP::SDK;

AimpGroupingPresets::AimpGroupingPresets(IAIMPMLGroupingPresets* aimpObject) : AimpObject(aimpObject)
{
    _internalProvider = nullptr;
}

AimpActionResult AimpGroupingPresets::Add(String^ id, String^ name, String^ fieldName,
                                          IAimpGroupingPresetStandard^% preset)
{
    IAIMPMLGroupingPresetStandard* standartPreset;

    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    IAIMPString* aimpName = AimpConverter::ToAimpString(name);
    IAIMPString* aimpFieldName = AimpConverter::ToAimpString(name);

    AimpActionResult result =
        CheckResult(InternalAimpObject->Add3(aimpId, aimpName, 0, aimpFieldName, &standartPreset));

    aimpId->Release();
    aimpName->Release();
    aimpFieldName->Release();

    preset = nullptr;
    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPresetStandard(standartPreset);
    }

    return result;
}

AimpActionResult AimpGroupingPresets::Add(String^ id, String^ name, IAimpGroupingTreeDataProvider^ provider,
                                          IAimpGroupingPreset^% preset)
{
    preset = nullptr;

    // create internal wrapper for grouping provider
    _internalProvider = new InternalAimpGroupingTreeDataProvider(provider);
    IAIMPMLGroupingPreset* aimpPreset = nullptr;
    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    IAIMPString* aimpName = AimpConverter::ToAimpString(name);

    AimpActionResult result = CheckResult(InternalAimpObject->Add(aimpId, aimpName, 0, _internalProvider, &aimpPreset));

    aimpId->Release();
    aimpName->Release();

    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPreset(aimpPreset);
    }

    return result;
}

AimpActionResult AimpGroupingPresets::Add(String^ id, String^ name, Generic::IList<String^>^ fieldNames,
                                          IAimpGroupingPresetStandard^% preset)
{
    IAIMPObjectList* fields = AimpConverter::CreateAimpObject<IAIMPObjectList>(IID_IAIMPObjectList);

    for (int i = 0; i < fieldNames->Count; i++)
    {
        IAIMPString* s = AimpConverter::ToAimpString(fieldNames[i]);
        fields->Add(s);
        //AimpObjectDisposer::AddToBack(s);
        s->Release();
    }

    IAIMPMLGroupingPresetStandard* standartPreset;
    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    IAIMPString* aimpName = AimpConverter::ToAimpString(name);

    AimpActionResult result = CheckResult(InternalAimpObject->Add2(aimpId, aimpName, 0, fields, &standartPreset));
    preset = nullptr;

    aimpId->Release();
    aimpName->Release();

    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPresetStandard(standartPreset);
    }

    return result;
}

void AimpGroupingPresets::BeginUpdate()
{
    InternalAimpObject->BeginUpdate();
}

void AimpGroupingPresets::EndUpdate()
{
    InternalAimpObject->EndUpdate();
}

AimpActionResult AimpGroupingPresets::Delete(int index)
{
    return CheckResult(InternalAimpObject->Delete(index));
}

int AimpGroupingPresets::GetCount(void)
{
    return InternalAimpObject->GetCount();
}

AimpActionResult AimpGroupingPresets::Get(int index, IAimpGroupingPresetStandard^% preset)
{
    IAIMPMLGroupingPresetStandard* p = nullptr;
    preset = nullptr;
    AimpActionResult result = CheckResult(
        InternalAimpObject->Get(index, IID_IAIMPMLGroupingPresetStandard, reinterpret_cast<void**>(&p)));

    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPresetStandard(p);
    }

    return result;
}

AimpActionResult AimpGroupingPresets::Get(int index, IAimpGroupingPreset^% preset)
{
    IAIMPMLGroupingPreset* p = nullptr;
    preset = nullptr;

    AimpActionResult result = CheckResult(
        InternalAimpObject->Get(index, IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&p)));
    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPreset(p);
    }

    return result;
}

AimpActionResult AimpGroupingPresets::GetById(String^ id, IAimpGroupingPresetStandard^% preset)
{
    IAIMPMLGroupingPresetStandard* p = nullptr;
    preset = nullptr;

    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    AimpActionResult result = CheckResult(
        InternalAimpObject->GetByID(aimpId, IID_IAIMPMLGroupingPresetStandard, reinterpret_cast<void**>(&p)));
    aimpId->Release();

    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPresetStandard(p);
    }

    return result;
}

AimpActionResult AimpGroupingPresets::GetById(String^ id, IAimpGroupingPreset^% preset)
{
    IAIMPMLGroupingPreset* p = nullptr;
    preset = nullptr;

    IAIMPString* aimpId = AimpConverter::ToAimpString(id);
    AimpActionResult result = CheckResult(
        InternalAimpObject->GetByID(aimpId, IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&p)));
    aimpId->Release();

    if (result == AimpActionResult::OK)
    {
        preset = gcnew AimpGroupingPreset(p);
    }

    return result;
}
