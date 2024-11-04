//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.Extension.Command;

/// <summary>
/// General case of the <see cref="IAimpDataStorageCommandDeleteFiles"/> command.
/// Provides an ability to delete files by user specified filter. Note that data storage must support for filtering on own side - refer to the AIMPML_DATASTORAGE_PROPID_CAPABILITIES property. 
/// </summary>
public interface IAimpDataStorageCommandDeleteFiles2 : IAimpDataStorageCommandDeleteFiles
{
    AimpActionResult Delete2(IAimpDataFilter filter, bool physically);
}