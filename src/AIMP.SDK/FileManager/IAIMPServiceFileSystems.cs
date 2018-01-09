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

using AIMP.SDK.FileManager.Commands;

namespace AIMP.SDK.FileManager
{
    public interface IAimpServiceFileSystems
    {
        AimpActionResult Get<TCommand>(string fileUri, ref TCommand command) where TCommand : IAimpFileSystemCommand;

        AimpActionResult GetDefault<TCommand>(ref TCommand command) where TCommand : IAimpFileSystemCommand;
    }
}