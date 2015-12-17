#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::Services::Options;

        public ref class AimpOptionsDialogFrame : public IAimpOptionsDialogFrame, public IAimpOptionsDialogFrameKeyboardHelper
        {
        private:
            IAIMPOptionsDialogFrame *_aimpObject;
        internal:
            virtual property IAIMPOptionsDialogFrame *AimpObject
            {
                IAIMPOptionsDialogFrame *get()
                {
                    return _aimpObject;
                }

                void set(IAIMPOptionsDialogFrame *value)
                {
                    _aimpObject = value;
                }
            }

        public:
            virtual String^ GetName() abstract;

            virtual IntPtr CreateFrame(IntPtr parentWindow) abstract;

            virtual void DestroyFrame() abstract;
            
            virtual void Notification(int id) abstract;

            virtual bool DialogKey(int charCode) abstract;

            virtual bool SelectFirstControl() abstract;

            virtual bool SelectNextControl(int findForward, int isTabKeyAction) abstract;
        };
    }
}
