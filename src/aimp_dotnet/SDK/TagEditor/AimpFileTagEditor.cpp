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
#include "AimpFileTagEditor.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "AimpFileTag.h"

using namespace AIMP::SDK;
using namespace AIMP::SDK::TagEditor;

AimpFileTagEditor::AimpFileTagEditor(IAIMPFileTagEditor* aimpObject) : AimpObject(aimpObject)
{ }

AimpActionResult AimpFileTagEditor::GetMixedInfo(IAimpFileInfo^% fileInfo)
{
    IAIMPFileInfo* aimpObject = nullptr;
    AimpActionResult result = CheckResult(InternalAimpObject->GetMixedInfo(&aimpObject));
    fileInfo = gcnew AimpFileInfo(aimpObject);
    return result;
}

AimpActionResult AimpFileTagEditor::GetTag(int index, IAimpFileTag^% fileTag)
{
    IAIMPFileTag* aimpTag = nullptr;
    AimpActionResult result = CheckResult(InternalAimpObject->GetTag(index, IID_IAIMPFileTag, (void**)&aimpTag));

    if (result == AimpActionResult::Ok && aimpTag != nullptr)
    {
        fileTag = gcnew AimpFileTag(aimpTag);
    }

    return result;
}

int AimpFileTagEditor::GetTagCount()
{
    return InternalAimpObject->GetTagCount();
}

AimpActionResult AimpFileTagEditor::SetToAll(IAimpFileInfo^ fileInfo)
{
    IAIMPFileInfo* fi = ((AimpFileInfo^)fileInfo)->InternalAimpObject;
    return CheckResult(InternalAimpObject->SetToAll(fi));
}

AimpActionResult AimpFileTagEditor::Save()
{
    return CheckResult(InternalAimpObject->Save());
}
