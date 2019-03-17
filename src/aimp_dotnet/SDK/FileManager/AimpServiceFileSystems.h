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

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace FileManager;
        using namespace Commands;

        public ref class AimpServiceFileSystems : public AimpBaseManager<IAIMPServiceFileSystems>, public IAimpServiceFileSystems
        {
        public:
            AimpServiceFileSystems(ManagedAimpCore^ core);

            virtual AimpActionResult Get(FileCommandType commandType, String^ fileUri, IAimpFileSystemCommand^% command);

            virtual AimpActionResult GetDefault(FileCommandType commandType, IAimpFileSystemCommand^% command);
        private:
            static GUID GetCommandId(FileCommandType commandType);

            AimpActionResult GetCommand(FileCommandType commandType, GUID commandId, IAIMPServiceFileSystems* service, String^ value, IAimpFileSystemCommand^% command, bool isDefault);
        };
    }
}
