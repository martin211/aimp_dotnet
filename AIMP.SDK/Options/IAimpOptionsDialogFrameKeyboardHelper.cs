namespace AIMP.SDK.Options
{
    public interface IAimpOptionsDialogFrameKeyboardHelper
    {
        bool DialogKey(int charCode);

        bool SelectFirstControl();

        bool SelectNextControl(int findForward, int isTabKeyAction);
    }
}