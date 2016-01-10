#pragma once
#include "AimpUIWinControl.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;

        public ref class AimpUIBaseEdit : public AimpUIWinControl, public IAimpUIBaseEdit
        {
        public:
            explicit AimpUIBaseEdit(IAIMPUIBaseEdit *aimpObject, IAimpServiceUI ^serviceUI);

            virtual property bool Borders
            {
                bool get();
                void set(bool value);
            }

            virtual property int MaxLength
            {
                int get();
                void set(int value);
            }

            virtual property bool ReadOnly
            {
                bool get();
                void set(bool value);
            }

            virtual property int SelStart
            {
                int get();
                void set(int value);
            }

            virtual property int SelLength
            {
                int get();
                void set(int value);
            }

            virtual property String ^SelText
            {
                String ^get();
                void set(String ^value);
            }

            virtual property String ^Text
            {
                String ^get();
                void set(String ^value);
            }

            virtual AimpActionResult CopyToClipboard();

            virtual AimpActionResult CutToClipboard();

            virtual AimpActionResult PasteFromClipboard();

            virtual AimpActionResult SelectAll();

            virtual AimpActionResult SelectNone();
        };
    }
}
