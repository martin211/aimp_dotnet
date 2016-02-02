#pragma once
#include "AimpUIControl.h"
#include "..\..\AimpConverter.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Form;
        using namespace AIMP::SDK::GUI::Controls::Events;

        public ref class AimpUILabel : public AimpUIControl, public IAimpUILabel
        {
        public:
            property virtual bool AutoSize
            {
                bool get()
                {
                    return AimpConverter::GetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_AUTOSIZE);
                }

                void set(bool value)
                {
                    AimpConverter::SetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_AUTOSIZE, value);
                }
            }

            property virtual bool ShowLine
            {
                bool get()
                {
                    return AimpConverter::GetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_LINE);
                }

                void set(bool value)
                {
                    AimpConverter::SetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_LINE, value);
                }
            }

            property virtual String ^Text
            {
                String ^get()
                {
                    return AimpConverter::GetString(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXT);
                }

                void set(String ^value)
                {
                    AimpConverter::SetString(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXT, value);
                }
            }

            property virtual AimpTextAlign ^TextAlign
            {
                AimpTextAlign ^get()
                {
                    return (AimpTextAlign)AimpConverter::GetInt32(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXTALIGN);
                }

                void set(AimpTextAlign ^value)
                {
                    AimpConverter::SetInt32(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXTALIGN, (int)value);
                }
            }

            property virtual AimpVerticalTextAlign ^VerticalTextAlign
            {
                AimpVerticalTextAlign ^get()
                {
                    return (AimpVerticalTextAlign)AimpConverter::GetInt32(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXTALIGNVERT);
                }

                void set(AimpVerticalTextAlign ^value)
                {
                    AimpConverter::SetInt32(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXTALIGNVERT, (int)value);
                }
            }

            property virtual Color ^TextColor
            {
                Color ^get()
                {
                    return nullptr;
                }

                void set(Color ^value)
                {
                    
                }
            }

            property virtual AimpTextStyle ^TextStyle
            {
                AimpTextStyle ^get()
                {
                    return (AimpTextStyle)AimpConverter::GetInt32(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXTSTYLE);
                }

                void set(AimpTextStyle ^value)
                {
                    AimpConverter::SetInt32(InternalAimpObject, AIMPUI_LABEL_PROPID_TEXTSTYLE, (int)value);
                }
            }

            property virtual bool Transparent
            {
                bool get()
                {
                    return AimpConverter::GetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_TRANSPARENT);
                }

                void set(bool value)
                {
                    AimpConverter::SetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_TRANSPARENT, value);
                }
            }

            property virtual String ^Url
            {
                String ^get()
                {
                    return AimpConverter::GetString(InternalAimpObject, AIMPUI_LABEL_PROPID_URL);
                }

                void set(String ^value)
                {
                    AimpConverter::SetString(InternalAimpObject, AIMPUI_LABEL_PROPID_URL, value);
                }
            }

            property virtual bool WordWrap
            {
                bool get()
                {
                    return AimpConverter::GetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_WORDWRAP);
                }

                void set(bool value)
                {
                    AimpConverter::SetBool(InternalAimpObject, AIMPUI_LABEL_PROPID_WORDWRAP, value);
                }
            }
        };
    }
}

