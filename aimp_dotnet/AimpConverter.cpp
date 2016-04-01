#include "AimpConverter.h"

namespace AIMP
{
    template<typename TAimpNativeObject>
    TAimpNativeObject AimpConverter::GetObject(REFIID objectId)
    {
        TAimpNativeObject *object = NULL;

        if (AIMP::SDK::ManagedAimpCore::GetAimpCore()->CreateObject(objectId, (void**)&object) == S_OK)
        {
            return object;
        }

        return NULL;
    }
}
