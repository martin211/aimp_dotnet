#pragma once
#include <locale>
#include <iostream>
#include <codecvt>
#include <memory>
#include <apiCore.h>
#include <apiObjects.h>
#include <IUnknownImpl.h>

bool CoreCheckVersion(IAIMPCore* core, int version, int buildNumber = 0);
bool CoreSupports(IAIMPCore* core, REFIID riid);
IAIMPString* MakeString(IAIMPCore* core, const TChar* text);
IAIMPString* MakeString(IAIMPCore* core, const std::string& text);
IAIMPString* MakeString(IAIMPCore* core, const std::wstring& text);
