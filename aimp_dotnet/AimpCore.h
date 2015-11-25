#pragma once
#include "ManagedAimpCore.h"
#include "SDK\AimpExtensionBase.h"

namespace AIMP
{
	namespace SDK
	{
        template <class T, class U>
        Boolean IsInst(U u)
        {
            return dynamic_cast<T>(u) != nullptr;
        }

		using namespace System;
		using namespace AIMP::SDK;
		using namespace AIMP::SDK::Interfaces;
		using namespace AIMP::SDK::Extensions;

		public ref class AimpCore : public IAimpCore
		{
		private:
			ManagedAimpCore ^_aimpCore;
			AimpEventsDelegate ^_coreMessageHandler;
			bool _disposed;

		public:
			AimpCore(ManagedAimpCore ^core)
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
				String ^path;
				if (_aimpCore->GetPath(pathType, path) == AIMP::SDK::Services::AimpActionResult::Ok)
				{
					return path;
				}

				return String::Empty;
			}

			virtual AIMP::SDK::Services::AimpActionResult SendMessage(AIMP::SDK::AimpMessages::AimpCoreMessageType message, int value, Object ^obj)
			{
				return Utils::CheckResult(_aimpCore->SendMessage(message, value, obj));
			}

            virtual AimpActionResult RegisterExtension(AIMP::Services::IAimpExtension ^extension)
			{
                if (((AimpExtensionBase^)extension)->ExtensionId == IID_IAIMPOptionsDialogFrame)
                {
                    OptionFrameProxy *frameProxy = new OptionFrameProxy();
                    _aimpCore->RegisterExtension(((AimpExtensionBase^)extension)->ExtensionId, ((AimpExtensionBase^)extension)->InternalProxyExtension);
                }
                return AimpActionResult::Ok;
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

		private:
			void OnCoreMessage(AimpMessages::AimpCoreMessageType param1, int param2)
			{
				CoreMessage(param1, param2);
			}
		};
	}
}
