#pragma once
#include "..\BaseManager.h"
#include "Commands\InternalAimpFileSystemCommandFileInfo.h"
#include "Commands\AimpFileSystemCommandFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::FileManager::Commands;

        public ref class AimpServiceFileSystems : public AimpBaseManager<IAIMPServiceFileSystems>, public IAimpServiceFileSystems
        {
        public:
            AimpServiceFileSystems(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileSystems>(core)
            {}

            generic<typename TCommand>
            virtual AimpActionResult Get(String ^fileUri, IAimpFileSystemCommand ^%command)
            {
                IAIMPServiceFileSystems *service = NULL;
                AimpActionResult result = AimpActionResult::Fail;
                IAIMPString *str = NULL;

                try
                {
                    if (GetService(IID_IAIMPServiceFileSystems, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            str = AimpExtension::GetAimpString(fileUri);

                            //if (IAimpFileSystemCommandFileInfo::GetType() == TCommand)
                            //{
                            //    IAIMPFileSystemCommandFileInfo *cmd;
                            //    result = CheckResult(service->Get(str, IID_IAIMPFileSystemCommandFileInfo, (void**)&cmd));

                            //    if (result == AimpActionResult::Ok)
                            //    {
                            //        command = gcnew AimpFileSystemCommandFileInfo(cmd);
                            //    }
                            //}
                        }
                    }

                    return result;
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }

                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                command = nullptr;
                return AimpActionResult::Fail;
            }

            generic<typename TCommand>
            virtual AimpActionResult GetDefault(IAimpFileSystemCommand ^%command)
            {
                command = nullptr;
                return AimpActionResult::Fail;
            }
        };
    }
}