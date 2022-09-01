//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

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

            virtual AimpActionResult<WCHAR>^ GetChar(int index);

            virtual String^ GetData();

            virtual int GetLength();

            virtual int GetHashCode() override;

            virtual AimpActionResult^ SetChar(int index, wchar_t c);

            virtual AimpActionResult^ SetData(String^ chars, int charsCount);

            virtual AimpActionResult^ Add(IAimpString^ str);

            virtual AimpActionResult^ Add(String^ chars, int charsCount);

            virtual AimpActionResult^ ChangeCase(AimpStringCase mode);

            virtual AimpActionResult<IAimpString^>^ Clone();

            virtual AimpActionResult<int>^ Compare(IAimpString^ str, bool ignoreCase);

            virtual AimpActionResult<int>^ Compare(String^ chars, bool ignoreCase);

            virtual AimpActionResult^ Delete(int index, int count);

            virtual AimpActionResult<int>^ Find(IAimpString^ str, AimpStringFindFlags flags, int startFromIndex);

            virtual AimpActionResult<int>^ Find(String^ chars, AimpStringFindFlags flags, int startFromIndex);

            virtual AimpActionResult^ Insert(int index, IAimpString^ str);

            virtual AimpActionResult^ Insert(int index, String^ chars);

            virtual AimpActionResult^ Replace(IAimpString^ oldPattern, IAimpString^ newPattern, AimpStringFindFlags flags);

            virtual AimpActionResult^ Replace(String^ oldPatternChars, String^ newPatternChars, AimpStringFindFlags flags);

            virtual AimpActionResult<IAimpString^>^ SubString(int index, int count);

            virtual void Release();

            virtual int GetAimpHashCode();

            virtual void Recalculate();
        };
    }
}
