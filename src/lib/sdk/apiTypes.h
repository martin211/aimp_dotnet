////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   General Types
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiTypesH
#define apiTypesH

#ifdef _WIN32

  #include <windows.h>
  #include <unknwn.h>

  #define _C L
  #define _clen  lstrlen
  #define _ctoi  _wtoi
  #define _ctof  _wtof
  #ifdef _MSC_VER
    #define _ctoll _wtoll  
  #else
    #define _ctoll wtoll
  #endif

  typedef float SINGLE;
  typedef wchar_t TChar;
  typedef TChar* PChar;
  typedef DWORD_PTR TTaskHandle;
  typedef HDC HCANVAS;

  #define CONSTIID REFIID
  #define EXPORT __declspec(dllexport)
  #define __unknwncall WINAPI

#else

    #include <cstdint>
    #include <cstdlib>
    #include <cstring>
    #include <cairo.h> // /usr/include/cairo or /usr/local/include/cairo/

    #define API_VAR_NEXTGEN
    
    #define TEXT(x) x
    #define REFIID const GUID & 
    #define CONSTIID const GUID
    #define _clen strlen
    #define _ctoi  atoi
    #define _ctof  atof
    #define _ctoll atoll

// Calling conventions are ignored for 64-bit apps
//    #define WINAPI __attribute__((stdcall))
//    #define __cdecl __attribute__((cdecl))
//    #define _unknwncall __attribute__((cdecl))
  #ifdef __GNUC__
    #define EXPORT __attribute__((dllexport))
  #else
    #define EXPORT __declspec(dllexport)
  #endif    
    #define WINAPI
    #define __cdecl
    #define __unknwncall

    #pragma pack(1)
   
    typedef int32_t BOOL;
    typedef char TChar, *PChar;
    typedef int32_t INT32;
    typedef int64_t INT64;
    typedef void* LPVOID;
    typedef wchar_t WCHAR;
    typedef uint64_t DWORD_PTR; // We have no 32-bit Linux version...
    typedef uint32_t HRESULT;
    typedef uint32_t DWORD;
    typedef uint16_t WORD;
    typedef uint8_t BYTE;
    typedef float SINGLE;
    typedef double DOUBLE;
    typedef cairo_t* HCANVAS;

    typedef DWORD_PTR HBITMAP;
    typedef DWORD_PTR HICON;
    typedef DWORD_PTR HWND;
    typedef DWORD_PTR HMODULE;
    typedef DWORD_PTR TTaskHandle;
    typedef DWORD_PTR LRESULT;
    typedef DWORD_PTR LPARAM;
    typedef DWORD_PTR WPARAM;

    const HRESULT S_OK           = 0;
    const HRESULT E_ABORT        = 0x80004004;
    const HRESULT E_ACCESSDENIED = 0x80070005;
    const HRESULT E_FAIL         = 0x80004005;
    const HRESULT E_HANDLE       = 0x80070006;
    const HRESULT E_INVALIDARG   = 0x80070057;
    const HRESULT E_OUTOFMEMORY  = 0x8007000E;
    const HRESULT E_PENDING      = 0x8000000A;
    const HRESULT E_POINTER      = 0x80004003;
    const HRESULT E_NOINTERFACE  = 0x80004002;
    const HRESULT E_NOTIMPL      = 0x80004001;

    typedef struct {
      INT32 x, y;
    } POINT, *PPOINT;
    
    typedef struct {
      INT32 cx, cy;
    } SIZE, *PSIZE;
  
    typedef struct {
      INT32 left, top, right, bottom;
    } RECT, *PRECT;

    typedef struct {
        DWORD Data1;
        WORD Data2;
        WORD Data3;
        BYTE Data4[8];
    } GUID;
    
    typedef struct 
    {
        BYTE rgbBlue, rgbGreen, rgbRed, rgbReserved;
    } RGBQUAD, *PRGBQUAD;

    #pragma pack()

    static const GUID IID_IUnknown = {0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46};

    class IUnknown
    {
        public:
            //# IUnknown definition is equal to FreePascal's
            virtual HRESULT __unknwncall QueryInterface(REFIID riid, LPVOID* ppvObject) = 0;
            virtual DWORD   __unknwncall AddRef() = 0;
            virtual DWORD   __unknwncall Release() = 0;
    };

#endif

#ifdef API_VAR_NEXTGEN

  const int vvNull   = 0;
  const int vvString = 1;
  const int vvInt32  = 2;
  const int vvInt64  = 3;
  const int vvFloat  = 4;

  #pragma pack(1)
  typedef void (__cdecl* TVarValueFreeProc)(void* ptr);
  typedef struct
  {
	  INT32 type;
	  TVarValueFreeProc freeproc;
  } VarValueStruct,* VarValue;
  #pragma pack()

  #define REFVARVALUE VarValue
  #define OUTVARVALUE VarValue*

#else

  typedef VARIANT VarValue;
  #define REFVARVALUE const VarValue &
  #define OUTVARVALUE VarValue*

#endif

  void VarValueFree(VarValue* value);
  void VarValueCopy(VarValue* target, const VarValue& source);
  void VarValueInit(VarValue* target, const PChar value);
  void VarValueInit(VarValue* target, INT32 value);
  void VarValueInit(VarValue* target, INT64 value);
  void VarValueInit(VarValue* target, double value);
  bool VarValueIsFloat(const VarValue& source);
  bool VarValueIsInt32(const VarValue& source);
  bool VarValueIsInt64(const VarValue& source);
  bool VarValueIsString(const VarValue& source);
  VarValue VarValueNull();
  double VarValueToFloat(const VarValue& source);
  INT32  VarValueToInt32(const VarValue& source);
  INT64  VarValueToInt64(const VarValue& source);
  PChar  VarValueToString(const VarValue& source);

  bool Failed(HRESULT code);
  bool Succeeded(HRESULT code);
  bool EqualGUID(REFIID a, REFIID b); 
#endif // !apiTypesH
