#pragma once
#include "..\..\AIMP_SDK\IUnknownInterfaceImpl.h"
#include "ServiceMenuManager.h"

namespace AIMP
{
	namespace SDK
	{
		#include "..\..\AIMP_SDK\AIMP360\apiActions.h"

		using namespace AIMP36SDK;

		typedef boost::signals::connection EventCallback;
		typedef boost::signal<void(void)> EventChangedSignal;
		typedef boost::signal<void(void)>::slot_function_type EventChangedSignalCB;

		class MenuItemEvent : public IUnknownInterfaceImpl<IAIMPActionEvent>
		{
		public:
			EventCallback RegisterCallback(EventChangedSignalCB subscriber)
			{
				return _callBack.connect(subscriber);
			}

			void UnregisterCallback(EventCallback callback)
			{
				_callBack.disconnect(callback);
			}

			virtual void WINAPI OnExecute(IUnknown *Data)
			{
				_callBack();
			}

			virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
			{
				if (riid == IID_IAIMPActionEvent)
				{
					*ppvObject = this;
					return S_OK;
				}

				ppvObject = NULL;
				return E_NOTIMPL;
			}
		private:
			EventChangedSignal _callBack;
		};
	}
}