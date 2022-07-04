#pragma once
#include "AimpDataStorage.h"
#include "Presets/AimpGroupingPreset.h"

namespace AIMP {
    namespace SDK {

        using namespace MusicLibrary::DataStorage;

        //template <class TStorage>
        //public ref class BaseDataStorage : public AimpObject<TStorage*> {
        //private:
        //    ActionResultType GetProperties(IAIMPPropertyList** properties) {
        //        //IAIMPPropertyList* prop = nullptr;
        //        //const auto result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop)));
        //        //*properties = prop;
        //        //return result;
        //        return ActionResultType::Fail;
        //    }
        ////protected:
        ////    TStorage* _storage;
        //public:
        //    BaseDataStorage(TStorage* storage) {
        //        //_storage = storage;
        //    }

        //    virtual property String^ Id
        //    {
        //        String^ get() {
        //            IAIMPPropertyList* properties = nullptr;
        //            try {
        //                if (GetProperties(&properties) == ActionResultType::OK) {
        //                    return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_ID);
        //                }
        //            }
        //            finally {
        //                if (properties != nullptr) {
        //                    properties->Release();
        //                    properties = nullptr;
        //                }
        //            }

        //            return String::Empty;
        //        }
        //    }

        //    virtual property String^ Caption
        //    {
        //        String^ get() {
        //            IAIMPPropertyList* properties = nullptr;
        //            try {
        //                if (GetProperties(&properties) == ActionResultType::OK) {
        //                    return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_CAPTION);
        //                }
        //            }
        //            finally {
        //                if (properties != nullptr) {
        //                    properties->Release();
        //                    properties = nullptr;
        //                }
        //            }

        //            return String::Empty;
        //        }
        //    }

        //    virtual property IAimpGroupingPreset^ GroupingPreset
        //    {
        //        IAimpGroupingPreset^ get() {
        //            IAIMPPropertyList* properties = nullptr;
        //            try {
        //                if (GetProperties(&properties) == ActionResultType::OK) {
        //                    IAIMPMLGroupingPreset* preset = nullptr;
        //                    if (PropertyListExtension::GetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET,
        //                        IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&preset)) ==
        //                        ActionResultType::OK) {
        //                        if (preset != nullptr) {
        //                            return gcnew AimpGroupingPreset(preset);
        //                        }
        //                    }
        //                }
        //            }
        //            finally {
        //                if (properties != nullptr) {
        //                    properties->Release();
        //                    properties = nullptr;
        //                }
        //            }

        //            return nullptr;
        //        }
        //        void set(IAimpGroupingPreset^ value) {
        //            IAIMPPropertyList* properties = nullptr;
        //            try {
        //                if (GetProperties(&properties) == ActionResultType::OK) {
        //                    IAIMPMLGroupingPreset* preset = static_cast<AimpGroupingPreset^>(value)->InternalAimpObject;
        //                    PropertyListExtension::SetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET, preset);
        //                }
        //            }
        //            finally {
        //                if (properties != nullptr) {
        //                    properties->Release();
        //                    properties = nullptr;
        //                }
        //            }
        //        }
        //    }
        //};


        //public ref class AimpDataStorage2 :  public IAimpDataStorage2 {

        //public:
        //    explicit AimpDataStorage2(IAIMPMLDataStorage2* aimpObject);

        //    virtual AimpActionResult<Object^>^ CreateObject();

        //private:
        //    ActionResultType GetProperties(IAIMPPropertyList** properties);
        //};
    }
}
