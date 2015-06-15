#pragma once

#include "../AIMP_SDK/aimp3_60_sdk.h"
#include "IUnknownInterfaceImpl.h"

namespace AIMP36SDK
{
	#include "AIMP360\apiOptions.h"
}

namespace AIMP36SDK
{
	public class UnknownReferencesManager
	{
	private:
		ULONG _linkCounter;
		IAIMPOptionsDialogFrame *_frame;
		IAIMPExtensionPlaylistManagerListener *_listner;
		static UnknownReferencesManager *_instance;

	public:
		static UnknownReferencesManager *GetInstance()
		{
			if (_instance == NULL)
			{
				_instance = new UnknownReferencesManager();
			}

			return _instance;
		}

		virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj)
		{
			if (!ppvObj) 
			{
				return E_POINTER;
			}

			if (IID_IUnknown == riid) 
			{
				return S_OK;
			}

			if (riid == AIMP36SDK::IID_IAIMPOptionsDialogFrame)
			{
				*ppvObj = _frame;
				AddRef();
				return S_OK;
			}

			if (riid == AIMP36SDK::IID_IAIMPExtensionPlaylistManagerListener)
			{
				*ppvObj = _listner;
				AddRef();
				return S_OK;
			}

			return E_NOINTERFACE;
		}

		virtual ULONG WINAPI AddRef(void)
		{
			_linkCounter++;
			return _linkCounter;
		}

		virtual ULONG WINAPI Release(void)
		{
			_linkCounter--;

			if (_linkCounter == 0) {
				delete this;
				return 0;
			}

			return _linkCounter;
		}

		virtual void RegisterOptionsFrame(IAIMPOptionsDialogFrame *frame)
		{
			_frame = frame;
		}

		virtual void RegisterPlayListManager(IAIMPExtensionPlaylistManagerListener *playListManager)
		{
			_listner = playListManager;
		}
	};
}
