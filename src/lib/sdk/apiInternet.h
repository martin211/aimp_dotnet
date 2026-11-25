////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   Internet API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiInternetH
#define apiInternetH

#include "apiTypes.h"
#include "apiObjects.h"
#include "apiCore.h"

static const GUID IID_IAIMPServiceConnectionSettings = {0x4941494D, 0x5053, 0x7276, 0x43, 0x6F, 0x6E, 0x6E, 0x43, 0x66, 0x67, 0x00};
static const GUID IID_IAIMPServiceHTTPClient = {0x41494D50, 0x5372, 0x7648, 0x74, 0x74, 0x70, 0x43, 0x6C, 0x74, 0x00, 0x00};
static const GUID IID_IAIMPServiceHTTPClient2 = {0x41494D50, 0x5372, 0x7648, 0x74, 0x74, 0x70, 0x43, 0x6C, 0x74, 0x32, 0x00};
static const GUID IID_IAIMPServiceHTTPClient3 = {0x41494D50, 0x5372, 0x7648, 0x74, 0x74, 0x70, 0x43, 0x6C, 0x74, 0x33, 0x00};
static const GUID IID_IAIMPHTTPClientEvents = {0x41494D50, 0x4874, 0x7470, 0x43, 0x6C, 0x74, 0x45, 0x76, 0x74, 0x73, 0x00};
static const GUID IID_IAIMPHTTPClientEvents2 = {0x41494D50, 0x4874, 0x7470, 0x43, 0x6C, 0x74, 0x45, 0x76, 0x74, 0x73, 0x32};

// PropIDs for IAIMPServiceConnectionSettings
const int AIMP_SERVICE_CONSET_PROPID_CONNECTION_TYPE = 1;
const int AIMP_SERVICE_CONSET_PROPID_PROXY_SERVER    = 2;
const int AIMP_SERVICE_CONSET_PROPID_PROXY_PORT      = 3;
const int AIMP_SERVICE_CONSET_PROPID_PROXY_USERNAME  = 4;
const int AIMP_SERVICE_CONSET_PROPID_PROXY_USERPASS  = 5;
const int AIMP_SERVICE_CONSET_PROPID_TIMEOUT         = 6;
const int AIMP_SERVICE_CONSET_PROPID_USERAGENT       = 7;

// Connection Types
const int AIMP_SERVICE_CONSET_CONNECTIONTYPE_DIRECT         = 0;
const int AIMP_SERVICE_CONSET_CONNECTIONTYPE_PROXY          = 1;
const int AIMP_SERVICE_CONSET_CONNECTIONTYPE_SYSTEMDEFAULTS = 2;

// Flags for HTTPClient
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_WAITFOR         	= 1;
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_UTF8            	= 2;
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_PRIORITY_NORMAL 	= 0;
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_PRIORITY_LOW    	= 4;
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_PRIORITY_HIGH   	= 8;
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_ASYNC_ACCEPT    	= 16; // v6.0
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_ASYNC_PROGRESS  	= 32; // v6.0
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_ASYNC_COMPLETE  	= 64; // v6.0
const int AIMP_SERVICE_HTTPCLIENT_FLAGS_IGNORE_CERT_ISSUES 	= 128; // v6.0

// Methods for IAIMPServiceHTTPClient2.Request
const int AIMP_SERVICE_HTTPCLIENT_METHOD_GET    = 0;
const int AIMP_SERVICE_HTTPCLIENT_METHOD_POST   = 1;
const int AIMP_SERVICE_HTTPCLIENT_METHOD_PUT    = 2;
const int AIMP_SERVICE_HTTPCLIENT_METHOD_DELETE = 3;
const int AIMP_SERVICE_HTTPCLIENT_METHOD_HEAD   = 4;

/* IAIMPHTTPClientEvents */

class IAIMPHTTPClientEvents: public IUnknown
{
	public:
		virtual void WINAPI OnAccept(IAIMPString *ContentType, const INT64 ContentSize, BOOL *Allow) = 0;
		virtual void WINAPI OnComplete(IAIMPErrorInfo *ErrorInfo, BOOL Canceled) = 0;
		virtual void WINAPI OnProgress(const INT64 Downloaded, const INT64 Total) = 0;
};

/* IAIMPHTTPClientEvents2 */

class IAIMPHTTPClientEvents2: public IUnknown
{
	public:
		virtual void WINAPI OnAcceptHeaders(IAIMPString* Header, BOOL* Allow) = 0;
};
  
/* IAIMPServiceConnectionSettings */

class IAIMPServiceConnectionSettings: public IAIMPPropertyList
{
};

/* IAIMPServiceHTTPClient */

class IAIMPServiceHTTPClient: public IUnknown
{
	public:
		virtual HRESULT WINAPI Get(IAIMPString *URL, DWORD Flags, IAIMPStream *AnswerData,
			IAIMPHTTPClientEvents *EventHandler, IAIMPConfig *Params, TTaskHandle *Task) = 0;
		virtual HRESULT WINAPI Post(IAIMPString *URL, DWORD Flags, IAIMPStream *AnswerData, IAIMPStream *PostData,
			IAIMPHTTPClientEvents *EventHandler, IAIMPConfig *Params, TTaskHandle *Task) = 0;
		virtual HRESULT WINAPI Cancel(TTaskHandle Task, DWORD Flags) = 0;
};

/* IAIMPServiceHTTPClient2 */

class IAIMPServiceHTTPClient2: public IUnknown
{
	public:
		virtual HRESULT WINAPI Request(IAIMPString *URL, DWORD Method, DWORD Flags,
			IAIMPStream *AnswerData, IAIMPStream *PostData,
			IAIMPHTTPClientEvents *EventHandler, IAIMPConfig *Params, TTaskHandle *Task) = 0;
		virtual HRESULT WINAPI Cancel(TTaskHandle Task, DWORD Flags) = 0;
};

/* IAIMPServiceHTTPClient3 */

class IAIMPServiceHTTPClient3: public IUnknown
{
	public:
		virtual HRESULT WINAPI Request(IAIMPString *URL, IAIMPString *Method, DWORD Flags,
			IAIMPStream *AnswerData, IAIMPStream *PostData,
			IAIMPHTTPClientEvents *EventHandler, IAIMPConfig *Params, TTaskHandle *Task) = 0;
		virtual HRESULT WINAPI Cancel(TTaskHandle Task, DWORD Flags) = 0;
};

#endif // !apiInternetH
