// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace Drawing;
        using namespace Runtime::InteropServices;
        using namespace MenuManager;
        using namespace ActionManager;

        public ref class AimpMenuItem : public AimpObject<IAIMPMenuItem>, public IAimpMenuItem
        {
        private:
            EventHandler^ _onExecuteHandler;
            EventHandler^ _onShowHandler;
            IAIMPActionEvent* _onExecuteEvent;
            IAIMPActionEvent* _onShowEvent;
            String^ _id;
            GCHandle _showHandler;
            GCHandle _executeHandler;
            IAimpMenuItem^ _parent = nullptr;

        internal:
            static void Execute(gcroot<IAimpActionEvent^> sender, IUnknown* data)
            {
                Object^ obj = sender;
                AimpMenuItem^ item = dynamic_cast<AimpMenuItem^>(obj);
                item->OnExecute(sender, EventArgs::Empty);
            }

            static void Show(gcroot<IAimpActionEvent^> sender, IUnknown* data)
            {
                Object^ obj = sender;
                AimpMenuItem^ item = dynamic_cast<AimpMenuItem^>(obj);
                item->OnShow(sender, EventArgs::Empty);
            }

        public:
            explicit AimpMenuItem(IAIMPMenuItem* menuItem);

            virtual property String^ Custom
            {
                String^ get();
                void set(String^ value);
            }

            virtual property IAimpAction^ Action
            {
                IAimpAction^ get();
                void set(IAimpAction^ value);
            }

            virtual property String^ Id
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Name
            {
                String^ get();
                void set(String^ value);
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

            virtual property Bitmap^ Glyph
            {
                Bitmap^ get();
                void set(Bitmap^ value);
            }

            virtual property IAimpMenuItem^ Parent
            {
                IAimpMenuItem^ get();
                void set(IAimpMenuItem^ value);
            }

            virtual property MenuItemStyle Style
            {
                MenuItemStyle get();
                void set(MenuItemStyle value);
            }

            virtual event EventHandler^ OnExecute
            {
                virtual void add(EventHandler^ onEvent);
                virtual void remove(EventHandler^ onEvent);
                virtual void raise(Object^ sender, EventArgs^ args);
            }

            virtual event EventHandler^ OnShow
            {
                virtual void add(EventHandler^ onEvent);
                virtual void remove(EventHandler^ onEvent);
                virtual void raise(Object^ sender, EventArgs^ args);
            }

            virtual property bool IsDefault
            {
                bool get();
                void set(bool value);
            }

            virtual property int Shortcut
            {
                int get();
                void set(int value);
            }

            virtual ActionResult DeleteChildren()
            {
                return gcnew AimpActionResult(CheckResult(InternalAimpObject->DeleteChildren()));
            }

        protected:
            void FreeResources() override;
        };
    }
}
