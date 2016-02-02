#pragma once
#include "AimpUIBaseEdit.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;

        public ref class AimpUIBaseButtonnedEdit : public AimpUIBaseEdit, public IAimpUIBaseButtonnedEdit
        {
        private:
            AimpUIControlEventHandler ^_onChange;

        public:
            explicit AimpUIBaseButtonnedEdit(IAIMPUIBaseButtonnedEdit *aimpObject, IAimpServiceUI ^serviceUI);

            virtual property IAimpUIImageList ^ButtonsImages
            {
                IAimpUIImageList ^get();
                void set(IAimpUIImageList ^value);
            }

            virtual AimpActionResult AddButton(IAimpUIEditButton ^%button);

            virtual AimpActionResult DeleteButton(IAimpUIEditButton ^button);

            virtual AimpActionResult DeleteButton(int index);

            virtual AimpActionResult GetButton(int index, IAimpUIEditButton ^button);

            virtual int GetButtonCount();

            virtual event AimpUIControlEventHandler ^OnChanged
            {
                virtual void add(AimpUIControlEventHandler ^onEvent);
                virtual void remove(AimpUIControlEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }
        };
    }
}
