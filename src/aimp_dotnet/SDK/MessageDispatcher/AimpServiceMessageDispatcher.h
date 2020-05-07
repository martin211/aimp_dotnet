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
#include "SDK\BaseManager.h"
#include "InternalAimpMessageHook.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace SDK;
        using namespace MessageDispatcher;

        public ref class AimpServiceMessageDispatcher : public BaseAimpService<IAIMPServiceMessageDispatcher>,
                                                        public IAimpServiceMessageDispatcher
        {
        public:
            explicit AimpServiceMessageDispatcher(ManagedAimpCore^ core);

            ~AimpServiceMessageDispatcher();

            virtual ActionResultType Send(int message, int param1, IntPtr param2);
            virtual int Register(String^ message);
            virtual ActionResultType Hook(IAimpMessageHook^ hook);
            virtual ActionResultType Unhook(IAimpMessageHook^ hook);
        protected:
            IAIMPServiceMessageDispatcher* GetAimpService() override;
        private:
            InternalAimpMessageHook* _hook;
        };
    }
}
