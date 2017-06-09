// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary
{
    public enum FilesType
    {
        All,
        Selected,
        Focused
    }

    public interface IAimpServiceMusicLibraryUI
    {
        AimpActionResult GetFiles(FilesType flags, out IAimpFileList list);

        AimpActionResult GetGroupingFilter(out IAimpDataFilter filter);

        AimpActionResult GetGroupingFilterPath(out string path);

        AimpActionResult SetGroupingFilterPath(string path);
    }
}