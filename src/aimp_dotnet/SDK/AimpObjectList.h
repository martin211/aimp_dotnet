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

#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;

        generic<class TObject>
        public ref class AimpObjectList :
            public IAimpObjectList<TObject>
        {
        private:
            IAIMPObjectList* _nativeObject;

        public:
            AimpObjectList(IAIMPObjectList* nativeObject);

            virtual AimpActionResult Add(TObject entry);

            virtual AimpActionResult Clear();

            virtual AimpActionResult Delete(int index);

            virtual AimpActionResult Insert(int index, TObject entry);

            virtual property int Count
            { 
                int get();
            }

            virtual AimpActionResult GetObject(int index, TObject% item);

            virtual AimpActionResult SetObject(int index, TObject item);
        };

        public ref class AimpObjectList2 : public IAimpObjectList, public AimpObject<IAIMPObjectList>
        {
        public:
            explicit AimpObjectList2(IAIMPObjectList* nativeObject) : AimpObject(nativeObject)
            {}

            virtual AimpActionResult Add(Object^ entry)
            {
                String^ s = dynamic_cast<String^>(entry);
                if (s != nullptr)
                {
                    return Utils::CheckResult(InternalAimpObject->Add(AimpConverter::ToAimpString(s)));
                }

                return Utils::CheckResult(InternalAimpObject->Add(AimpConverter::ToAimpString((String^)entry)));
            }

            virtual AimpActionResult Clear()
            {
                return AimpActionResult::Fail;
            }

            virtual AimpActionResult Delete(int index)
            {
                return AimpActionResult::Fail;
            }

            virtual AimpActionResult Insert(int index, Object^ entry)
            {
                return AimpActionResult::Fail;
            }

            virtual property int Count
            {
                int get()
                {
                    return 0;
                }
            }

            virtual AimpActionResult GetObject(int index, Object^% item)
            {
                return AimpActionResult::Fail;
            }

            virtual AimpActionResult SetObject(int index, Object^ item)
            {
                return AimpActionResult::Fail;
            }
        };
    }
}
