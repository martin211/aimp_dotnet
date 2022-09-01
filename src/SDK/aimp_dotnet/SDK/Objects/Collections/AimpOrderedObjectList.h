//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        namespace Collections {
            public ref class AimpOrderedObjectList : public AimpObject<IAIMPObjectList>, public IAimpOrderedObjectList {
            public:
                explicit AimpOrderedObjectList(IAIMPObjectList* list);
                virtual IAimpOrderedItem^ Create(String^ name, MusicLibrary::SortDirectionType sortDirection);
                virtual AimpActionResult^ Add(IAimpOrderedItem^ entry);
                virtual AimpActionResult^ Insert(int index, IAimpOrderedItem^ item);
                virtual AimpActionResult^ GetObject(int index, IAimpOrderedItem^% item);
                virtual AimpActionResult^ SetObject(int index, IAimpOrderedItem^ item);
                property int Count { virtual int get(); }
                virtual AimpActionResult^ Clear();
                virtual AimpActionResult^ Delete(int index);
            //private:
            //    System::Collections::Generic::IList<IAimpOrderedItem^>^ _items;
            };
        }
    }
}
