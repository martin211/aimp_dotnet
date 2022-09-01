//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileTagEditor.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "AimpFileTag.h"

using namespace AIMP::SDK;
using namespace TagEditor;

AimpFileTagEditor::AimpFileTagEditor(IAIMPFileTagEditor* aimpObject) : AimpObject(aimpObject) {
}

TYPED_RESULT(IAimpFileInfo) AimpFileTagEditor::GetMixedInfo() {
    AimpFileInfo^ fileInfo = nullptr;
    IAIMPFileInfo* aimpObject = nullptr;
    ActionResultType result = CheckResult(InternalAimpObject->GetMixedInfo(&aimpObject));
    if (result == ActionResultType::OK) {
        fileInfo = gcnew AimpFileInfo(aimpObject);
    }

    return RETURN_TYPED_RESULT(IAimpFileInfo, result, fileInfo);
}

TYPED_RESULT(IAimpFileTag) AimpFileTagEditor::GetTag(int index) {
    AimpFileTag^ fileTag = nullptr;
    IAIMPFileTag* aimpTag = nullptr;
    ActionResultType result = CheckResult(
        InternalAimpObject->GetTag(index, IID_IAIMPFileTag, reinterpret_cast<void**>(&aimpTag)));

    if (result == ActionResultType::OK && aimpTag != nullptr) {
        fileTag = gcnew AimpFileTag(aimpTag);
    }

    return RETURN_TYPED_RESULT(IAimpFileTag, result, fileTag);
}

int AimpFileTagEditor::GetTagCount() {
    return InternalAimpObject->GetTagCount();
}

ActionResult AimpFileTagEditor::SetToAll(IAimpFileInfo^ fileInfo) {
    IAIMPFileInfo* fi = static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject;
    return ACTION_RESULT(CheckResult(InternalAimpObject->SetToAll(fi)));
}

ActionResult AimpFileTagEditor::Save() {
    return ACTION_RESULT(CheckResult(InternalAimpObject->Save()));
}
