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
            AimpEventsDelegate^ _coreMessageHandler;
            AimpEventsDelegate^ _internalCoreMessageHandler;
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
                _aimpCore->CoreMessage -= gcnew AimpEventsDelegate(this, &AIMP::SDK::AimpCore::OnCoreMessage);
            }

            virtual String^ GetPath(AimpMessages::AimpCorePathType pathType)
            {
                String^ path;
                if (_aimpCore->GetPath(pathType, path) == AIMP::SDK::AimpActionResult::OK)
                {
                    return path;
                }

                return String::Empty;
            }

            virtual AimpActionResult SendMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType message, int value,
                                                 Object^ obj)
            {
                return Utils::CheckResult(_aimpCore->SendMessage(message, value, obj));
            }

            virtual AimpActionResult RegisterExtension(AIMP::IAimpExtension^ extension)
            {
                return Utils::CheckResult(_aimpCore->RegisterExtension(IID_IAIMPOptionsDialogFrame, extension));
            }

            virtual AimpActionResult UnregisterExtension(AIMP::IAimpExtension^ extension)
            {
                return Utils::CheckResult(_aimpCore->UnregisterExtension(extension));
            }

            virtual event AimpEventsDelegate^ CoreMessage
            {
                virtual void add(AimpEventsDelegate^ onEvent)
                {
                    bool tmp = _coreMessageHandler == nullptr;
                    if (tmp)
                    {
                        _coreMessageHandler = (AimpEventsDelegate^)Delegate::Combine(_coreMessageHandler, onEvent);
                        _aimpCore->CoreMessage += gcnew AimpEventsDelegate(this, &AIMP::SDK::AimpCore::OnCoreMessage);
                    }
                }
                virtual void remove(AimpEventsDelegate^ onEvent)
                {
                    bool tmp = _coreMessageHandler != nullptr;
                    if (tmp)
                    {
                        _coreMessageHandler = (AimpEventsDelegate^)Delegate::Remove(_coreMessageHandler, onEvent);
                        _aimpCore->CoreMessage -= gcnew AimpEventsDelegate(this, &AIMP::SDK::AimpCore::OnCoreMessage);
                    }
                }
                void raise(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
                {
                    bool tmp = _coreMessageHandler != nullptr;
                    if (tmp)
                    {
                        _coreMessageHandler(param1, param2);
                    }
                }
            }

            virtual IAimpStream^ CreateStream()
            {
                IAIMPStream* stream = nullptr;
                if (_aimpCore->CreateStream(&stream) == AimpActionResult::OK && stream != nullptr)
                {
                    return gcnew AIMP::SDK::AimpStream(stream);
                }

                return nullptr;
            }

            virtual System::IntPtr CreateObject(Guid% iid)
            {
                IAIMPCore* core = _aimpCore->GetAimpCore();
                IUnknown* obj;
                array<Byte>^ guidData = iid.ToByteArray();
                pin_ptr<Byte> data = &(guidData[0]);
                //AimpActionResult result = Utils::CheckResult(core->CreateObject(*(_GUID *)data, (void**)&obj));
                AimpActionResult result = Utils::CheckResult(
                    core->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&obj)));
                if (result == AimpActionResult::OK)
                {
                    return IntPtr(obj);
                }

                return IntPtr::Zero;
            }

        internal:
            virtual event AimpEventsDelegate^ InternalCoreMessage
            {
                virtual void add(AimpEventsDelegate^ onEvent)
                {
                    _internalCoreMessageHandler = (AimpEventsDelegate^)Delegate::Combine(
                        _internalCoreMessageHandler, onEvent);
                    _aimpCore->InternalCoreMessage += gcnew AimpEventsDelegate(
                        this, &AIMP::SDK::AimpCore::OnInternalCoreMessage);
                }
                virtual void remove(AimpEventsDelegate^ onEvent)
                {
                    _internalCoreMessageHandler = (AimpEventsDelegate^)Delegate::Remove(
                        _internalCoreMessageHandler, onEvent);
                    _aimpCore->InternalCoreMessage -= gcnew AimpEventsDelegate(
                        this, &AIMP::SDK::AimpCore::OnInternalCoreMessage);
                }
                void raise(AIMP::SDK::AimpMessages::AimpCoreMessageType param1, int param2)
                {
                    bool tmp = _internalCoreMessageHandler != nullptr;
                    if (tmp)
                    {
                        _internalCoreMessageHandler(param1, param2);
                    }
                }
            }

        private:
            void OnCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
            {
                CoreMessage(param1, param2);
            }

            void OnInternalCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
            {
                InternalCoreMessage(param1, param2);
            }
        };
    }
}
