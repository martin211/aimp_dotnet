////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   MUI API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiMUIH
#define apiMUIH

#include "apiTypes.h"
#include "apiObjects.h"

static const GUID IID_IAIMPServiceMUI = {0x41494D50, 0x5372, 0x764D, 0x55, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* IAIMPServiceMUI */

class IAIMPServiceMUI: public IUnknown
{
	public:
 		virtual HRESULT WINAPI GetName(IAIMPString **Value) = 0;
		virtual HRESULT WINAPI GetValue(IAIMPString *KeyPath, IAIMPString **Value) = 0;
		virtual HRESULT WINAPI GetValuePart(IAIMPString *KeyPath, INT32 Part, IAIMPString **Value) = 0;
};

#endif // !apiMUIH
