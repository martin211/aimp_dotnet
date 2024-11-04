//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.DataStorage;

/// <summary>
/// Extended version of the <see cref="IAimpDataStorage"/> interface that provides an ability to create data storage based objects.
/// </summary>
public interface IAimpDataStorage2 : IAimpDataStorage
{
    /// <summary>
    /// Creates the object.
    /// Supports only <see cref="IAimpDataFilter"/>.
    /// </summary>
    /// <returns></returns>
    AimpActionResult<object> CreateObject();
}