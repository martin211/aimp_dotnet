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
#include "AimpFileTag.h"

using namespace AIMP::SDK;

AimpFileTag::AimpFileTag(IAIMPFileTag* aimpObject) : AimpFileInfo(aimpObject)
{
    _fileTag = aimpObject;
}

TagType AimpFileTag::TagId::get()
{
    return (TagType)PropertyListExtension::GetInt32(_aimpObject, AIMP_FILETAG_PROPID_TAG_ID);
}

void AimpFileTag::TagId::set(TagType value)
{
    PropertyListExtension::SetInt32(_aimpObject, AIMP_FILETAG_PROPID_TAG_ID, (int)value);
}

bool AimpFileTag::DeleteOnSaving::get()
{
    return PropertyListExtension::GetBool(_aimpObject, AIMP_FILETAG_PROPID_DELETE_ON_SAVING);
}

void AimpFileTag::DeleteOnSaving::set(bool value)
{
    PropertyListExtension::SetBool(_aimpObject, AIMP_FILETAG_PROPID_DELETE_ON_SAVING, value);
}
