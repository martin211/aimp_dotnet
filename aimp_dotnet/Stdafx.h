// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <windows.h>
#include "AimpSdk.h"
#include <vcclr.h>

#include <boost/intrusive_ptr.hpp>

#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <iostream>

typedef boost::intrusive_ptr<IAIMPString> IAIMPString_ptr;

inline void intrusive_ptr_add_ref(IUnknown* po)
{
	po->AddRef();
}

inline void intrusive_ptr_release(IUnknown* po)
{
	po->Release();
}