namespace AIMP.SDK.Options
{
    public interface IAimpServiceOptionsDialog
    {
        AimpActionResult FrameModified(IAimpOptionsDialogFrame frame);

        AimpActionResult FrameShow(IAimpOptionsDialogFrame frame, bool forceShow);
    }
}