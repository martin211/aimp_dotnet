#include "Stdafx.h"
#include "AimpTaskOwner.h"

using namespace AIMP::SDK;

AimpTaskOwner::AimpTaskOwner(IAIMPTaskOwner *taskOwner) : AimpObject(taskOwner)
{}

bool AimpTaskOwner::IsCanceled::get()
{
    return InternalAimpObject->IsCanceled();
}
