//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "InternalOrderedListItem.h"

namespace AIMP {
    namespace SDK {
        namespace Collections {
            public ref class OrderedListItem : public IAimpOrderedItem {
            private:
                InternalOrderedListItem* _item = nullptr;

            public:
                OrderedListItem(String^ name, MusicLibrary::SortDirectionType sortDirection);

                ~OrderedListItem();

                property MusicLibrary::SortDirectionType Value {
                    virtual MusicLibrary::SortDirectionType get();
                    virtual void set(MusicLibrary::SortDirectionType value);
                }

                property IAimpString^ Name {
                    virtual IAimpString^ get();
                }

                property IUnknown* InternalAimpObject {
                    virtual IUnknown* get();
                }
            };
        }
    }
}
