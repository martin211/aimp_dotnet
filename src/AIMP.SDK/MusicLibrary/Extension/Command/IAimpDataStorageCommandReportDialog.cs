using System;

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public interface IAimpDataStorageCommandReportDialog
    {
        AimpActionResult Execute(IntPtr ownerHandle);
    }
}