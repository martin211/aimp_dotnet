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
#include "AimpVirtualFile.h"
#include "AimpFileInfo.h"

using namespace AIMP::SDK;

AimpVirtualFile::AimpVirtualFile(IAIMPVirtualFile* aimpObject) : AimpObject(aimpObject)
{
}

int AimpVirtualFile::IndexInSet::get()
{
    return PropertyListExtension::GetInt32(_aimpObject, AIMP_VIRTUALFILE_PROPID_INDEXINSET);
}

void AimpVirtualFile::IndexInSet::set(int value)
{
    PropertyListExtension::SetInt32(_aimpObject, AIMP_VIRTUALFILE_PROPID_INDEXINSET, value);
}

double AimpVirtualFile::ClipStart::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPSTART);
}

void AimpVirtualFile::ClipStart::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPSTART, value);
}

double AimpVirtualFile::ClipFinish::get()
{
    return PropertyListExtension::GetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPFINISH);
}

void AimpVirtualFile::ClipFinish::set(double value)
{
    PropertyListExtension::SetFloat(_aimpObject, AIMP_VIRTUALFILE_PROPID_CLIPFINISH, value);
}

String^ AimpVirtualFile::AudioSourceFile::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE);
}

void AimpVirtualFile::AudioSourceFile::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE, value);
}

String^ AimpVirtualFile::FileFormat::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT);
}

void AimpVirtualFile::FileFormat::set(System::String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT, value);
}

String^ AimpVirtualFile::FileUri::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI);
}

void AimpVirtualFile::FileUri::set(String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI, value);
}

AimpActionResult AimpVirtualFile::CreateStream(IO::Stream^% stream)
{
    // TODO Complete it
    stream = nullptr;
    return AimpActionResult::OK;
}

AimpActionResult AimpVirtualFile::GetFileInfo(IAimpFileInfo^% fileInfo)
{
    IAIMPFileInfo *fi = nullptr;
    fileInfo = nullptr;
    AimpActionResult result = CheckResult(_aimpObject->GetFileInfo(fi));

    if (result == AimpActionResult::OK && fi != nullptr)
    {
        fileInfo = gcnew AimpFileInfo(fi);
    }

    return result;
}

bool AimpVirtualFile::IsExists()
{
    return _aimpObject->IsExists();
}

AimpActionResult AimpVirtualFile::IsInSameStream(IAimpVirtualFile ^virtualFile)
{
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpVirtualFile::Synchronize()
{
    return CheckResult(_aimpObject->Synchronize());
}
