//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.Extension.Command;

public interface IAimpDataStorageCommandDeleteFiles2 : IAimpDataStorageCommandDeleteFiles
{
    AimpActionResult Delete2(IAimpDataFilter filter, bool physically);
}