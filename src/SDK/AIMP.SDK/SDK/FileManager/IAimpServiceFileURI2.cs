//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.FileManager;

/// <summary>
/// The service provides few methods to work with FileURI of real and virtual files.
/// </summary>
public interface IAimpServiceFileURI2 : IAimpServiceFileURI
{
    /// <summary>
    /// Method returns the scheme of the FileURI.
    /// </summary>
    /// <param name="fileUri">The file uri.</param>
    AimpActionResult<string> GetScheme(string fileUri);
}