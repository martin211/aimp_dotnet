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
#include "AimpServiceFileTagEditor.h"
#include "AimpFileTagEditor.h"
#include "SDK/FileManager/AimpFileInfo.h"

using namespace AIMP::SDK;

AimpServiceFileTagEditor::AimpServiceFileTagEditor(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServiceFileTagEditor>(core)
{}

AimpActionResult AimpServiceFileTagEditor::EditFile(String^ filePath, IAimpFileTagEditor^% editor)
{
    IAIMPServiceFileTagEditor* service = nullptr;
    IAIMPString* str = AimpConverter::ToAimpString(filePath);
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceFileTagEditor, &service);
        if (result == AimpActionResult::Ok && service != nullptr)
        {
            IAIMPFileTagEditor* aimpEditor = nullptr;
            result = CheckResult(service->EditFile(str, IID_IAIMPFileTagEditor, (void**)&aimpEditor));

            if (result == AimpActionResult::Ok && aimpEditor != nullptr)
            {
                editor = gcnew AimpFileTagEditor(aimpEditor);
            }
        }

        return result;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceFileTagEditor::EditFile(IAimpStream^ fileStream, IAimpFileTagEditor^% editor)
{
    IAIMPServiceFileTagEditor* service = nullptr;
    IAIMPStream* stream = ((AimpStream^)fileStream)->InternalAimpObject;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceFileTagEditor, &service);
        if (result == AimpActionResult::Ok && service != nullptr)
        {
            IAIMPFileTagEditor* aimpEditor = nullptr;
            result = CheckResult(service->EditFile(stream, IID_IAIMPFileTagEditor, (void**)&aimpEditor));

            if (result == AimpActionResult::Ok && aimpEditor != nullptr)
            {
                editor = gcnew AimpFileTagEditor(aimpEditor);
            }
        }

        return result;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }
}

AimpActionResult AimpServiceFileTagEditor::EditTag(String^ filePath, TagType tag, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileTagEditor* service = nullptr;
    IAIMPString* str = AimpConverter::ToAimpString(filePath);
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceFileTagEditor, &service);
        if (result == AimpActionResult::Ok && service != nullptr)
        {
            IAIMPFileInfo* aimpFileInfo = nullptr;
            result = CheckResult(service->EditTag(str, (int)tag, IID_IAIMPFileInfo, (void**)&aimpFileInfo));

            if (result == AimpActionResult::Ok && aimpFileInfo != nullptr)
            {
                fileInfo = gcnew AimpFileInfo(aimpFileInfo);
            }
        }

        return result;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }
}

AimpActionResult AimpServiceFileTagEditor::EditTag(IAimpStream^ fileStream, TagType tag, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileTagEditor* service = nullptr;
    IAIMPStream* stream = ((AimpStream^)fileStream)->InternalAimpObject;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceFileTagEditor, &service);
        if (result == AimpActionResult::Ok && service != nullptr)
        {
            IAIMPFileInfo* aimpFileInfo = nullptr;
            result = CheckResult(service->EditTag(stream, (int)tag, IID_IAIMPFileInfo, (void**)&aimpFileInfo));

            if (result == AimpActionResult::Ok && aimpFileInfo != nullptr)
            {
                fileInfo = gcnew AimpFileInfo(aimpFileInfo);
            }
        }

        return result;
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }
}
