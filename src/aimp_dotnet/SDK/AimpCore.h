// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\AimpExtensionBase.h"
#include "AimpStream.h"
#include "Action/AimpAction.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK;

        [System::Serializable]
        public ref class AimpCore : public IAimpCore
        {
        private:
            ManagedAimpCore^ _aimpCore;
            bool _disposed;

        public:
            AimpCore(ManagedAimpCore^ core)
            {
                _aimpCore = core;
            }

            ~AimpCore()
            {
                System::Diagnostics::Trace::TraceInformation("Dispose AimpCore");
                System::Diagnostics::Trace::Flush();
                if (_disposed)
                {
                    return;
                }

                this->!AimpCore();
                _disposed = true;
            }

            !AimpCore()
            {
            }

            virtual String^ GetPath(MessageDispatcher::AimpCorePathType pathType)
            {
                String^ path;
                if (_aimpCore->GetPath(pathType, path) == AIMP::SDK::ActionResultType::OK)
                {
                    return path;
                }

                return String::Empty;
            }

            virtual AimpActionResult^ SendMessage(MessageDispatcher::AimpCoreMessageType message, int value, Object^ obj)
            {
                return ACTION_RESULT(Utils::CheckResult(_aimpCore->SendMessage(message, value, obj)));
            }

            virtual AimpActionResult^ RegisterExtension(AIMP::IAimpExtension^ extension)
            {
                return ACTION_RESULT(Utils::CheckResult(_aimpCore->RegisterExtension(IID_IAIMPOptionsDialogFrame, extension)));
            }

            virtual AimpActionResult^ UnregisterExtension(AIMP::IAimpExtension^ extension)
            {
                return ACTION_RESULT(Utils::CheckResult(_aimpCore->UnregisterExtension(extension)));
            }

            virtual StreamResult CreateStream()
            {
                IAIMPStream* stream = nullptr;
                const auto result = _aimpCore->CreateStream(&stream);
                if (result == ActionResultType::OK && stream != nullptr)
                {
                    return gcnew AimpActionResult<IAimpStream^>(result, gcnew AimpStream(stream));
                }

                return gcnew AimpActionResult<IAimpStream^>(result, nullptr);
            }

            virtual System::IntPtr CreateObject(Guid% iid)
            {
                IAIMPCore* core = _aimpCore->GetAimpCore();
                IUnknown* obj;
                array<Byte>^ guidData = iid.ToByteArray();
                pin_ptr<Byte> data = &(guidData[0]);
                //ActionResultType result = Utils::CheckResult(core->CreateObject(*(_GUID *)data, (void**)&obj));
                ActionResultType result = Utils::CheckResult(
                    core->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&obj)));
                if (result == ActionResultType::OK)
                {
                    return IntPtr(obj);
                }

                return IntPtr::Zero;
            }
        };
    }
}
