#pragma once
#include "..\Converter.h"
#include "MenuItemEvent.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::MenuManager;
        using namespace AIMP::SDK::ActionManager;

        public ref class AimpMenuItem : public AimpObject<IAIMPMenuItem>, public IAimpMenuItem
        {
        private:
            EventHandler ^_onExecuteHandler;
            EventHandler ^_onShowHandler;
            MenuItemEvent *_onExecuteEvent;
            MenuItemEvent *_onShowEvent;
            EventCallback *_onExecuteCallback;
            EventCallback *_onShowCallback;

        public:
            explicit AimpMenuItem(IAIMPMenuItem *menuItem) : AimpObject(menuItem)
            {}

            ~AimpMenuItem()
            {
                delete _onExecuteEvent;
                delete _onShowEvent;
                delete _onExecuteCallback;
                delete _onShowCallback;
            }

            virtual property String ^Custom
            {
                String^ get()
                {
                    return String::Empty;
                }

                void set(String ^value)
                {}
            }

            virtual property IAimpAction ^Action
            {
                IAimpAction ^get()
                {
                    return nullptr;
                }

                void set(IAimpAction ^value)
                {

                }
            }

            virtual property String ^Id
            {
                String ^get()
                {
                    return Converter::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID);
                }

                void set(String ^value)
                {
                    Converter::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, value);
                }
            }

            virtual property String ^Name
            {
                String ^get()
                {
                    return Converter::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME);
                }

                void set(String ^value)
                {
                    Converter::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, value);
                }
            }

            virtual property bool Checked
            {
                bool get()
                {
                    return Converter::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED);
                }

                void set(bool value)
                {
                    Converter::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, value);
                }
            }

            virtual property bool Enabled
            {
                bool get()
                {
                    return Converter::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED);
                }

                void set(bool value)
                {
                    Converter::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, value);
                }
            }

            virtual property bool Visible
            {
                bool get()
                {
                    return Converter::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE);
                }

                void set(bool value)
                {
                    Converter::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, value);
                }
            }

            virtual property Bitmap ^Glyph
            {
                Bitmap ^get()
                {
                    return nullptr;
                }

                void set(Bitmap ^value)
                {
                    //if (value != nullptr)
                    //{
                    //    IAIMPImage *image = Converter::CreateImage(value);
                    //    InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_GLYPH, image);
                    //    image->Release();
                    //}
                }
            }

            virtual property IAimpMenuItem ^Parent
            {
                IAimpMenuItem ^get()
                {
                    IAIMPMenuItem *item;
                    InternalAimpObject->GetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, IID_IAIMPMenuItem, (void**)&item);
                    return gcnew AimpMenuItem(item);

                    return nullptr;
                }

                void set(IAimpMenuItem ^value)
                {
                    InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, ((AimpMenuItem^)value)->InternalAimpObject);
                }
            }

            virtual property AimpMenuItemStyle Style
            {
                AimpMenuItemStyle get()
                {
                    return (AimpMenuItemStyle)Converter::GetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE);
                }

                void set(AimpMenuItemStyle value)
                {
                    Converter::SetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, (int)value);
                }
            }

            virtual event EventHandler ^OnExecute
            {
                virtual void add(EventHandler ^onEvent);

                virtual void remove(EventHandler ^onEvent);

                virtual void raise(Object ^sender, EventArgs ^args);
            }

            virtual event EventHandler ^OnShow
            {
                virtual void add(EventHandler ^onEvent);

                virtual void remove(EventHandler ^onEvent);

                virtual void raise(Object ^sender, EventArgs ^args);
            }

            virtual AimpActionResult DeleteChildren()
            {
                return CheckResult(InternalAimpObject->DeleteChildren());
            }

        internal:
            void OnExecuteClick()
            {
                this->OnExecute(this, EventArgs::Empty);
            }

            void OnBeforeShowClick()
            {
                this->OnShow(this, EventArgs::Empty);
            }
        };
    }
}
