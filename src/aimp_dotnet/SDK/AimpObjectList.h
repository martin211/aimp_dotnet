// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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

        generic <class TObject>
        public ref class AimpObjectList :
            public IAimpObjectList<TObject>
        {
        private:
            IAIMPObjectList* _nativeObject;

        public:
            AimpObjectList(IAIMPObjectList* nativeObject);

            virtual ActionResultType Add(TObject entry);

            virtual ActionResultType Clear();

            virtual ActionResultType Delete(int index);

            virtual ActionResultType Insert(int index, TObject entry);

            virtual property int Count
            {
                int get();
            }

            virtual ActionResultType GetObject(int index, TObject% item);

            virtual ActionResultType SetObject(int index, TObject item);
        };

        public ref class AimpObjectList2 : public IAimpObjectList, public AimpObject<IAIMPObjectList>
        {
        public:
            explicit AimpObjectList2(IAIMPObjectList* nativeObject) : AimpObject(nativeObject)
            {
            }

            virtual ActionResultType Add(Object^ entry)
            {
                String^ s = dynamic_cast<String^>(entry);
                if (s != nullptr)
                {
                    return Utils::CheckResult(InternalAimpObject->Add(AimpConverter::ToAimpString(s)));
                }

                return Utils::CheckResult(InternalAimpObject->Add(AimpConverter::ToAimpString((String^)entry)));
            }

            virtual ActionResultType Clear()
            {
                return ActionResultType::Fail;
            }

            virtual ActionResultType Delete(int index)
            {
                return ActionResultType::Fail;
            }

            virtual ActionResultType Insert(int index, Object^ entry)
            {
                return ActionResultType::Fail;
            }

            virtual property int Count
            {
                int get()
                {
                    return 0;
                }
            }

            virtual ActionResultType GetObject(int index, Object^% item)
            {
                return ActionResultType::Fail;
            }

            virtual ActionResultType SetObject(int index, Object^ item)
            {
                return ActionResultType::Fail;
            }
        };
    }
}
