/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MusicLibrary;

        public ref class AimpFileList :
            public AimpObject<IAIMPMLFileList>,
            public IAimpFileList
        {
        public:
            explicit AimpFileList(IAIMPMLFileList* aimpObject);

            virtual AimpActionResult Add(Object^ id, String^ fileName);

            virtual AimpActionResult Clear();

            virtual AimpActionResult Delete(int index);

            virtual AimpActionResult Insert(int index, Object^ id, String^ fileName);

            virtual int GetCount();

            virtual AimpActionResult GetFileName(int index, String^% fileName);

            virtual AimpActionResult SetFileName(int index, String^ fileName);

            virtual AimpActionResult GetId(int index, Object^% id);

            virtual AimpActionResult SetId(int index, Object^ id);

            virtual AimpActionResult Clone(IAimpFileList^% list);
        };
    }
}
