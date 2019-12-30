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
namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Objects;

        public ref class AimpString :
            public AimpObject<IAIMPString>,
            public IAimpString
        {
        public:
            explicit AimpString(IAIMPString* aimpObject);

            virtual AimpActionResult GetChar(int index, wchar_t% c);

            virtual String^ GetData();

            virtual int GetLength();

            virtual int GetHashCode() override;

            virtual AimpActionResult SetChar(int index, wchar_t c);

            virtual AimpActionResult SetData(String^ chars, int charsCount);

            virtual AimpActionResult Add(IAimpString^ str);

            virtual AimpActionResult Add(String^ chars, int charsCount);

            virtual AimpActionResult ChangeCase(AIMPStringCase mode);

            virtual AimpActionResult Clone(IAimpString^% str);

            virtual AimpActionResult Compare(IAimpString^ str, int% compareResult, bool ignoreCase);

            virtual AimpActionResult Compare(String^ chars, int charsCount, int% compareResult, bool ignoreCase);

            virtual AimpActionResult Delete(int index, int count);

            virtual AimpActionResult Find(IAimpString^ str, int% index, AIMPStringFindFlags flags, int startFromIndex);

            virtual AimpActionResult Find(String^ chars, int charsCount, int% index, AIMPStringFindFlags flags,
                                          int startFromIndex);

            virtual AimpActionResult Insert(int index, IAimpString^ str);

            virtual AimpActionResult Insert(int index, String^ chars, int charsCount);

            virtual AimpActionResult Replace(IAimpString^ oldPattern, IAimpString^ newPattern, int flags);

            virtual AimpActionResult Replace(String^ oldPatternChars, int oldPatternCharsCount, String^ newPatternChars,
                                             int newPatternCharsCount, int flags);

            virtual AimpActionResult SubString(int index, int count, IAimpString^% str);
        };
    }
}
