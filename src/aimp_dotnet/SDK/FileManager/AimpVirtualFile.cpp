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
#include "AimpVirtualFile.h"
#include "AimpFileInfo.h"

using namespace AIMP::SDK;

AimpVirtualFile::AimpVirtualFile(IAIMPVirtualFile* aimpObject) : AimpObject(aimpObject)
{
}

int AimpVirtualFile::IndexInSet::get()
{
    return PropertyListExtension::GetInt32(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_INDEXINSET);
}

void AimpVirtualFile::IndexInSet::set(int value)
{
    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_INDEXINSET, value);
}

double AimpVirtualFile::ClipStart::get()
{
    return PropertyListExtension::GetFloat(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_CLIPSTART);
}

void AimpVirtualFile::ClipStart::set(double value)
{
    PropertyListExtension::SetFloat(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_CLIPSTART, value);
}

double AimpVirtualFile::ClipFinish::get()
{
    return PropertyListExtension::GetFloat(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_CLIPFINISH);
}

void AimpVirtualFile::ClipFinish::set(double value)
{
    PropertyListExtension::SetFloat(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_CLIPFINISH, value);
}

String^ AimpVirtualFile::AudioSourceFile::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE);
}

void AimpVirtualFile::AudioSourceFile::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE, value);
}

String^ AimpVirtualFile::FileFormat::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT);
}

void AimpVirtualFile::FileFormat::set(System::String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT, value);
}

String^ AimpVirtualFile::FileUri::get()
{
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI);
}

void AimpVirtualFile::FileUri::set(String^ value)
{
    PropertyListExtension::SetString(InternalAimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI, value);
}

ActionResultType AimpVirtualFile::CreateStream(IAimpStream^% stream)
{
    stream = nullptr;
    IAIMPStream* aimpStream = nullptr;

    const auto result = CheckResult(InternalAimpObject->CreateStream(&aimpStream));
    if (result == ActionResultType::OK && aimpStream != nullptr)
    {
        stream = gcnew AimpStream(aimpStream);
    }

    return result;
}

ActionResultType AimpVirtualFile::GetFileInfo(IAimpFileInfo^% fileInfo)
{
    IAIMPFileInfo* fi = nullptr;
    fileInfo = nullptr;
    const auto result = CheckResult(InternalAimpObject->GetFileInfo(fi));

    if (result == ActionResultType::OK && fi != nullptr)
    {
        fileInfo = gcnew AimpFileInfo(fi);
    }

    return result;
}

bool AimpVirtualFile::IsExists()
{
    return InternalAimpObject->IsExists();
}

ActionResultType AimpVirtualFile::IsInSameStream(IAimpVirtualFile^ virtualFile)
{
    return CheckResult(InternalAimpObject->IsInSameStream(static_cast<AimpVirtualFile^>(virtualFile)->InternalAimpObject));
}

ActionResultType AimpVirtualFile::Synchronize()
{
    return CheckResult(InternalAimpObject->Synchronize());
}
