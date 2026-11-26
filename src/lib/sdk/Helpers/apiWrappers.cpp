#include "apiWrappers.h"

bool CoreCheckVersion(IAIMPCore* core, int version, int buildNumber)
{
    bool result = false;
    IAIMPServiceVersionInfo* info = nullptr;
    if (core != nullptr && Succeeded(core->QueryInterface(IID_IAIMPServiceVersionInfo, reinterpret_cast<void**>(&info))))
    {
        result = info->GetVersionID() >= version && info->GetBuildNumber() >= buildNumber;
        info->Release();
    }
    return result;
}

bool CoreSupports(IAIMPCore* core, REFIID riid)
{
    IUnknown* intf = nullptr;
    if (Succeeded(core->QueryInterface(riid, reinterpret_cast<void**>(&intf))))
    {
        intf->Release();
        return true;
    }
    return false;
}

IAIMPString* MakeString(IAIMPCore* core, const TChar* text)
{
	IAIMPString* string;
	if (Succeeded(core->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&string))))
	{
		string->SetData((PChar)text, _clen(text));
        	return string;
	}
	return nullptr;
}

IAIMPString* MakeString(IAIMPCore* core, const std::string& text)
{
#ifdef _WIN32
	std::wstring wstr(text.begin(), text.end());
	return MakeString(core, wstr);
#else
	return MakeString(core, text.c_str());
#endif
}

IAIMPString* MakeString(IAIMPCore* core, const std::wstring& text)
{
#ifdef _WIN32
	return MakeString(core, text.c_str());
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return MakeString(core, converter.to_bytes(text));
#endif
}
