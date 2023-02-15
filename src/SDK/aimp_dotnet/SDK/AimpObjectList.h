//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace AIMP::SDK;

        generic <class TObject>
        public ref class AimpObjectList :
            public AimpObject<IAIMPObjectList>,
            public IAimpObjectList<TObject> {
        protected:
            IAIMPObjectList* _nativeObject;

        public:
            property IAIMPObjectList* AimpObject {
                IAIMPObjectList* get();
            }

            explicit AimpObjectList(IAIMPObjectList* nativeObject);

            virtual ActionResult Add(TObject entry);

            virtual ActionResult Clear();

            virtual ActionResult Delete(int index);

            virtual ActionResult Insert(int index, TObject entry);

            virtual property int Count
            {
                int get();
            }

            virtual ActionResult GetObject(int index, TObject% item);

            virtual ActionResult SetObject(int index, TObject item);

            virtual Collections::IEnumerator^ GetEnumerator();
        };

        public ref class AimpObjectList2 : public IAimpObjectList, public AimpObject<IAIMPObjectList> {
        public:
            explicit AimpObjectList2(IAIMPObjectList* nativeObject) : AimpObject(nativeObject) {
            }

            virtual ActionResult Add(Object^ entry) {
                String^ s = dynamic_cast<String^>(entry);
                if (s != nullptr) {
                    return ACTION_RESULT(Utils::CheckResult(InternalAimpObject->Add(AimpConverter::ToAimpString(s))));
                }

                return ACTION_RESULT(
                    Utils::CheckResult(InternalAimpObject->Add(AimpConverter::ToAimpString((String^)entry))));
            }

            virtual ActionResult Clear() {
                return ACTION_RESULT(ActionResultType::Fail);
            }

            virtual ActionResult Delete(int index) {
                return ACTION_RESULT(ActionResultType::Fail);
            }

            virtual ActionResult Insert(int index, Object^ entry) {
                return ACTION_RESULT(ActionResultType::Fail);
            }

            virtual property int Count
            {
                int get() {
                    return 0;
                }
            }

            virtual ActionResult GetObject(int index, Object^% item) {
                return ACTION_RESULT(ActionResultType::Fail);
            }

            virtual ActionResult SetObject(int index, Object^ item) {
                return ACTION_RESULT(ActionResultType::Fail);
            }
        };
    }
}
