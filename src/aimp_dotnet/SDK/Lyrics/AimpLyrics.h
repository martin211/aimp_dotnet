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
#include "SDK/AimpObject.h"
#include "AIMPSDK/AIMP400/apiLyrics.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace Lyrics;

        public ref class AimpLyrics : public AimpObject<IAIMPLyrics>, public IAimpLyrics
        {
        public:
            AimpLyrics(IAIMPLyrics* lyrics);

            virtual property String^ Text
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Author
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Album
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Title
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Creator
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ Application
            {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ ApplicationVersion
            {
                String^ get();
                void set(String^ value);
            }

            virtual property LyricsType Type
            {
                LyricsType get();
                void set(LyricsType value);
            }

            virtual property int Offset
            {
                int get();
                void set(int value);
            }

            virtual ActionResultType Assign(IAimpLyrics^ source);

            virtual ActionResultType Clone(IAimpLyrics^% lyrics);

            virtual ActionResultType Add(int timeStart, int timeFinish, String^ text);

            virtual ActionResultType Delete(int index);

            virtual ActionResultType Find(int time, int index, String^% text);

            virtual ActionResultType Get(int index, int timeStart, int timeFinish, String^% text);

            virtual ActionResultType GetCount(int% value);

            virtual ActionResultType LoadFromFile(String^ virtualFileName);

            virtual ActionResultType LoadFromStream(IAimpStream^ stream, LyricsFormat format);

            virtual ActionResultType LoadFromString(String^ lyrics, LyricsFormat format);

            virtual ActionResultType SaveToFile(String^ fileUri);

            virtual ActionResultType SaveToStream(IAimpStream^ stream, LyricsFormat format);

            virtual ActionResultType SaveToString(String^% lyrics, LyricsFormat format);
        };
    }
}
