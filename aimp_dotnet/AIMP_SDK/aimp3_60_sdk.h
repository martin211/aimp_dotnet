#pragma once

#include <InitGuid.h> // need to force macro DEFINE_GUID to define guid instead declare.
#include <windows.h>

namespace AIMP36SDK
{
	// Add all AIMP SDK functionality to AIMP360SDK namespace.
	#include "AIMP360\apiPlugin.h"
	#include "AIMP360\apiPlayer.h"
	
	#include "AIMP360\apiObjects.h"
	#include "AIMP360\apiFileManager.h"
	#include "AIMP360\apiMessages.h"
	#include "AIMP360\apiAlbumArt.h"
	#include "AIMP360\apiMenu.h"


	
	#include "AIMP360\apiPlaylists.h"
	

	typedef boost::intrusive_ptr<IAIMPString> IAIMPString_ptr;

}



template<class TAimpObject>
public ref class AimpObject
{
protected:
	AimpObject() {}
	TAimpObject *_aimpObject;
public:
	AimpObject(TAimpObject *aimpObject) : _aimpObject(aimpObject)
	{		
	}

	~AimpObject()
	{
		((IUnknown*) _aimpObject)->Release();
		delete _aimpObject;
	}
protected:
	AIMP::SDK::Services::ActionResult CheckResult(HRESULT result)
	{		
		switch (result)
		{
		case E_ACCESSDENIED:
			return AIMP::SDK::Services::ActionResult::AccessDenied;
		case E_HANDLE:
			return AIMP::SDK::Services::ActionResult::Handle;
		case E_INVALIDARG:
			return AIMP::SDK::Services::ActionResult::InvalidArguments;
		case E_NOTIMPL:
			return AIMP::SDK::Services::ActionResult::NotImplemented;
		case E_UNEXPECTED:
			return AIMP::SDK::Services::ActionResult::Unexpected;
		case E_FAIL:
			return AIMP::SDK::Services::ActionResult::Fail;
		}

		return AIMP::SDK::Services::ActionResult::Ok;
	}
internal:
	property TAimpObject *InternalAimpObject
	{
		TAimpObject *get()
		{
			return _aimpObject;
		}
	}
};
