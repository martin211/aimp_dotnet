#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Events;

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

            virtual event AimpUIEventHandler<AimpMouseClickArgs^> ^OnMouseDoubleClick;

            virtual event AimpUIEventHandler<AimpMouseClickArgs^> ^OnMouseDown;

            virtual event AimpUIEventHandler<AimpMouseClickArgs^> ^OnMouseUp;

            virtual event AimpUIEventHandler^ OnMouseLeave;

            virtual event AimpUIEventHandler<AimpMouseMoveArgs^> ^OnMouseMove;

            virtual event AimpUIEventHandler ^OnMouseWheel;

            virtual event AimpUIEventHandler ^OnBoundsChanged;

            virtual event AimpBoolUIEventHandler<AimpContextPopupArgs^> ^OnContextPopup;
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
