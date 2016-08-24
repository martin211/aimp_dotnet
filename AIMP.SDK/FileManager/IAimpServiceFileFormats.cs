﻿using System;

namespace AIMP.SDK.FileManager
{
    [Flags]
    public enum FileFormats
    {
        AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO,
        AIMP_SERVICE_FILEFORMATS_CATEGORY_PLAYLISTS
    }

    public interface IAimpServiceFileFormats
    {
        AimpActionResult GetFormats(out string formats);

        AimpActionResult IsSupported(string fileName, FileFormats flags);
    }
}