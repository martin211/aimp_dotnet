#include "Stdafx.h"
#include "AimpVirtualFile.h"


using namespace AIMP::SDK;

AimpVirtualFile::AimpVirtualFile(IAIMPVirtualFile *aimpObject) : AimpObject(aimpObject)
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

System::String^ AimpVirtualFile::AudioSourceFile::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE);
}

void AimpVirtualFile::AudioSourceFile::set(System::String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE, value);
}

System::String^ AimpVirtualFile::FileFormat::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT);
}

void AimpVirtualFile::FileFormat::set(System::String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEFORMAT, value);
}

System::String^ AimpVirtualFile::FileUri::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI);
}

void AimpVirtualFile::FileUri::set(System::String^ value)
{
    PropertyListExtension::SetString(_aimpObject, AIMP_VIRTUALFILE_PROPID_FILEURI, value);
}

AimpActionResult AimpVirtualFile::CreateStream(System::IO::Stream ^%stream)
{
    stream = nullptr;
    return AimpActionResult::Ok;
}

AimpActionResult AimpVirtualFile::GetFileInfo(IAimpFileInfo ^%fileInfo)
{
    IAIMPFileInfo *fi = NULL;
    AimpActionResult result = CheckResult(_aimpObject->GetFileInfo(fi));
    if (result == AimpActionResult::Ok)
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
