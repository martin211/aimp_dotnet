#include "AimpDataStorage.h"

namespace AIMP
{
    namespace SDK
    {
        AimpActionResult AimpDataStorage::GetProperties(IAIMPPropertyList** properties)
        {
            IAIMPPropertyList *prop = NULL;
            AimpActionResult result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&prop));
            *properties = prop;
            return result;
        }

        AimpDataStorage::AimpDataStorage(IAIMPMLDataStorage *aimpDataStorage)
        {
        }

        String ^AimpDataStorage::Id::get()
        {
            
        }

        String ^AimpDataStorage::Caption::get()
        {
            
        }

        IAimpGroupingPreset ^AimpDataStorage::GroupingPreset::get()
        {
            
        }

        void AimpDataStorage::GroupingPreset::set(IAimpGroupingPreset ^value)
        {
            
        }
    }
}
