#include "Stdafx.h"
#include "AimpDataStorage.h"
#include "AimpGroupingPreset.h"

namespace AIMP
{
    namespace SDK
    {
        AimpDataStorage::!AimpDataStorage()
        {
            _aimpObject->Release();
        }

        AimpDataStorage::~AimpDataStorage()
        {
            this->!AimpDataStorage();
        }

        AimpActionResult AimpDataStorage::GetProperties(IAIMPPropertyList** properties)
        {
            IAIMPPropertyList *prop = NULL;
            AimpActionResult result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, (void**)&prop));
            *properties = prop;
            return result;
        }

        AimpDataStorage::AimpDataStorage(IAIMPMLDataStorage *aimpDataStorage) : AimpObject(aimpDataStorage)
        {
        }

        String ^AimpDataStorage::Id::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_ID);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }

            return String::Empty;
        }

        String ^AimpDataStorage::Caption::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_CAPTION);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }

            return String::Empty;
        }

        IAimpGroupingPreset ^AimpDataStorage::GroupingPreset::get()
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    IAIMPMLGroupingPreset *preset = NULL;
                    if (PropertyListExtension::GetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET, IID_IAIMPMLGroupingPreset, (void**)&preset) == AimpActionResult::Ok)
                    {
                        if (preset != NULL)
                            return gcnew AimpGroupingPreset(preset);
                    }
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }

            return nullptr;
        }

        void AimpDataStorage::GroupingPreset::set(IAimpGroupingPreset ^value)
        {
            IAIMPPropertyList *properties = NULL;
            try
            {
                if (GetProperties(&properties) == AimpActionResult::Ok)
                {
                    IAIMPMLGroupingPreset *preset = ((AimpGroupingPreset^)value)->InternalAimpObject;
                    PropertyListExtension::SetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET, preset);
                }
            }
            finally
            {
                if (properties != NULL)
                {
                    properties->Release();
                    properties = NULL;
                }
            }
        }
    }
}
