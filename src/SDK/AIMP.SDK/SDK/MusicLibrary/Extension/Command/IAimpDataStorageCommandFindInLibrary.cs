//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.Objects;

namespace AIMP.SDK.MusicLibrary.Extension.Command;

public class FindResult
{
    public IAimpString GroupingPresetID { get; set; }

    public IAimpGroupingTreeSelection GroupingTreeSelection { get; set; }
}

public interface IAimpDataStorageCommandFindInLibrary
{
    AimpActionResult<FindResult> Find(IAimpFileInfo fileInfo);
}