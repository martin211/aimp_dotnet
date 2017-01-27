/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
