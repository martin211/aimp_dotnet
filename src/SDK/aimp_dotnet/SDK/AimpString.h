// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace AIMP::SDK;

        public ref class AimpString :
            public AimpObject<IAIMPString>,
            public IAimpString {
        public:
            explicit AimpString(IAIMPString* aimpObject);

            virtual ActionResultType GetChar(int index, wchar_t% c);

            virtual String^ GetData();

            virtual int GetLength();

            virtual int GetHashCode() override;

            virtual ActionResultType SetChar(int index, wchar_t c);

            virtual ActionResultType SetData(String^ chars, int charsCount);

            virtual ActionResultType Add(IAimpString^ str);

            virtual ActionResultType Add(String^ chars, int charsCount);

            virtual ActionResultType ChangeCase(AimpStringCase mode);

            virtual ActionResultType Clone(IAimpString^% str);

            virtual ActionResultType Compare(IAimpString^ str, int% compareResult, bool ignoreCase);

            virtual ActionResultType Compare(String^ chars, int charsCount, int% compareResult, bool ignoreCase);

            virtual ActionResultType Delete(int index, int count);

            virtual ActionResultType Find(IAimpString^ str, int% index, AimpStringFindFlags flags, int startFromIndex);

            virtual ActionResultType Find(String^ chars, int charsCount, int% index, AimpStringFindFlags flags,
                                          int startFromIndex);

            virtual ActionResultType Insert(int index, IAimpString^ str);

            virtual ActionResultType Insert(int index, String^ chars, int charsCount);

            virtual ActionResultType Replace(IAimpString^ oldPattern, IAimpString^ newPattern, int flags);

            virtual ActionResultType Replace(String^ oldPatternChars, int oldPatternCharsCount, String^ newPatternChars,
                                             int newPatternCharsCount, int flags);

            virtual ActionResultType SubString(int index, int count, IAimpString^% str);

            virtual void Release();
        };
    }
}
