// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently
#pragma once

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif  // _DEBUG

#include <windows.h>
#include "AimpSdk.h"
#include <vcclr.h>

#include <boost/intrusive_ptr.hpp>

#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <iostream>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


typedef boost::intrusive_ptr<IAIMPString> IAIMPString_ptr;

inline void intrusive_ptr_add_ref(IUnknown* po)
{
	po->AddRef();
}

inline void intrusive_ptr_release(IUnknown* po)
{
	po->Release();
}
