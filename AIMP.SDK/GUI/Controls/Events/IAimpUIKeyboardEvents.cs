namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIKeyboardEvents
    {
        event AimpUIEventHandler OnEnter;

        event AimpUIEventHandler OnExit;

        event AimpUIEventHandler<AimpKeyboardArgs> OnKeyDown;

        event AimpUIEventHandler<AimpKeyboardArgs> OnKeyUp;

        event AimpUIEventHandler<AimpKeyArgs> OnKeyPress;
    }
}