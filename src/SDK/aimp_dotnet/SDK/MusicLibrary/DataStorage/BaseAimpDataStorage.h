#pragma once
#include "SDK/MusicLibrary/Presets/AimpGroupingPreset.h"

namespace AIMP {
    namespace SDK {

        using namespace MusicLibrary::Presets;

        template <class T>
        public ref class BaseAimpDataStorage : public AimpObject<T> {
        public:
            explicit BaseAimpDataStorage(T* obj) : AimpObject(obj) {}

            virtual property String^ Id
            {
                String^ get() {
                    IAIMPPropertyList* properties = nullptr;
                    try {
                        if (GetProperties(&properties) == ActionResultType::OK) {
                            try {
                                return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_ID);
                            }
                            catch (AimpActionException^) {
                                return String::Empty;
                            }
                        }
                    }
                    finally {
                        RELEASE(properties)
                    }

                    return String::Empty;
                }
            }

            virtual property String^ Caption
            {
                String^ get() {
                    IAIMPPropertyList* properties = nullptr;
                    try {
                        if (GetProperties(&properties) == ActionResultType::OK) {
                            return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_CAPTION);
                        }
                    }
                    finally {
                        RELEASE(properties)
                    }

                    return String::Empty;
                }
            }

            virtual property IAimpGroupingPreset^ GroupingPreset
            {
                IAimpGroupingPreset^ get() {
                    IAIMPPropertyList* properties = nullptr;
                    try {
                        if (GetProperties(&properties) == ActionResultType::OK) {
                            IAIMPMLGroupingPreset* preset = nullptr;
                            if (PropertyListExtension::GetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET,
                                IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&preset)) ==
                                ActionResultType::OK) {
                                if (preset != nullptr) {
                                    return gcnew AimpGroupingPreset(preset);
                                }
                            }
                        }
                    }
                    finally {
                        RELEASE(properties)
                    }

                    return nullptr;
                }
                void set(IAimpGroupingPreset^ value) {
                    IAIMPPropertyList* properties = nullptr;
                    try {
                        if (GetProperties(&properties) == ActionResultType::OK) {
                            IAIMPMLGroupingPreset* preset = static_cast<AimpGroupingPreset^>(value)->InternalAimpObject;
                            PropertyListExtension::SetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET, preset);
                        }
                    }
                    finally {
                        RELEASE(properties)
                    }
                }
            }
        private:
            ActionResultType GetProperties(IAIMPPropertyList** properties) {
                IAIMPPropertyList* prop = nullptr;
                const auto result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop)));
                *properties = prop;
                return result;
            }
        };
    }
}

