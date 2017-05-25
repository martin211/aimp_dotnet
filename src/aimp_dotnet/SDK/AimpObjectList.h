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
    }
}
