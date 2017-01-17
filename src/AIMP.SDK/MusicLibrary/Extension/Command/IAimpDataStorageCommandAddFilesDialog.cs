using System;

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public interface IAimpDataStorageCommandAddFilesDialog
    {
        AimpActionResult Execute(IntPtr ownerHandle);
    }
}