#pragma once
#include "MenuItemEvent.h"


namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::MenuManager;
        using namespace AIMP::SDK::ActionManager;

        public ref class AimpMenuItem : public AimpObject<IAIMPMenuItem>, public IAimpMenuItem, public IAimpMenuEvents
        {
        private:
            EventHandler ^_onExecuteHandler;
            EventHandler ^_onShowHandler;
            MenuItemEvent *_onExecuteEvent;
            MenuItemEvent *_onShowEvent;
            String ^_id;

        public:
            explicit AimpMenuItem(IAIMPMenuItem *menuItem) : AimpObject(menuItem)
            {}

            ~AimpMenuItem()
            {
                _onExecuteHandler = nullptr;
                _onExecuteHandler = nullptr;
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
                    String^ str = nullptr;
                    PropertyListExtension::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, *&str);
                    return str;
                }

                void set(String ^value)
                {
                    _id = value;
                    PropertyListExtension::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_ID, value);
                }
            }

            virtual property String ^Name
            {
                String ^get()
                {
                    String^ str = nullptr;
                    PropertyListExtension::GetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, *&str);
                    return str;
                }

                void set(String ^value)
                {
                    PropertyListExtension::SetString(InternalAimpObject, AIMP_MENUITEM_PROPID_NAME, value);
                }
            }

            virtual property bool Checked
            {
                bool get()
                {
                    bool val = false;
                    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, val);
                    return val;
                }

                void set(bool value)
                {
                    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_CHECKED, value);
                }
            }

            virtual property bool Enabled
            {
                bool get()
                {
                    bool val = false;
                    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, val);
                    return val;
                }

                void set(bool value)
                {
                    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_ENABLED, value);
                }
            }

            virtual property bool Visible
            {
                bool get()
                {
                    bool val = false;
                    PropertyListExtension::GetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, val);
                    return val;
                }

                void set(bool value)
                {
                    PropertyListExtension::SetBool(InternalAimpObject, AIMP_MENUITEM_PROPID_VISIBLE, value);
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
                    if (value != nullptr)
                    {
                        IAIMPImage *image = AimpExtension::GetImage(value);
                        InternalAimpObject->SetValueAsObject(AIMP_MENUITEM_PROPID_GLYPH, image);
                        image->Release();
                    }
                }
            }

            virtual property IAimpMenuItem ^Parent
            {
                IAimpMenuItem ^get()
                {
                    IAIMPMenuItem *item;
                    InternalAimpObject->GetValueAsObject(AIMP_MENUITEM_PROPID_PARENT, IID_IAIMPMenuItem, (void**)&item);
                    AimpMenuItem ^parentIttem = gcnew AimpMenuItem(item);
                    item->Release();

                    return parentIttem;
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
                    int val = 0;
                    PropertyListExtension::GetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, val);
                    return (AimpMenuItemStyle)val;
                }

                void set(AimpMenuItemStyle value)
                {
                    PropertyListExtension::SetInt32(InternalAimpObject, AIMP_MENUITEM_PROPID_STYLE, (int)value);
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

            virtual void Execute()
            {
                this->OnExecute(this, EventArgs::Empty);
            }

            virtual void Show()
            {
                this->OnShow(this, EventArgs::Empty);
            }
        };
    }
}
