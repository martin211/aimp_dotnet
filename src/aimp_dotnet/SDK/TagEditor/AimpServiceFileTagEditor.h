// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP {
    namespace SDK {
        using namespace TagEditor;

        public ref class AimpServiceFileTagEditor : public BaseAimpService<IAIMPServiceFileTagEditor>,
                                                    public IAimpServiceFileTagEditor {
        public:
            explicit AimpServiceFileTagEditor(ManagedAimpCore^ core);

            virtual TYPED_RESULT(IAimpFileTagEditor) EditFile(String^ filePath);

            virtual TYPED_RESULT(IAimpFileTagEditor) EditFile(IAimpStream^ fileStream);

            virtual TYPED_RESULT(IAimpFileInfo) EditTag(String^ filePath, TagType tag);

            virtual TYPED_RESULT(IAimpFileInfo) EditTag(IAimpStream^ fileStream, TagType tag);
        protected:
            IAIMPServiceFileTagEditor* GetAimpService() override;
        };
    }
}
