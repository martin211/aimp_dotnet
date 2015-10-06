#pragma once
#include "ManagedAimpCore.h"

namespace AIMP
{
	namespace SDK
	{
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
			
			void OnTest(System::Object ^sender, System::EventArgs ^e)
			{
				throw gcnew System::NotImplementedException();
			}
		};
	}
}


