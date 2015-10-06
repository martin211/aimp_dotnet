#pragma once

#include <msclr/marshal.h>

namespace AIMPSDK
{
	#include "aimp3_60_sdk.h"
	
	#include "IUnknownInterfaceImpl.h"
	#include "Utils.h"
	#include "AimpObject.h"

	using namespace AIMPSDK36;

	typedef boost::intrusive_ptr<AIMPSDK36::IAIMPString> IAIMPString_ptr;
}