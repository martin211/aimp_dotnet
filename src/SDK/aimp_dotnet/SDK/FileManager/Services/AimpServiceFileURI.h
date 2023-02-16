//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {

        public ref class AimpServiceFileURI :
            public BaseAimpService<IAIMPServiceFileURI>,
            public IAimpServiceFileURI {
        public:
            explicit AimpServiceFileURI(ManagedAimpCore^ core);
        protected:
            IAIMPServiceFileURI* GetAimpService() override;
        public:
            virtual AimpActionResult<String^>^ Build(String^ containerName, String^ partName);
            virtual AimpActionResult<Tuple<String^, String^>^>^ Parse(String^ fileUri);
            virtual AimpActionResult^ ChangeFileExt(String^ fileUri, String^ extension, FileUriFlag flag);
            virtual AimpActionResult<String^>^ ExtractFileExt(String^ fileUri, FileUriFlag flag);
            virtual AimpActionResult<String^>^ ExtractFileName(String^ fileUri);
            virtual AimpActionResult<String^>^ ExtractFileParentDirName(String^ fileUri);
            virtual AimpActionResult<String^>^ ExtractFileParentName(String^ fileUri);
            virtual AimpActionResult<String^>^ ExtractFilePath(String^ fileUri);
            virtual AimpActionResult^ IsURL(String^ fileUri);
        };
    }
}
