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
