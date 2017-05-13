/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace System::Runtime::InteropServices;
        using namespace AIMP::SDK::MenuManager;
        using namespace AIMP::SDK::ActionManager;

        public ref class AimpMenuItem : public AimpObject<IAIMPMenuItem>, public IAimpMenuItem
        {
        private:
            EventHandler ^_onExecuteHandler;
            EventHandler ^_onShowHandler;
            IAIMPActionEvent *_onExecuteEvent;
            IAIMPActionEvent *_onShowEvent;
            String ^_id;
            GCHandle _showHandler;
            GCHandle _executeHandler;

        internal:
            static void Execute(gcroot<AIMP::SDK::ActionManager::IAimpActionEvent^> sender, IUnknown *data)
            {
                Object ^obj = sender;
                AimpMenuItem ^item = dynamic_cast<AimpMenuItem^>(obj);
                item->OnExecute(sender, EventArgs::Empty);
            }

            static void Show(gcroot<AIMP::SDK::ActionManager::IAimpActionEvent^> sender, IUnknown *data)
            {
                Object ^obj = sender;
                AimpMenuItem ^item = dynamic_cast<AimpMenuItem^>(obj);
                item->OnShow(sender, EventArgs::Empty);
            }

        public:
            explicit AimpMenuItem(IAIMPMenuItem *menuItem);

            ~AimpMenuItem();

            virtual property String ^Custom
            {
                String^ get();
                void set(String ^value);
            }

            virtual property IAimpAction ^Action
            {
                IAimpAction ^get();
                void set(IAimpAction ^value);
            }

            virtual property String ^Id
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^Name
            {
                String ^get();
                void set(String ^value);
            }

            virtual property bool Checked
            {
                bool get();
                void set(bool value);
            }

            virtual property bool Enabled
            {
                bool get();
                void set(bool value);
            }

            virtual property bool Visible
            {
                bool get();
                void set(bool value);
            }

            virtual property Bitmap ^Glyph
            {
                Bitmap ^get();
                void set(Bitmap ^value);
            }

            virtual property IAimpMenuItem ^Parent
            {
                IAimpMenuItem ^get();
                void set(IAimpMenuItem ^value);
            }

            virtual property AimpMenuItemStyle Style
            {
                AimpMenuItemStyle get();
                void set(AimpMenuItemStyle value);
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

            //virtual void Execute()
            //{
            //    this->OnExecute(this, EventArgs::Empty);
            //}

            //virtual void Show()
            //{
            //    this->OnShow(this, EventArgs::Empty);
            //}
        };
    }
}
