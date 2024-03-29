//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

#include "SDK/BaseAimpService.h"
#include "AIMPSDK/AIMP400/apiLyrics.h"

namespace AIMP {
    namespace SDK {
        using namespace Lyrics;
        using namespace Lyrics::Objects;

        public ref class AimpServiceLyrics :
            public BaseAimpService<IAIMPServiceLyrics>,
            public IAimpServiceLyrics {
        public:
            explicit AimpServiceLyrics(ManagedAimpCore^ core);

            ~AimpServiceLyrics();

            virtual AimpActionResult<IntPtr>^ Get(IAimpFileInfo^ fileInfo, LyricsFlags flags, String^ userData);

            virtual ActionResult Cancel(IntPtr taskId, LyricsFlags flags);

            event AimpServiceLyricsReceive^ LyricsReceive
            {
                virtual void add(AimpServiceLyricsReceive^ handler);
                virtual void remove(AimpServiceLyricsReceive^ handler);
                void raise(IAimpLyrics^ lyrics, String^ userData);
            }
        private:
            delegate void OnAimpServiceLyricsReceiveCallback(IAIMPLyrics* lyrics, void* userData);
            OnAimpServiceLyricsReceiveCallback^ _callBack;
            AimpServiceLyricsReceive^ _eventCallBack;

            void OnAimpServiceLyricsReceive(IAIMPLyrics* lyrics, void* userData);
        protected:
            IAIMPServiceLyrics* GetAimpService() override;
        };
    }
}
