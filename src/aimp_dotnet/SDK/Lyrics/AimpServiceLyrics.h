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

#include "SDK\BaseManager.h"
#include "AIMPSDK/AIMP400/apiLyrics.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Lyrics;

        public ref class AimpServiceLyrics :
            public AimpBaseManager<IAIMPServiceLyrics>,
            public IAimpServiceLyrics
        {
        public:
            explicit AimpServiceLyrics(ManagedAimpCore^ core);

            ~AimpServiceLyrics();

            virtual AimpActionResult Get(IAimpFileInfo^ fileInfo, LyricsFlags flags, Object^ userData, IntPtr% taskId);

            virtual AimpActionResult Cancel(IntPtr taskId, LyricsFlags flags);

            event AimpServiceLyricsReceive^ LyricsReceive
            {
                virtual void add(AimpServiceLyricsReceive^ handler);
                virtual void remove(AimpServiceLyricsReceive^ handler);
                void raise(IAimpLyrics^ lyrics, Object^ userData);
            }
        private:
            delegate void OnAimpServiceLyricsReceiveCallback(IAIMPLyrics* lyrics, void* userData);
            OnAimpServiceLyricsReceiveCallback^ _callBack;
            AimpServiceLyricsReceive^ _eventCallBack;

            void OnAimpServiceLyricsReceive(IAIMPLyrics* lyrics, void* userData);
        };
    }
}