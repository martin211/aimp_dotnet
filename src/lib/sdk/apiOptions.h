////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   Options Dialog API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiOptionsH
#define apiOptionsH

#include "apiTypes.h"
#include "apiObjects.h"

static const GUID IID_IAIMPServiceOptionsDialog = {0x41494D50, 0x5372, 0x764F, 0x70, 0x74, 0x44, 0x6C, 0x67, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPOptionsDialogFrame   = {0x41494D50, 0x4F70, 0x7444, 0x6C, 0x67, 0x46, 0x72, 0x61, 0x6D, 0x65, 0x00};
static const GUID IID_IAIMPOptionsDialogFrameKeyboardHelper  = {0x41494D50, 0x4F70, 0x7444, 0x6C, 0x67, 0x46, 0x72, 0x6D, 0x4B, 0x48, 0x70};
static const GUID IID_IAIMPOptionsDialogFrameKeyboardHelper2 = {0x41494D50, 0x4F70, 0x7444, 0x6C, 0x67, 0x46, 0x72, 0x6D, 0x4B, 0x48, 0x32};

const int AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOAD         = 0x1;
const int AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_LOCALIZATION = 0x2;
const int AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_SAVE         = 0x3;
const int AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_CAN_SAVE     = 0x4;
const int AIMP_SERVICE_OPTIONSDIALOG_NOTIFICATION_RESET        = 0x5;

static const TChar AIMP_OPT_FRAME_ID[]	 = TEXT("!\\Id");
static const TChar AIMP_OPT_FRAME_PAGE[] = TEXT("!\\Page");

/* IAIMPOptionsDialogFrame */

class IAIMPOptionsDialogFrame: public IUnknown
{
	public:
		virtual HRESULT WINAPI GetName(IAIMPString **S) = 0;
		virtual HWND WINAPI CreateFrame(HWND ParentWnd) = 0;
		virtual void WINAPI DestroyFrame() = 0;
		virtual void WINAPI Notification(INT32 ID) = 0;
};

/* IAIMPOptionsDialogFrameKeyboardHelper */

class IAIMPOptionsDialogFrameKeyboardHelper: public IUnknown
{
	public:
		virtual BOOL WINAPI DialogChar(WCHAR CharCode, INT32 Unused) = 0;
		virtual BOOL WINAPI DialogKey(WORD CharCode, INT32 Unused) = 0;
		virtual BOOL WINAPI SelectFirstControl() = 0;
		virtual BOOL WINAPI SelectNextControl(BOOL FindForward, BOOL CheckTabStop) = 0;
};

/* IAIMPOptionsDialogFrameKeyboardHelper2 */

class IAIMPOptionsDialogFrameKeyboardHelper2: public IUnknown
{
	public:
		virtual BOOL WINAPI SelectLastControl() = 0;
};

/* IAIMPServiceOptionsDialog */

class IAIMPServiceOptionsDialog: public IUnknown
{
	public:
 		virtual HRESULT WINAPI FrameModified(IAIMPOptionsDialogFrame* Frame) = 0;
		virtual HRESULT WINAPI FrameShow(
			IUnknown* Frame, // IAIMPOptionsDialogFrame, IAIMPConfig
		  	BOOL ForceShow) = 0;
};

#endif // !apiOptionsH
