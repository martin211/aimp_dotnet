//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpPlaylistPreimage.h"

using namespace AIMP::SDK;

AimpPlaylistPreimage::AimpPlaylistPreimage(IAIMPPlaylistPreimage* aimpObject) : AimpObject(aimpObject) {
}

String^ AimpPlaylistPreimage::FactoryId::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_FACTORYID);
}

bool AimpPlaylistPreimage::AutoSync::get() {
    int value = PropertyListExtension::GetInt32(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC);
    return value > 0;

    //return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC);
}

void AimpPlaylistPreimage::AutoSync::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC, value);
}

bool AimpPlaylistPreimage::AutoSyncOnStartup::get() {
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP);
}

void AimpPlaylistPreimage::AutoSyncOnStartup::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_AUTOSYNC_ON_STARTUP, value);
}

bool AimpPlaylistPreimage::HasDialog::get() {
    return PropertyListExtension::GetBool(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG);
}

void AimpPlaylistPreimage::HasDialog::set(bool value) {
    PropertyListExtension::SetBool(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_HASDIALOG, value);
}

String^ AimpPlaylistPreimage::SortTemplate::get() {
    return PropertyListExtension::GetString(InternalAimpObject, AIMP_PLAYLISTPREIMAGE_PROPID_SORTTEMPLATE);
}

ActionResult AimpPlaylistPreimage::ConfigLoad(IAimpStream^ stream) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->ConfigLoad(((AimpStream^)stream)->InternalAimpObject)));
}

ActionResult AimpPlaylistPreimage::ConfigSave(IAimpStream^ stream) {
    return ACTION_RESULT(CheckResult(InternalAimpObject->ConfigSave(((AimpStream^)stream)->InternalAimpObject)));
}

ActionResult AimpPlaylistPreimage::ExecuteDialog(IntPtr ownerHandle) {
    //InternalAimpObject->ExecuteDialog()
    return ACTION_RESULT(ActionResultType::NotImplemented);
}

void AimpPlaylistPreimage::Initialize(IAimpPlaylistPreimageListener^ listener) {
}

void AimpPlaylistPreimage::FinalizeObject() {
    InternalAimpObject->Finalize();
}
