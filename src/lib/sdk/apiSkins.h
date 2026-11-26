////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   Skin Manager API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiSkinsH
#define apiSkinsH

#include "apiTypes.h"
#include "apiObjects.h"
#include "apiCore.h"

static const GUID IID_IAIMPSkinInfo = {0x41494D50, 0x536B, 0x696E, 0x49, 0x6E, 0x66, 0x6F, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPServiceSkinsManager = {0x41494D50, 0x5372, 0x7653, 0x6B, 0x69, 0x6E, 0x73, 0x4D, 0x6E, 0x67, 0x72};

// SkinInfo Properties
const int AIMP_SKININFO_PROPID_NAME         = 1;
const int AIMP_SKININFO_PROPID_AUTHOR       = 2;
const int AIMP_SKININFO_PROPID_DESCRIPTION  = 3;
const int AIMP_SKININFO_PROPID_PREVIEW      = 4;

// SkinsManager Properties
const int AIMP_SERVICE_SKINSMAN_PROPID_SKIN                = 1; // IAIMPString
const int AIMP_SERVICE_SKINSMAN_PROPID_HUE                 = 2; // Int32
const int AIMP_SERVICE_SKINSMAN_PROPID_HUE_INTENSITY       = 3; // Int32
const int AIMP_SERVICE_SKINSMAN_PROPID_HUE_BRIGHTNESS      = 4; // Int32, v6.0
const int AIMP_SERVICE_SKINSMAN_PROPID_ALBUMART_ACCENT     = 5; // Int64 (ARGB), v6.0
const int AIMP_SERVICE_SKINSMAN_PROPID_ALBUMART_BACKGROUND = 6; // Int64 (ARGB), v6.0
const int AIMP_SERVICE_SKINSMAN_PROPID_ALBUMART_FOREGROUND = 7; // Int64 (ARGB), v6.0

// Flags for IAIMPServiceSkinsManager.Install
const int AIMP_SERVICE_SKINSMAN_FLAGS_INSTALL_FOR_ALL_USERS = 1;

/* IAIMPSkinInfo */

class IAIMPSkinInfo: public IAIMPPropertyList
{

};

/* IAIMPServiceSkinsManager */

class IAIMPServiceSkinsManager: public IUnknown
{
	public:
		virtual HRESULT WINAPI EnumSkins(IAIMPObjectList **List) = 0;
		virtual HRESULT WINAPI GetSkinInfo(IAIMPString* FileName, IAIMPSkinInfo **Info) = 0;
		virtual HRESULT WINAPI Select(IAIMPString* FileName) = 0;
		// Install/Uninstall
		virtual HRESULT WINAPI Install(IAIMPString *FileName, DWORD Flags) = 0;
		virtual HRESULT WINAPI Uninstall(IAIMPString *FileName) = 0;
		// Tools
		virtual HRESULT WINAPI HSLToRGB(BYTE H, BYTE S, BYTE L, BYTE *R, BYTE *G, BYTE *B) = 0;
		virtual HRESULT WINAPI RGBToHSL(BYTE R, BYTE G, BYTE B, BYTE *H, BYTE *S, BYTE *L) = 0;
};

#endif // !apiSkinsH
