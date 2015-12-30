#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::GUI::Controls::Form;

        ref class AimpUIForm : public IAimpUIForm
        {
        private:
            String ^_caption;
            AimpBorderIcon _borderIcon;
            AimpBorderStyle _borderStyle;
            IntPtr _icon;
            bool _showTasksBar;
            bool _closeByEscape;
            int _padding;

        public:
            virtual property String ^Caption
            {
                String ^get()
                {
                    return _caption;
                }
                void set(String ^value)
                {
                    _caption = value;
                }
            }

            virtual property AimpBorderIcon AimpBorderIcons
            {
                AimpBorderIcon get()
                {
                    return _borderIcon;
                }
                void set(AimpBorderIcon value)
                {
                    _borderIcon = value;
                }
            }

            virtual property AimpBorderStyle AimpBorderStyle
            {
                AimpBorderStyle get()
                {
                    return _borderStyle;
                }
                void set(AimpBorderStyle value)
                {
                    _borderStyle = value;
                }
            }

            virtual property IntPtr Icon
            {
                IntPtr get()
                {
                    return _icon;
                }
                void set(IntPtr value)
                {
                    _icon = value;
                }
            }

            virtual property bool ShowTasksBar
            {
                bool get()
                {
                    return _showTasksBar;
                }
                void set(bool value)
                {
                    _showTasksBar = value;
                }
            }

            virtual property bool CloseByEscape
            {
                bool get()
                {
                    return _closeByEscape;
                }
                void set(bool value)
                {
                    _closeByEscape = value;
                }
            }

            virtual property int Padding
            {
                int get()
                {
                    return _padding;
                }
                void set(int value)
                {
                    _padding = value;
                }
            }
        };
    }
}
