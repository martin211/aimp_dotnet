// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#ifndef apiMUIH
#define apiMUIH

#include <windows.h>
#include <unknwn.h>
#include "apiObjects.h"

static const GUID IID_IAIMPServiceMUI = {0x41494D50, 0x5372, 0x764D, 0x55, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* IAIMPServiceMUI */

class IAIMPServiceMUI : public IUnknown
{
public:
    virtual HRESULT WINAPI GetName(IAIMPString** Value) = 0;
    virtual HRESULT WINAPI GetValue(IAIMPString* KeyPath, IAIMPString** Value) = 0;
    virtual HRESULT WINAPI GetValuePart(IAIMPString* KeyPath, int Part, IAIMPString** Value) = 0;
};

#endif // !apiMUIH
