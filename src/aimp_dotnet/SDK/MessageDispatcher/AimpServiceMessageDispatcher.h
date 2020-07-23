// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
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

            virtual ActionResult Send(AimpCoreMessageType message, int param1, IntPtr param2);
            virtual int Register(String^ message);
            virtual ActionResult Hook(IAimpMessageHook^ hook);
            virtual ActionResult Unhook(IAimpMessageHook^ hook);
        protected:
            IAIMPServiceMessageDispatcher* GetAimpService() override;
        private:
            InternalAimpMessageHook* _hook = nullptr;
        };
    }
}
