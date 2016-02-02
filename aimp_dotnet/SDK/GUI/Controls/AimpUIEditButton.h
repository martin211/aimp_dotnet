#pragma once
#include "..\..\AimpConverter.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Events;

        public ref class AimpUIEditButton : public IAimpUIEditButton
        {
        internal:
            IAIMPUIEditButton *AimpObject;

        private:
            AimpUIControlEventHandler^ _onChanged;

        public:
            AimpUIEditButton(IAIMPUIEditButton *button)
            {
                AimpObject = button;
            }

            virtual property String ^Custom
            {
                String ^get()
                {
                    return String::Empty;
                }

                void set(String ^value)
                {}
            }

            virtual property String ^Caption
            {
                String ^get()
                {
                    return AimpConverter::GetString(AimpObject, AIMPUI_EDITBUTTON_PROPID_CAPTION);
                }

                void set(String ^value)
                {
                    AimpConverter::SetString(AimpObject, AIMPUI_EDITBUTTON_PROPID_CAPTION, value);
                }
            }

            virtual property bool Enabled
            {
                bool get()
                {
                    return AimpConverter::GetBool(AimpObject, AIMPUI_EDITBUTTON_PROPID_ENABLED);
                }

                void set(bool value)
                {
                    AimpConverter::SetBool(AimpObject, AIMPUI_EDITBUTTON_PROPID_ENABLED, value);
                }
            }

            virtual property String ^Hint
            {
                String ^get()
                {
                    return AimpConverter::GetString(AimpObject, AIMPUI_EDITBUTTON_PROPID_HINT);
                }

                void set(String ^value)
                {
                    AimpConverter::SetString(AimpObject, AIMPUI_EDITBUTTON_PROPID_HINT, value);
                }
            }

            virtual property int Index
            {
                int get()
                {
                    return AimpConverter::GetInt32(AimpObject, AIMPUI_EDITBUTTON_PROPID_INDEX);
                }

                void set(int value)
                {
                    AimpConverter::SetInt32(AimpObject, AIMPUI_EDITBUTTON_PROPID_INDEX, value);
                }
            }

            virtual property int ImageIndex
            {
                int get()
                {
                    return AimpConverter::GetInt32(AimpObject, AIMPUI_EDITBUTTON_PROPID_IMAGEINDEX);
                }

                void set(int value)
                {
                    AimpConverter::SetInt32(AimpObject, AIMPUI_EDITBUTTON_PROPID_IMAGEINDEX, value);
                }
            }

            virtual property bool Visible
            {
                bool get()
                {
                    return AimpConverter::GetBool(AimpObject, AIMPUI_EDITBUTTON_PROPID_VISIBLE);
                }

                void set(bool value)
                {
                    AimpConverter::SetBool(AimpObject, AIMPUI_EDITBUTTON_PROPID_VISIBLE, value);
                }
            }

            virtual property String^ Width
            {
                String^ get()
                {
                    return AimpConverter::GetString(AimpObject, AIMPUI_EDITBUTTON_PROPID_WIDTH);
                }

                void set(String^ value)
                {
                    AimpConverter::SetString(AimpObject, AIMPUI_EDITBUTTON_PROPID_WIDTH, value);
                }
            }

            virtual event AimpUIControlEventHandler^ OnChanged
            {
                virtual void add(AimpUIControlEventHandler^ onEvent)
                {
                    if (this->_onChanged == nullptr)
                    {
                        _onChanged = (AimpUIControlEventHandler^)Delegate::Combine(_onChanged, onEvent);
                    }
                }
                virtual void remove(AimpUIControlEventHandler^ onEvent)
                {
                    if (this->_onChanged != nullptr)
                    {
                        this->_onChanged = (AimpUIControlEventHandler^)Delegate::Remove(this->_onChanged, onEvent);
                    }
                }
                virtual void raise(IAimpUIControl^ sender)
                {
                    if (this->_onChanged != nullptr)
                    {
                        this->_onChanged(sender);
                    }
                }
            }
        };
    }
}
