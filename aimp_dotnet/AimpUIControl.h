#pragma once

namespace AIMP
{
    namespace SDK
    {
        namespace GUI
        {
            using namespace System;
            using namespace AIMP::SDK::GUI::Controls;

            public ref class AimpUIControl : public AimpObject<IAIMPUIControl>, public IAimpUIControl
            {
            public:
                AimpUIControl();

                virtual property String ^CustomData
                {
                    String ^get();
                    void set(String ^value);
                }

                virtual property bool Enabled
                {
                    bool get();
                    void set(bool value);
                }

                virtual property String ^Hint
                {
                    String ^get();
                    void set(String ^value);
                }

                virtual property String ^Name
                {
                    String ^get();
                    void set(String ^value);
                }

                virtual property AIMP::SDK::GUI::Controls::IAimpUIWinControl ^Parent
                {
                    AIMP::SDK::GUI::Controls::IAimpUIWinControl ^get();
                    void set(AIMP::SDK::GUI::Controls::IAimpUIWinControl ^value);
                }
            };
        }
    }
}


