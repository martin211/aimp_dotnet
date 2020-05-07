// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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

        public ref class AimpServiceFileTagEditor : public BaseAimpService<IAIMPServiceFileTagEditor>,
                                                    public IAimpServiceFileTagEditor
        {
        public:
            explicit AimpServiceFileTagEditor(ManagedAimpCore^ core);

            virtual ActionResultType EditFile(String^ filePath, IAimpFileTagEditor^% editor);

            virtual ActionResultType EditFile(IAimpStream^ fileStream, IAimpFileTagEditor^% editor);

            virtual ActionResultType EditTag(String^ filePath, TagType tag, IAimpFileInfo^% fileInfo);

            virtual ActionResultType EditTag(IAimpStream^ fileStream, TagType tag, IAimpFileInfo^% fileInfo);
        protected:
            IAIMPServiceFileTagEditor* GetAimpService() override;
        };
    }
}
