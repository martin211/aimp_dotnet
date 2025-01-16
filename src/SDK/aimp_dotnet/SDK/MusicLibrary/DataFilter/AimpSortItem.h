#pragma once
#include "SDK/Objects/AimpString.h"
using namespace MusicLibrary;

namespace AIMP {
    namespace SDK {
        private ref class AimpSortItem :
        public IAimpSortItem {
        private:
            SortDirectionType _sortDirection;;
            String^ _fieldName;
        public:
        AimpSortItem(IAIMPString* item) {
        }
        public:
            property String^ FieldName {
	            virtual String^ get() {
                    return _fieldName;
	            }
                virtual void set(String^ value) {
                    _fieldName = value;
	            }
            }

        property SortDirectionType SortDirection {
            virtual SortDirectionType get() {
                return _sortDirection;
            }
            virtual void set(SortDirectionType value) {
                _sortDirection = value;
            }
        }
    };
    }
}
