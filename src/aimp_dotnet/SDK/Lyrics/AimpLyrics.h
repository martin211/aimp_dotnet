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

            virtual AimpActionResult Assign(IAimpLyrics^ source);

            virtual AimpActionResult Clone(IAimpLyrics^% lyrics);

            virtual AimpActionResult Add(int timeStart, int timeFinish, String^ text);

            virtual AimpActionResult Delete(int index);

            virtual AimpActionResult Find(int time, int index, String^% text);

            virtual AimpActionResult Get(int index, int timeStart, int timeFinish, String^% text);

            virtual AimpActionResult GetCount(int% value);

            virtual AimpActionResult LoadFromFile(String^ virtualFileName);

            virtual AimpActionResult LoadFromStream(IAimpStream^ stream, LyricsFormat format);

            virtual AimpActionResult LoadFromString(String^ lyrics, LyricsFormat format);

            virtual AimpActionResult SaveToFile(String^ fileUri);

            virtual AimpActionResult SaveToStream(IAimpStream^ stream, LyricsFormat format);

            virtual AimpActionResult SaveToString(String^% lyrics, LyricsFormat format);
        };
    }
}
