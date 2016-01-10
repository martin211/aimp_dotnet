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
        public:
            explicit AimpUIBaseButtonnedEdit(IAIMPUIBaseButtonnedEdit *aimpObject, IAimpServiceUI ^serviceUI);

            virtual property IAimpUIImageList ^ButtonsImages
            {
                IAimpUIImageList ^get();
                void set(IAimpUIImageList ^value);
            }

            virtual AimpActionResult AddButton(IAimpUIEditButton ^%button);

            virtual AimpActionResult DeleteButton(IAimpUIEditButton ^button);

            virtual AimpActionResult DeleteButton(int index, IAimpUIEditButton ^button);

            virtual AimpActionResult GetButton(int index, IAimpUIEditButton ^button);

            virtual int GetButtonCount();

            virtual event AimpUIEventHandler ^OnChanged
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }
        };
    }
}
