////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   General API Objects
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiObjectsH
#define apiObjectsH

#include "apiTypes.h"

static const GUID IID_IAIMPConfig = {0x41494D50, 0x436F, 0x6E66, 0x69, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPConfigFile = {0x41494D50, 0x436F, 0x6E66, 0x69, 0x67, 0x46, 0x69, 0x6C, 0x65, 0x00, 0x00};
static const GUID IID_IAIMPDPIAware = {0x41494D50, 0x4450, 0x4941, 0x77, 0x61, 0x72, 0x65, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPErrorInfo = {0x41494D50, 0x4572, 0x7249, 0x6E, 0x66, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPHashCode = {0x41494D50, 0x4861, 0x7368, 0x43, 0x6F, 0x64, 0x65, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPFileStream = {0x41494D50, 0x4669, 0x6C65, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6D, 0x00, 0x00};
static const GUID IID_IAIMPImage = {0x41494D50, 0x496D, 0x6167, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPImage2 = {0x41494D50, 0x496D, 0x6167, 0x65, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPImage3 = {0x41494D50, 0x496D, 0x6167, 0x65, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPImageContainer = {0x41494D50, 0x496D, 0x6167, 0x65, 0x43, 0x6F, 0x6E, 0x74, 0x6E, 0x72, 0x00};
static const GUID IID_IAIMPMemoryStream = {0x41494D50, 0x4D65, 0x6D53, 0x74, 0x72, 0x65, 0x61, 0x6D, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPObjectList = {0x41494D50, 0x4F62, 0x6A4C, 0x69, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPObjectList2 = {0x41494D50, 0x4F62, 0x6A4C, 0x69, 0x73, 0x74, 0x32, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPProgressCallback = {0x41494D50, 0x5072, 0x6F67, 0x72, 0x65, 0x73, 0x73, 0x43, 0x42, 0x00, 0x00};
static const GUID IID_IAIMPPropertyList = {0x41494D50, 0x5072, 0x6F70, 0x4C, 0x69, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPPropertyList2 = {0x41494D50, 0x5072, 0x6F70, 0x4C, 0x69, 0x73, 0x74, 0x32, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPStream = {0x41494D50, 0x5374, 0x7265, 0x61, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPString = {0x41494D50, 0x5374, 0x7269, 0x6E, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const GUID IID_IAIMPNamedContainer = {0x41494D50, 0x4E61, 0x6D65, 0x64, 0x43, 0x6E, 0x74, 0x72, 0x00, 0x00, 0x00};

// IAIMPImage and IAIMPImageContainer FormatID
const int AIMP_IMAGE_FORMAT_UNKNOWN = 0;
const int AIMP_IMAGE_FORMAT_BMP     = 1;
const int AIMP_IMAGE_FORMAT_GIF     = 2;
const int AIMP_IMAGE_FORMAT_JPG     = 3;
const int AIMP_IMAGE_FORMAT_PNG     = 4;

// Flags for IAIMPImage.Draw
const int AIMP_IMAGE_DRAW_STRETCHMODE_STRETCH = 0;
const int AIMP_IMAGE_DRAW_STRETCHMODE_FILL    = 1;
const int AIMP_IMAGE_DRAW_STRETCHMODE_FIT     = 2;
const int AIMP_IMAGE_DRAW_STRETCHMODE_TILE    = 4;
const int AIMP_IMAGE_DRAW_QUALITY_DEFAULT     = 0;
const int AIMP_IMAGE_DRAW_QUALITY_LOW         = 8;
const int AIMP_IMAGE_DRAW_QUALITY_HIGH        = 16;
  
// IAIMPPropertyList
const int AIMP_PROPERTYLIST_CUSTOM_PROPID_BASE = 1000;

// Flags for IAIMPString.ChangeCase
const int AIMP_STRING_CASE_LOWER                          = 1;
const int AIMP_STRING_CASE_UPPER                          = 2;
const int AIMP_STRING_CASE_ALL_WORDS_WITH_CAPICAL_LETTER  = 3;
const int AIMP_STRING_CASE_FIRST_WORD_WITH_CAPICAL_LETTER = 4;

// Flags for IAIMPString.Find and IAIMPString.Replace
const int AIMP_STRING_FIND_IGNORECASE = 1;
const int AIMP_STRING_FIND_WHOLEWORD  = 2;

// IAIMPStream.Seet Mode
const int AIMP_STREAM_SEEKMODE_FROM_BEGINNING = 0;
const int AIMP_STREAM_SEEKMODE_FROM_CURRENT   = 1;
const int AIMP_STREAM_SEEKMODE_FROM_END       = 2;

/* IAIMPHashCode */

class IAIMPHashCode: public IUnknown
{
	public:
		virtual INT32  	WINAPI GetHashCode() = 0;
		virtual void 	WINAPI Recalculate() = 0;
};

/* IAIMPDPIAware */

class IAIMPDPIAware: public IUnknown
{
	public:
		virtual INT32  	WINAPI GetDPI() = 0;
		virtual HRESULT WINAPI SetDPI(INT32 Value) = 0;
};

/* IAIMPObjectList */

class IAIMPObjectList: public IUnknown
{
	public:
		virtual HRESULT WINAPI Add(IUnknown* Obj) = 0;
		virtual HRESULT WINAPI Clear() = 0;
		virtual HRESULT WINAPI Delete(INT32 Index) = 0;
		virtual HRESULT WINAPI Insert(INT32 Index, IUnknown* Obj) = 0;
		
		virtual INT32 WINAPI GetCount() = 0;
		virtual HRESULT WINAPI GetObject(INT32 Index, CONSTIID IID, void **Obj) = 0;
		virtual HRESULT WINAPI SetObject(INT32 Index, IUnknown* Obj) = 0;
};

/* IAIMPObjectList2 */

class IAIMPObjectList2: public IAIMPObjectList // v6.00
{
	public:
		virtual INT32 WINAPI IndexOf(IUnknown* Obj) = 0;
};

/* IAIMPString */

class IAIMPString: public IUnknown
{
	public: 
		virtual HRESULT WINAPI Get(INT32 Index, TChar* Item) = 0;
		virtual PChar WINAPI GetData() = 0;
		virtual INT32 WINAPI GetLength() = 0;
		virtual INT32 WINAPI GetHashCode() = 0;
		virtual HRESULT WINAPI Set(INT32 Index, TChar Item) = 0;
		virtual HRESULT WINAPI SetData(PChar Item, INT32 ItemCount) = 0;

		virtual HRESULT WINAPI Add(IAIMPString* S) = 0;
		virtual HRESULT WINAPI Add2(PChar Item, INT32 ItemCount) = 0;

		virtual HRESULT WINAPI ChangeCase(INT32 Mode) = 0;
		virtual HRESULT WINAPI Clone(IAIMPString **S) = 0;

		virtual HRESULT WINAPI Compare(IAIMPString* S, INT32* CompareResult, BOOL IgnoreCase) = 0;
		virtual HRESULT WINAPI Compare2(PChar Items, INT32 ItemCount, INT32* CompareResult, BOOL IgnoreCase) = 0;

		virtual HRESULT WINAPI Delete(INT32 Index, INT32 Count) = 0;

		virtual HRESULT WINAPI Find(IAIMPString* S, INT32 *Index, INT32 Flags, INT32 StartFromIndex) = 0;
		virtual HRESULT WINAPI Find2(TChar *Items, INT32 ItemCount, INT32 *Index, INT32 Flags, INT32 StartFromIndex) = 0;

		virtual HRESULT WINAPI Insert(INT32 Index, IAIMPString *S) = 0;
		virtual HRESULT WINAPI Insert2(INT32 Index, TChar *Items, INT32 ItemCount) = 0;

		virtual HRESULT WINAPI Replace(IAIMPString *OldPattern, IAIMPString *NewPattern, INT32 Flags) = 0;
		virtual HRESULT WINAPI Replace2(TChar *OldPatternItems, INT32 OldPatternItemCount,
			TChar *NewPatternItems, INT32 NewPatternItemCount, INT32 Flags) = 0;

		virtual HRESULT WINAPI SubString(INT32 Index, INT32 Count, IAIMPString **S) = 0;
};

/* IAIMPNamedContainer */

class IAIMPNamedContainer: public IAIMPString // v6.00
{
	public:
		virtual HRESULT WINAPI GetCustomData(void** Obj) = 0;
		virtual HRESULT WINAPI SetCustomData(void* Obj) = 0;
		virtual HRESULT WINAPI GetCustomObject(IUnknown** Obj) = 0;
		virtual HRESULT WINAPI SetCustomObject(IUnknown* Obj) = 0;
};

/* IAIMPStream */

class IAIMPStream: public IUnknown
{
	public:
		virtual INT64 WINAPI GetSize() = 0;
		virtual HRESULT WINAPI SetSize(const INT64 Value) = 0;
		virtual INT64 WINAPI GetPosition() = 0;
		virtual HRESULT WINAPI Seek(const INT64 Offset, INT32 Mode) = 0;
		virtual INT32 WINAPI Read(void* Buffer, DWORD Count) = 0;
		virtual HRESULT WINAPI Write(void* Buffer, DWORD Count, DWORD* Written) = 0;
};

/* IAIMPFileStream */

class IAIMPFileStream: public IAIMPStream
{
	public:
		virtual HRESULT WINAPI GetClipping(INT64 *Offset, INT64 *Size) = 0;
		virtual HRESULT WINAPI GetFileName(IAIMPString **S) = 0;
};

/* IAIMPMemoryStream */

class IAIMPMemoryStream: public IAIMPStream
{
	public:
		virtual void* WINAPI GetData() = 0;
};

/* IAIMPErrorInfo */

class IAIMPErrorInfo: public IUnknown
{
	public:
		virtual HRESULT WINAPI GetInfo(INT32 *ErrorCode, IAIMPString **Message, IAIMPString **Details) = 0;
		virtual HRESULT WINAPI GetInfoFormatted(IAIMPString **S) = 0;
		virtual void WINAPI	SetInfo(INT32 ErrorCode, IAIMPString *Message, IAIMPString *Details) = 0;
};

/* IAIMPImage */

class IAIMPImage: public IUnknown
{
	public:
		virtual HRESULT WINAPI LoadFromFile(IAIMPString *FileName) = 0;
		virtual HRESULT WINAPI LoadFromStream(IAIMPStream *Stream) = 0;
		virtual HRESULT WINAPI SaveToFile(IAIMPString *FileName, INT32 FormatID) = 0;
		virtual HRESULT WINAPI SaveToStream(IAIMPStream *Stream, INT32 FormatID) = 0;
		virtual INT32 WINAPI GetFormatID() = 0;
		virtual HRESULT WINAPI GetSize(SIZE *size) = 0;
		virtual HRESULT Clone(IAIMPImage **Image) = 0;
		virtual HRESULT WINAPI Draw(HCANVAS Canvas, RECT R, DWORD Flags, IUnknown *Attrs) = 0;
		virtual HRESULT WINAPI Resize(INT32 Width, INT32 Height) = 0;
};

/* IAIMPImage2 */

class IAIMPImage2: public IAIMPImage
{
	public:
		virtual HRESULT WINAPI LoadFromResource(HMODULE ResInstance, PChar ResName, PChar ResType) = 0;
		virtual HRESULT WINAPI LoadFromBitmap(HBITMAP Bitmap) = 0;
		virtual HRESULT WINAPI LoadFromBits(RGBQUAD* Bits, INT32 Width, INT32 Height) = 0;
		virtual HRESULT WINAPI CopyToClipboard() = 0;
		virtual HRESULT WINAPI CanPasteFromClipboard() = 0;
		virtual HRESULT WINAPI PasteFromClipboard() = 0;
};


/* IAIMPImage3 */

class IAIMPImage3: public IAIMPImage2
{
	public:
		virtual HRESULT WINAPI SaveToBits(RGBQUAD* Bits) = 0;
};

/* IAIMPImageContainer */

class IAIMPImageContainer: public IUnknown
{
	public:
		virtual HRESULT WINAPI CreateImage(IAIMPImage **Image) = 0;
		virtual HRESULT WINAPI GetInfo(SIZE *Size, INT32 *FormatID) = 0;
		virtual BYTE* WINAPI GetData() = 0;
		virtual DWORD WINAPI GetDataSize() = 0;
		virtual HRESULT WINAPI SetDataSize(DWORD Value) = 0;
};

/* IAIMPProgressCallback */

class IAIMPProgressCallback: public IUnknown
{
	public:
		virtual HRESULT WINAPI Process(float Progress, BOOL *Canceled) = 0;
};

/* IAIMPPropertyList */

class IAIMPPropertyList: public IUnknown
{
	public:
		virtual void WINAPI BeginUpdate() = 0;
		virtual void WINAPI EndUpdate() = 0;
		virtual HRESULT WINAPI Reset() = 0;
		// Read
		virtual HRESULT WINAPI GetValueAsFloat(INT32 PropertyID, DOUBLE *Value) = 0;
		virtual HRESULT WINAPI GetValueAsInt32(INT32 PropertyID, INT32 *Value) = 0;
		virtual HRESULT WINAPI GetValueAsInt64(INT32 PropertyID, INT64 *Value) = 0;
		virtual HRESULT WINAPI GetValueAsObject(INT32 PropertyID, CONSTIID IID, void **Value) = 0;
		// Write
		virtual HRESULT WINAPI SetValueAsFloat(INT32 PropertyID, const DOUBLE Value) = 0;
		virtual HRESULT WINAPI SetValueAsInt32(INT32 PropertyID, INT32 Value) = 0;
		virtual HRESULT WINAPI SetValueAsInt64(INT32 PropertyID, const INT64 Value) = 0;
		virtual HRESULT WINAPI SetValueAsObject(INT32 PropertyID, IUnknown *Value) = 0;
};

/* IAIMPPropertyList2 */

class IAIMPPropertyList2: public IAIMPPropertyList
{
	public:
		virtual HRESULT WINAPI GetValueAsVariant(INT32 PropertyID, OUTVARVALUE Value) = 0;
		virtual HRESULT WINAPI SetValueAsVariant(INT32 PropertyID, REFVARVALUE Value) = 0;
};

/* IAIMPConfig */

class IAIMPConfig: public IUnknown
{
	public:
		// Delete
		virtual HRESULT WINAPI Delete(IAIMPString *KeyPath) = 0;
		// Read
		virtual HRESULT WINAPI GetValueAsFloat(IAIMPString *KeyPath, DOUBLE *Value) = 0;
		virtual HRESULT WINAPI GetValueAsInt32(IAIMPString *KeyPath, INT32 *Value) = 0;
		virtual HRESULT WINAPI GetValueAsInt64(IAIMPString *KeyPath, INT64 *Value) = 0;
		virtual HRESULT WINAPI GetValueAsStream(IAIMPString *KeyPath, IAIMPStream **Value) = 0;
		virtual HRESULT WINAPI GetValueAsString(IAIMPString *KeyPath, IAIMPString **Value) = 0;
		// Write
		virtual HRESULT WINAPI SetValueAsFloat(IAIMPString *KeyPath, const DOUBLE Value) = 0;
		virtual HRESULT WINAPI SetValueAsInt32(IAIMPString *KeyPath, INT32 Value) = 0;
		virtual HRESULT WINAPI SetValueAsInt64(IAIMPString *KeyPath, const INT64 Value) = 0;
		virtual HRESULT WINAPI SetValueAsStream(IAIMPString *KeyPath, IAIMPStream *Value) = 0;
		virtual HRESULT WINAPI SetValueAsString(IAIMPString *KeyPath, IAIMPString *Value) = 0;
};

/* IAIMPConfigFile */

class IAIMPConfigFile: public IAIMPConfig
{
	public:
		virtual HRESULT WINAPI LoadFromFile(IAIMPString *FileName) = 0;
		virtual HRESULT WINAPI LoadFromStream(IAIMPStream *Stream) = 0;
		virtual HRESULT WINAPI SaveToFile(IAIMPString *FileName) = 0;
		virtual HRESULT WINAPI SaveToStream(IAIMPStream *Stream) = 0;
};

#endif // !apiObjectsH
