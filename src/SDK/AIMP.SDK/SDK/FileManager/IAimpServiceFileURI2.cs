//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.FileManager;

public interface IAimpServiceFileURI2 : IAimpServiceFileURI
{
    AimpActionResult<string> GetScheme(string fileUri);
}