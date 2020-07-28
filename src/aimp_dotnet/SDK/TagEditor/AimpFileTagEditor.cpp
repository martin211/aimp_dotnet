// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileTagEditor.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "AimpFileTag.h"

using namespace AIMP::SDK;
using namespace TagEditor;

AimpFileTagEditor::AimpFileTagEditor(IAIMPFileTagEditor* aimpObject) : AimpObject(aimpObject) {
}

ActionResultType AimpFileTagEditor::GetMixedInfo(IAimpFileInfo^% fileInfo) {
    IAIMPFileInfo* aimpObject = nullptr;
    ActionResultType result = CheckResult(InternalAimpObject->GetMixedInfo(&aimpObject));
    fileInfo = gcnew AimpFileInfo(aimpObject);
    return result;
}

ActionResultType AimpFileTagEditor::GetTag(int index, IAimpFileTag^% fileTag) {
    IAIMPFileTag* aimpTag = nullptr;
    ActionResultType result = CheckResult(
        InternalAimpObject->GetTag(index, IID_IAIMPFileTag, reinterpret_cast<void**>(&aimpTag)));

    if (result == ActionResultType::OK && aimpTag != nullptr) {
        fileTag = gcnew AimpFileTag(aimpTag);
    }

    return result;
}

int AimpFileTagEditor::GetTagCount() {
    return InternalAimpObject->GetTagCount();
}

ActionResultType AimpFileTagEditor::SetToAll(IAimpFileInfo^ fileInfo) {
    IAIMPFileInfo* fi = static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject;
    return CheckResult(InternalAimpObject->SetToAll(fi));
}

ActionResultType AimpFileTagEditor::Save() {
    return CheckResult(InternalAimpObject->Save());
}
