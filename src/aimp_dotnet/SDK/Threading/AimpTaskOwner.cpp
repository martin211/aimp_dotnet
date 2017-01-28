/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpTaskOwner.h"

using namespace AIMP::SDK;

AimpTaskOwner::AimpTaskOwner(IAIMPTaskOwner *taskOwner) : AimpObject(taskOwner)
{}

bool AimpTaskOwner::IsCanceled::get()
{
    return InternalAimpObject->IsCanceled();
}
