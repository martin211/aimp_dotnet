#pragma once

class AimpExtensionPlayerHook :
    public IUnknownInterfaceImpl<IAIMPExtensionPlayerHook>
{
private:
    gcroot<Playback::IAimpExtensionPlayerHook^> _managed;
public:
    explicit AimpExtensionPlayerHook(const gcroot<Playback::IAimpExtensionPlayerHook^> managed)
        : _managed(managed)
    {
    }

    typedef IUnknownInterfaceImpl<IAIMPExtensionPlayerHook> Base;

    virtual HRESULT WINAPI OnCheckURL(IAIMPString* url, BOOL* handled);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};