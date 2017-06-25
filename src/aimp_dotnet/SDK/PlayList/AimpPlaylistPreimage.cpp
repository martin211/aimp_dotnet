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
#include "AimpPlaylistPreimage.h"

using namespace AIMP::SDK;

AimpPlaylistPreimage::AimpPlaylistPreimage(IAIMPPlaylistPreimage* aimpObject) : AimpObject(aimpObject)
{}

String^ AimpPlaylistPreimage::FactoryId::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_FACTORYID);
}

bool AimpPlaylistPreimage::AutoSync::get()
{
    return PropertyListExtension::GetBool(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC);
}

void AimpPlaylistPreimage::AutoSync::set(bool value)
{
    PropertyListExtension::SetBool(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC, value);
}

bool AimpPlaylistPreimage::AutoSyncOnStartup::get()
{
    return PropertyListExtension::GetBool(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP);
}

void AimpPlaylistPreimage::AutoSyncOnStartup::set(bool value)
{
    PropertyListExtension::SetBool(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP, value);
}

bool AimpPlaylistPreimage::HasDialog::get()
{
    return PropertyListExtension::GetBool(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG);
}

void AimpPlaylistPreimage::HasDialog::set(bool value)
{
    PropertyListExtension::SetBool(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG, value);
}

String^ AimpPlaylistPreimage::SortTemplate::get()
{
    return PropertyListExtension::GetString(_aimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_SORTTEMPLATE);
}

AimpActionResult AimpPlaylistPreimage::ConfigLoad(IAimpStream^ stream)
{
    return AimpActionResult::Unexpected;
}

AimpActionResult AimpPlaylistPreimage::ConfigSave(IAimpStream^ stream)
{
    return AimpActionResult::Unexpected;
}

AimpActionResult AimpPlaylistPreimage::ExecuteDialog(IntPtr ownerHandle)
{
    //_aimpObject->ExecuteDialog()
    return AimpActionResult::Unexpected;
}

void AimpPlaylistPreimage::Initialize(IAimpPlaylistPreimageListener^ listener)
{
    
}

void AimpPlaylistPreimage::FinalizeObject()
{
    _aimpObject->Finalize();
}
