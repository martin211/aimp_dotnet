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
        using namespace TagEditor;

        public ref class AimpServiceFileTagEditor : public AimpBaseManager<IAIMPServiceFileTagEditor>, public IAimpServiceFileTagEditor
        {
        public:
            explicit AimpServiceFileTagEditor(ManagedAimpCore ^core);

            virtual AimpActionResult EditFile(String^ filePath, IAimpFileTagEditor^% editor);

            virtual AimpActionResult EditFile(IAimpStream^ fileStream, IAimpFileTagEditor^% editor);

            virtual AimpActionResult EditTag(String^ filePath, TagType tag, IAimpFileInfo^% fileInfo);

            virtual AimpActionResult EditTag(IAimpStream^ fileStream, TagType tag, IAimpFileInfo^% fileInfo);
        };
    }
}
