namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIMouseEvents
    {
        event AimpUIControlEventHandler<AimpMouseClickArgs> OnMouseDoubleClick;

        event AimpUIControlEventHandler<AimpMouseClickArgs> OnMouseDown;

        event AimpUIControlEventHandler<AimpMouseClickArgs> OnMouseUp;

        event AimpUIControlEventHandler OnMouseLeave;

        event AimpUIControlEventHandler<AimpMouseMoveArgs> OnMouseMove;
    }
}