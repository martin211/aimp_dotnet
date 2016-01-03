#pragma once

#include "..\..\..\AIMPSDK\apiGUI.h"
#include "..\..\AimpObject.h"
#include "..\..\AimpConverter.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::GUI::Controls;

        public ref class AimpUIControl : public AimpObject<IAIMPUIControl>, public IAimpUIControl
        {
        public:
            explicit AimpUIControl(IAIMPUIControl *aimpObject);

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

            virtual property IAimpUIWinControl ^Parent
            {
                AIMP::SDK::GUI::Controls::IAimpUIWinControl ^get();
                void set(AIMP::SDK::GUI::Controls::IAimpUIWinControl ^value);
            }

            virtual property IAimpUIPopupMenu ^PopupMenu
            {
                IAimpUIPopupMenu ^get();
                void set(IAimpUIPopupMenu ^value);
            }

            virtual property bool Visible
            {
                bool get();
                void set(bool value);
            }

            virtual AimpActionResult GetPlacement(AimpUIControlPlacement %placement) override;

            virtual AimpActionResult GetPlacementConstraints(AimpUIControlPlacementConstraints %placementConstraints) override;

            virtual AimpActionResult SetPlacement(AimpUIControlPlacement placement) override;

            virtual AimpActionResult SetPlacementConstraints(AimpUIControlPlacementConstraints placementConstraints) override;

            virtual AimpActionResult ClientToScreen(PointF %point) override;

            virtual AimpActionResult ScreenToClient(PointF %point) override;

            virtual AimpActionResult Invalidate() override;

            virtual AimpActionResult PaintTo(IntPtr parent, int x, int y) override;
        internal:
            property IAIMPUIControl *InternalAimpControl
            {
                IAIMPUIControl *get()
                {
                    return _aimpObject;
                }
            }
        };
    }
}
