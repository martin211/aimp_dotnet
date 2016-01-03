namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIMouseEvents
    {
        event AimpUIEventHandler<AimpMouseClickArgs> OnMouseDoubleClick;

        event AimpUIEventHandler<AimpMouseClickArgs> OnMouseDown;

        event AimpUIEventHandler<AimpMouseClickArgs> OnMouseUp;

        event AimpUIEventHandler OnMouseLeave;

        event AimpUIEventHandler<AimpMouseMoveArgs> OnMouseMove;
    }
}