namespace AIMP.SDK.GUI.Controls
{
    using AIMP.SDK.GUI.Controls.Events;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIBaseButtonnedEdit : IAimpUIBaseEdit, IAimpUIChangeEvents
    {
        IAimpUIImageList ButtonsImages { get; set; }

        AimpActionResult AddButton(out IAimpUIEditButton button);

        AimpActionResult DeleteButton(IAimpUIEditButton button);

        AimpActionResult DeleteButton(int index);

        AimpActionResult GetButton(int index, IAimpUIEditButton button);

        int GetButtonCount();
    }
}