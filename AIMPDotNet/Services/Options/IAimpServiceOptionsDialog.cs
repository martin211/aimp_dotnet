namespace AIMP.SDK.Services.Options
{
    public interface IAimpServiceOptionsDialog
    {
        AimpActionResult FrameModified(IAimpOptionsDialogFrame frame);

        AimpActionResult FrameShow(IAimpOptionsDialogFrame frame, bool forceShow);
    }
}