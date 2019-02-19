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
#include "SDK\FileManager\AimpFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace TagEditor;

        public ref class AimpFileTag : public IAimpFileTag, public AimpFileInfo//, public AimpObject<IAIMPFileTag>,
        {
        private:
            IAIMPFileTag * _fileTag;
        public:
            explicit AimpFileTag(IAIMPFileTag* aimpObject);

            virtual property TagType TagId
            {
                TagType get();
                void set(TagType value);
            }

            virtual property bool DeleteOnSaving
            {
                bool get();
                void set(bool value);
            }
        };
    }
}
