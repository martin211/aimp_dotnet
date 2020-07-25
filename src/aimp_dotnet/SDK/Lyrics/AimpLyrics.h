// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
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
        protected:
            void RegisterAtMemoryManager() override;
            void ReleaseFromMemoryManager() override;

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

            virtual ActionResult Assign(IAimpLyrics^ source);

            virtual AimpActionResult<IAimpLyrics^>^ Clone();

            virtual ActionResult Add(int timeStart, int timeFinish, String^ text);

            virtual ActionResult Delete(int index);

            virtual AimpActionResult<String^>^ Find(int time, int index);

            virtual AimpActionResult<String^>^ Get(int index, int timeStart, int timeFinish);

            virtual IntResult GetCount();

            virtual ActionResult LoadFromFile(String^ virtualFileName);

            virtual ActionResult LoadFromStream(IAimpStream^ stream, LyricsFormat format);

            virtual ActionResult LoadFromString(String^ lyrics, LyricsFormat format);

            virtual ActionResult SaveToFile(String^ fileUri);

            virtual ActionResult SaveToStream(IAimpStream^ stream, LyricsFormat format);

            virtual AimpActionResult<String^>^ SaveToString(LyricsFormat format);
        };
    }
}
