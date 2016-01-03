namespace AIMP.SDK.GUI.Controls.Events
{
    using System;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIMouseEvents
    {
        event EventHandler<AimpMouseClickEventArgs> OnMouseDoubleClick;

        event EventHandler<AimpMouseClickEventArgs> OnMouseDown;

        event EventHandler<AimpMouseClickEventArgs> OnMouseUp;

        event EventHandler OnMouseLeave;

        event EventHandler<AimpMouseMoveEventArgs> OnMouseMove;
    }
}