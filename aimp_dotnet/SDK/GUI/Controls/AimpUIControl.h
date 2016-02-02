#pragma once
//#include "..\AimpServiceUI.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::Drawing;
        using namespace AIMP::SDK::GUI;
        using namespace AIMP::SDK::GUI::Controls;
        using namespace AIMP::SDK::GUI::Controls::Events;

        public ref class AimpUIControl : public AimpObject<IAIMPUIControl>, public IAimpUIControl
        {
        private:
            IAimpServiceUI ^_serviceUI;
            AimpUIControlEventHandler<AimpMouseClickArgs^> ^_mouseDoubleClick;
            AimpUIControlEventHandler<AimpMouseClickArgs^> ^_mouseDown;
            AimpUIControlEventHandler<AimpMouseClickArgs^> ^_mouseUp;
            AimpUIControlEventHandler^ _mouseLeave;
            AimpUIControlEventHandler<AimpMouseMoveArgs^> ^_mouseMove;
            AimpUIControlEventHandler ^_mouseWheel;
            AimpUIControlEventHandler ^_boundsChanged;
            AimpBoolUIControlEventHandler<AimpContextPopupArgs^> ^_contextPopup;

        public:
            explicit AimpUIControl(IAIMPUIControl *aimpObject, IAimpServiceUI ^serviceUI);

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

            virtual AimpActionResult GetPlacement(AimpUIControlPlacement %placement);

            virtual AimpActionResult GetPlacementConstraints(AimpUIControlPlacementConstraints %placementConstraints);

            virtual AimpActionResult SetPlacement(AimpUIControlPlacement placement);

            virtual AimpActionResult SetPlacementConstraints(AimpUIControlPlacementConstraints placementConstraints);

            virtual AimpActionResult ClientToScreen(Point %point);

            virtual AimpActionResult ScreenToClient(Point %point);

            virtual AimpActionResult Invalidate();

            virtual AimpActionResult PaintTo(IntPtr parent, int x, int y);

            virtual event AimpUIControlEventHandler<AimpMouseClickArgs^> ^OnMouseDoubleClick
            {
                virtual void add(AimpUIControlEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args);
            }

            virtual event AimpUIControlEventHandler<AimpMouseClickArgs^> ^OnMouseDown
            {
                virtual void add(AimpUIControlEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args);
            }

            virtual event AimpUIControlEventHandler<AimpMouseClickArgs^> ^OnMouseUp
            {
                virtual void add(AimpUIControlEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args);
            }

            virtual event AimpUIControlEventHandler^ OnMouseLeave
            {
                virtual void add(AimpUIControlEventHandler ^onEvent);
                virtual void remove(AimpUIControlEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIControlEventHandler<AimpMouseMoveArgs^> ^OnMouseMove
            {
                virtual void add(AimpUIControlEventHandler<AimpMouseMoveArgs^> ^onEvent);
                virtual void remove(AimpUIControlEventHandler<AimpMouseMoveArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseMoveArgs ^args);
            }

            virtual event AimpUIControlEventHandler ^OnMouseWheel
            {
                virtual void add(AimpUIControlEventHandler ^onEvent);
                virtual void remove(AimpUIControlEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIControlEventHandler ^OnBoundsChanged
            {
                virtual void add(AimpUIControlEventHandler ^onEvent);
                virtual void remove(AimpUIControlEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpBoolUIControlEventHandler<AimpContextPopupArgs^> ^OnContextPopup
            {
                virtual void add(AimpBoolUIControlEventHandler<AimpContextPopupArgs^> ^onEvent);
                virtual void remove(AimpBoolUIControlEventHandler<AimpContextPopupArgs^> ^onEvent);
                virtual bool raise(IAimpUIControl ^sender, AimpContextPopupArgs^ args);
            }
        internal:
            property IAIMPUIControl *InternalAimpControl
            {
                IAIMPUIControl *get()
                {
                    return _aimpObject;
                }
            }

            void OnMouseDoubleClickEvent(IAIMPUIControl *sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
            {
                OnMouseDoubleClick(this, gcnew AimpMouseClickArgs(Point(X, Y), (AimpUIModifiers)Modifiers, (AimpUIMouseButton)Button));
            }

            void OnMouseDownEvent(IAIMPUIControl *sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
            {
                OnMouseDown(this, gcnew AimpMouseClickArgs(Point(X, Y), (AimpUIModifiers)Modifiers, (AimpUIMouseButton)Button));
            }

            void OnMouseUpEvent(IAIMPUIControl *sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
            {
                OnMouseUp(this, gcnew AimpMouseClickArgs(Point(X, Y), (AimpUIModifiers)Modifiers, (AimpUIMouseButton)Button));
            }

            void OnMouseLeaveEvent(IAIMPUIControl *sender)
            {
                OnMouseLeave(this);
            }

            void OnMouseWheelEvent(IAIMPUIControl *sender)
            {
                OnMouseWheel(this);
            }

            void OnBoundsChangedEvent(IAIMPUIControl *sender)
            {
                OnBoundsChanged(this);
            }

            void OnMouseMoveEvent(IAIMPUIControl *sender, int X, int Y, WORD Modifiers)
            {
                OnMouseMove(this, gcnew AimpMouseMoveArgs(Point(X, Y), (AimpUIModifiers)Modifiers));
            }

            bool OnContextPopupEvent(IAIMPUIControl *sender, int X, int Y)
            {
                return OnContextPopup(this, gcnew AimpContextPopupArgs(Point(X, Y)));
            }
        };
    }
}
