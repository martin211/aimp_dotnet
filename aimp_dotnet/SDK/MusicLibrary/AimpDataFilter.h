#pragma once
#include "AimpDataFilterGroup.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary;

        public ref class AimpDataFilter :
            public AimpDataFilterGroup,
            public IAimpDataFilter
        {
        public:
            explicit AimpDataFilter(IAIMPMLDataFilter* native) : AimpDataFilterGroup(native)
            {}

            virtual property int Offset
            {
                int get()
                {
                    return PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_OFFSET);
                }

                void set(int value)
                {
                    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_OFFSET, value);
                }
            }

            virtual property int Limit
            {
                int get()
                {
                    return PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_LIMIT);
                }

                void set(int value)
                {
                    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_LIMIT, value);
                }
            }

            virtual property String^ SortBy
            {
                String^ get()
                {
                    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FILTER_SORTBY);
                }

                void set(String^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FILTER_SORTBY, value);
                }
            }

            virtual property SortDirectionType SortDirection
            {
                SortDirectionType get()
                {
                    return (SortDirectionType)PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_SORTDIRECTION);
                }

                void set(SortDirectionType value)
                {
                    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_SORTDIRECTION, (int)value);
                }
            }

            virtual property String^ SearchString
            {
                String^ get()
                {
                    return PropertyListExtension::GetString(InternalAimpObject, AIMPML_FILTER_SEARCHSTRING);
                }

                void set(String^ value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMPML_FILTER_SEARCHSTRING, value);
                }
            }

            virtual property int AlphaBeticIndex
            {
                int get()
                {
                    return PropertyListExtension::GetInt32(InternalAimpObject, AIMPML_FILTER_ALPHABETICINDEX);
                }

                void set(int value)
                {
                    PropertyListExtension::SetInt32(InternalAimpObject, AIMPML_FILTER_ALPHABETICINDEX, value);
                }
            }

            virtual AimpActionResult Assign(IAimpDataFieldFilter^ source)
            {
                return AimpActionResult::NotImplemented;
            }

            virtual AimpActionResult Clone(IAimpDataFilter^% source)
            {
                source = nullptr;
                return AimpActionResult::NotImplemented;
            }
        };
    }
}
