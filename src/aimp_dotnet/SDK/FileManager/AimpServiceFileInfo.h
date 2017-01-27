/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once
#include "..\BaseManager.h"
#include "AimpFileInfo.h"
#include "AimpVirtualFile.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::IO;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpServiceFileInfo : public AimpBaseManager<IAIMPServiceFileInfo>, public IAimpServiceFileInfo
        {
        public:
            AimpServiceFileInfo(ManagedAimpCore^ core);

            virtual AimpActionResult GetFileInfoFromFileUri(String ^fileUri, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo ^%fileInfo);

            virtual AimpActionResult GetFileInfoFromStream(IAimpStream ^fileStream, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo ^% fileInfo);

            virtual AimpActionResult GetVirtualFile(String ^fileUri, IAimpVirtualFile ^%virtualFile);
        };
    }
}
