////////////////////////////////////////////////////////////////////////////////
//
//  Project:   AIMP
//             Programming Interface
//
//  Target:    v6.00 build 3100
//
//  Purpose:   Visualization API
//
//  Author:    Artem Izmaylov
//             © 2006-2026
//             www.aimp.ru
//
#ifndef apiVisualsH
#define apiVisualsH

#include "apiTypes.h"
#include "apiObjects.h"
#include "apiCore.h"

static const GUID IID_IAIMPExtensionCustomVisualization = {0x41494D50, 0x4578, 0x7443, 0x73, 0x74, 0x6D, 0x56, 0x69, 0x73, 0x00, 0x00};
static const GUID IID_IAIMPExtensionEmbeddedVisualization = {0x41494D50, 0x4578, 0x7445, 0x6D, 0x62, 0x64, 0x56, 0x69, 0x73, 0x00, 0x00};
static const GUID IID_IAIMPVisualizationDirectOutput = { 0x41494D50, 0x5669, 0x7344, 0x4F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // v6.0
static const GUID IID_IAIMPServiceVisualizations = {0x41494D50, 0x5372, 0x7656, 0x69, 0x73, 0x75, 0x61, 0x6C, 0x00, 0x00, 0x00};

// Button ID for IAIMPExtensionEmbeddedVisualization.Action
const INT32 AIMP_VISUAL_ACTION_CLICK        = 0;
const INT32 AIMP_VISUAL_ACTION_CLICK_MIDDLE = 1;
const INT32 AIMP_VISUAL_ACTION_MOVE         = 3; // v6.0, only if AIMP_VISUAL_FLAGS_ACTION_EXTRA in Flags
const INT32 AIMP_VISUAL_ACTION_LEAVE        = 4; // v6.0, only if AIMP_VISUAL_FLAGS_ACTION_EXTRA in Flags
const INT32 AIMP_VISUAL_ACTION_CLICK_DOUBLE = 5; // v6.0, only if AIMP_VISUAL_FLAGS_ACTION_DOUBLE_CLICK in Flags
const INT32 AIMP_VISUAL_ACTION_WHEEL_DOWN   = 6; // v6.0, only if AIMP_VISUAL_FLAGS_ACTION_WHEEL in Flags
const INT32 AIMP_VISUAL_ACTION_WHEEL_UP     = 7; // v6.0, only if AIMP_VISUAL_FLAGS_ACTION_WHEEL in Flags
const INT32 AIMP_VISUAL_ACTION_DOWN         = 8; // v6.0, only if AIMP_VISUAL_FLAGS_ACTION_EXTRA in Flags

// Flags for
//   IAIMPExtensionCustomVisualization.GetFlags
//   IAIMPExtensionEmbeddedVisualization.GetFlags and
const DWORD AIMP_VISUAL_FLAGS_RQD_DATA_WAVEFORM 			= 1;
const DWORD AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM				= 2;
const DWORD AIMP_VISUAL_FLAGS_NOT_SUSPEND	    			= 4;
const DWORD AIMP_VISUAL_FLAGS_RQD_DATA_LOGARITHMIC_SPECTRUM = 8; // for internal use
// Flags for IAIMPExtensionEmbeddedVisualization.GetFlags to receive
// extra actions in IAIMPExtensionEmbeddedVisualization.Action method
const DWORD AIMP_VISUAL_FLAGS_ACTION_EXTRA        = 16; // v6.0, for AIMP_VISUAL_ACTION_DOWN, AIMP_VISUAL_ACTION_MOVE, AIMP_VISUAL_ACTION_LEAVE
const DWORD AIMP_VISUAL_FLAGS_ACTION_DOUBLE_CLICK = 32; // v6.0, for AIMP_VISUAL_ACTION_CLICK_DOUBLE
const DWORD AIMP_VISUAL_FLAGS_ACTION_WHEEL        = 64; // v6.0, for AIMP_VISUAL_ACTION_WHEEL_XXX

const int AIMP_VISUAL_SPECTRUM_MAX = 256;
const int AIMP_VISUAL_WAVEFORM_MAX = 512;

typedef SINGLE TAIMPVisualDataSpectrum[AIMP_VISUAL_SPECTRUM_MAX];
typedef SINGLE TAIMPVisualDataWaveform[AIMP_VISUAL_WAVEFORM_MAX];

#pragma pack(push, 1)
struct TAIMPVisualData
{
	SINGLE Peaks[2];
	TAIMPVisualDataSpectrum Spectrum[3];
	TAIMPVisualDataWaveform WaveForm[2];
	INT32 SampleRate; // since v6.0
	TAIMPVisualDataSpectrum LogarithmicSpectrum[3]; // for internal use
	INT32 Reserved; // since v6.0
};
#pragma pack(pop)
typedef TAIMPVisualData* PAIMPVisualData;

/* IAIMPVisualExtension */

class IAIMPExtensionCustomVisualization: public IUnknown
{
		// Common Information
		virtual DWORD WINAPI GetFlags() = 0;
		// Basic functionality
		virtual void WINAPI Draw(PAIMPVisualData Data) = 0;
};

/* IAIMPExtensionEmbeddedVisualization */

class IAIMPExtensionEmbeddedVisualization: public IUnknown
{
	public:
		// Common Information
		virtual DWORD WINAPI GetFlags() = 0;
		virtual HRESULT WINAPI GetMaxDisplaySize(INT32 *Width, INT32 *Height) = 0;
		virtual HRESULT WINAPI GetName(IAIMPString **S) = 0;
		// Initialization / Finalization
		virtual HRESULT WINAPI Initialize(INT32 Width, INT32 Height) = 0;
		virtual void WINAPI Finalize() = 0;
		// Basic functionality
		virtual void WINAPI Action(INT32 X, INT32 Y, INT32 Action) = 0;
		virtual void WINAPI Draw(HCANVAS Canvas, PAIMPVisualData Data) = 0;
		virtual void WINAPI Resize(INT32 NewWidth, INT32 NewHeight) = 0;
};

/* IAIMPVisualizationDirectOutput */

class IAIMPVisualizationDirectOutput : public IUnknown
{
	public:
		virtual void WINAPI Draw(RGBQUAD* Buffer, PAIMPVisualData Data) = 0;
};

/* IAIMPServiceVisual */

class IAIMPServiceVisualizations: public IUnknown
{
};

#endif // !apiVisualsH
