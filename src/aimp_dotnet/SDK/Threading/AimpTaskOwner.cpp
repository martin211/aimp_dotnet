// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpTaskOwner.h"

using namespace AIMP::SDK;

AimpTaskOwner::AimpTaskOwner(IAIMPTaskOwner* taskOwner) : AimpObject(taskOwner)
{
}

bool AimpTaskOwner::IsCanceled::get()
{
    return InternalAimpObject->IsCanceled();
}
