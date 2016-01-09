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

            virtual event AimpUIEventHandler<AimpMouseClickArgs^> ^OnMouseDoubleClick
            {
                virtual void add(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args);
            }

            virtual event AimpUIEventHandler<AimpMouseClickArgs^> ^OnMouseDown
            {
                virtual void add(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args);
            }

            virtual event AimpUIEventHandler<AimpMouseClickArgs^> ^OnMouseUp
            {
                virtual void add(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpMouseClickArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseClickArgs ^args);
            }

            virtual event AimpUIEventHandler^ OnMouseLeave
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler<AimpMouseMoveArgs^> ^OnMouseMove
            {
                virtual void add(AimpUIEventHandler<AimpMouseMoveArgs^> ^onEvent);
                virtual void remove(AimpUIEventHandler<AimpMouseMoveArgs^> ^onEvent);
                virtual void raise(IAimpUIControl ^sender, AimpMouseMoveArgs ^args);
            }

            virtual event AimpUIEventHandler ^OnMouseWheel
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpUIEventHandler ^OnBoundsChanged
            {
                virtual void add(AimpUIEventHandler ^onEvent);
                virtual void remove(AimpUIEventHandler ^onEvent);
                virtual void raise(IAimpUIControl ^sender);
            }

            virtual event AimpBoolUIEventHandler<AimpContextPopupArgs^> ^OnContextPopup
            {
                virtual void add(AimpBoolUIEventHandler<AimpContextPopupArgs^> ^onEvent);
                virtual void remove(AimpBoolUIEventHandler<AimpContextPopupArgs^> ^onEvent);
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
                OnMouseDoubleClick(this, gcnew AimpMouseClickArgs(PointF(X, Y), (AimpUIModifiers)Modifiers, (AimpUIMouseButton)Button));
            }

            void OnMouseDownEvent(IAIMPUIControl *sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
            {
                OnMouseDown(this, gcnew AimpMouseClickArgs(PointF(X, Y), (AimpUIModifiers)Modifiers, (AimpUIMouseButton)Button));
            }

            void OnMouseUpEvent(IAIMPUIControl *sender, TAIMPUIMouseButton Button, int X, int Y, WORD Modifiers)
            {
                OnMouseUp(this, gcnew AimpMouseClickArgs(PointF(X, Y), (AimpUIModifiers)Modifiers, (AimpUIMouseButton)Button));
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
                OnMouseMove(this, gcnew AimpMouseMoveArgs(PointF(X, Y), (AimpUIModifiers)Modifiers));
            }

            bool OnContextPopupEvent(IAIMPUIControl *sender, int X, int Y)
            {
                return OnContextPopup(this, gcnew AimpContextPopupArgs(PointF(X, Y)));
            }
        private:
            AimpUIEventHandler<AimpMouseClickArgs^> ^_mouseDoubleClick;
            AimpUIEventHandler<AimpMouseClickArgs^> ^_mouseDown;
            AimpUIEventHandler<AimpMouseClickArgs^> ^_mouseUp;
            AimpUIEventHandler^ _mouseLeave;
            AimpUIEventHandler<AimpMouseMoveArgs^> ^_mouseMove;
            AimpUIEventHandler ^_mouseWheel;
            AimpUIEventHandler ^_boundsChanged;
            AimpBoolUIEventHandler<AimpContextPopupArgs^> ^_contextPopup;
        };
    }
}
