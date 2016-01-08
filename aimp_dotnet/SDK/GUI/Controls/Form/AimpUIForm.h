#pragma once
#include "..\AimpUIWinControl.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Form;

        ref class AimpUIForm : public AimpUIWinControl, public IAimpUIForm
        {
        public:
            explicit AimpUIForm(IAIMPUIForm *aimpForm, IAIMPUIFormEvents *events);

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

            virtual event AimpUIEventHandler ^OnActivated;

            virtual event AimpUIEventHandler ^OnDeactivated;

            virtual event AimpUIEventHandler ^OnCreated;

            virtual event AimpUIEventHandler ^OnDestroyed;

            virtual event AimpUIEventHandler<AimpFormCloseQueryArgs^> ^OnCloseQuery;

            virtual event AimpUIEventHandler ^OnLocalize;

            virtual event AimpUIEventHandler<AimpFormShortCutArgs^> ^OnShortCut;
        };
    }
}
