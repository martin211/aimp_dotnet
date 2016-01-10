#pragma once
#include "..\AimpUIWinControl.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Form;

        ref class AimpUIForm : public AimpUIWinControl, public IAimpUIForm
        {
        public:
            explicit AimpUIForm(IAIMPUIForm *aimpForm, IAimpServiceUI ^serviceUI);

            virtual property String ^Caption
            {
                String ^get();
                void set(String ^value);
            }

            virtual property AimpBorderIcon AimpBorderIcons
            {
                AimpBorderIcon get();
                void set(AimpBorderIcon value);
            }

            virtual property AimpBorderStyle AimpBorderStyle
            {
                AIMP::SDK::GUI::Controls::Form::AimpBorderStyle get();
                void set(AIMP::SDK::GUI::Controls::Form::AimpBorderStyle value);
            }

            virtual property IntPtr Icon
            {
                IntPtr get();
                void set(IntPtr value);
            }

            virtual property bool ShowTasksBar
            {
                bool get();
                void set(bool value);
            }

            virtual property bool CloseByEscape
            {
                bool get();
                void set(bool value);
            }

            virtual property int Padding
            {
                int get();
                void set(int value);
            }

            virtual AimpActionResult Close();

            virtual AimpActionResult GetFocusedControl(IAimpUIWinControl ^%control);

            virtual AimpActionResult Localized();

            virtual AimpActionResult Release(bool postponed);

            virtual AimpModalResult ShowModal();

            virtual void Show();

            virtual event AimpUIEventHandler ^OnActivated
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler ^OnDeactivated
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler ^OnCreated
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler ^OnDestroyed
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler<AimpFormCloseQueryArgs^> ^OnCloseQuery
            {
                virtual void add(AimpUIEventHandler<AimpFormCloseQueryArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpFormCloseQueryArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpFormCloseQueryArgs ^args);
            }

            virtual event AimpUIEventHandler ^OnLocalize
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler<AimpFormShortCutArgs^> ^OnShortCut
            {
                virtual void add(AimpUIEventHandler<AimpFormShortCutArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpFormShortCutArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpFormShortCutArgs  ^args);
            }

        public:
            void OnActivatedEvent(IAIMPUIForm *sender)
            {
                OnActivated(this);
            }

            void OnDeactivatedEvent(IAIMPUIForm *sender)
            {
                OnDeactivated(this);
            }

            void OnCreatedEvent(IAIMPUIForm *sender)
            {
                OnCreated(this);
            }

            void OnDestroyedEvent(IAIMPUIForm *sender)
            {
                OnDestroyed(this);
            }

            void OnLocalizeEvent(IAIMPUIForm *sender)
            {
                OnLocalize(this);
            }

            bool OnCloseQueryEvent(IAIMPUIForm *sender, BOOL *canClose)
            {
                AimpFormCloseQueryArgs ^args = gcnew AimpFormCloseQueryArgs();
                OnCloseQuery(this, args);
                return args->CanClose;
            }

            bool OnShortCutEvent(IAIMPUIForm *sender, WORD key, WORD modifiers, BOOL *handled)
            {
                AimpFormShortCutArgs ^args = gcnew AimpFormShortCutArgs((int)key, (AimpUIModifiers)modifiers, handled);
                OnShortCut(this, args);
                return args->Handled;
            }

        private:
            AimpUIEventHandler ^_onActivated;
            AimpUIEventHandler ^_onDeactivated;
            AimpUIEventHandler ^_onCreated;
            AimpUIEventHandler ^_onDestroyed;
            AimpUIEventHandler<AimpFormCloseQueryArgs^> ^_onCloseQuery;
            AimpUIEventHandler ^_onLocalize;
            AimpUIEventHandler<AimpFormShortCutArgs^> ^_onShortCut;
        };
    }
}
