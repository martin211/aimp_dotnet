namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIKeyboardEvents
    {
        event AimpUIControlEventHandler OnEnter;

        event AimpUIControlEventHandler OnExit;

        event AimpUIControlEventHandler<AimpKeyboardArgs> OnKeyDown;

        event AimpUIControlEventHandler<AimpKeyboardArgs> OnKeyUp;

        event AimpUIControlEventHandler<AimpKeyArgs> OnKeyPress;
    }
}