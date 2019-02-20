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

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::TagEditor;

        public ref class AimpFileTagEditor : public IAimpFileTagEditor, public AimpObject<IAIMPFileTagEditor>
        {
        public:
            explicit AimpFileTagEditor(IAIMPFileTagEditor* aimpObject);

            virtual AimpActionResult GetMixedInfo(IAimpFileInfo^% fileInfo);

            virtual AimpActionResult GetTag(int index, IAimpFileTag^% fileTag);

            virtual int GetTagCount();

            virtual AimpActionResult SetToAll(IAimpFileInfo^ fileInfo);

            virtual AimpActionResult Save();
        };
    }
}
