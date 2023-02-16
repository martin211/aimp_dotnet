//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::TagEditor;

        public ref class AimpFileTagEditor : public IAimpFileTagEditor, public AimpObject<IAIMPFileTagEditor> {
        public:
            explicit AimpFileTagEditor(IAIMPFileTagEditor* aimpObject);

            virtual TYPED_RESULT(IAimpFileInfo) GetMixedInfo();

            virtual TYPED_RESULT(IAimpFileTag) GetTag(int index);

            virtual int GetTagCount();

            virtual ActionResult SetToAll(IAimpFileInfo^ fileInfo);

            virtual ActionResult Save();
        };
    }
}
