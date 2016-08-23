#pragma once

class InternalAimpDataProviderSelection : public IUnknownInterfaceImpl<IAIMPMLDataProviderSelection>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> _instance;
public:
    InternalAimpDataProviderSelection(gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> managedInstance)
    {
        _instance = managedInstance;
    }

    virtual DOUBLE WINAPI GetValueAsFloat(int FieldIndex)
    {
        return _instance->GetValueAsFloat(FieldIndex);
    }

    virtual int WINAPI GetValueAsInt32(int FieldIndex)
    {
        return _instance->GetValueAsInt32(FieldIndex);
    }

    virtual INT64 WINAPI GetValueAsInt64(int FieldIndex)
    {
        return _instance->GetValueAsInt64(FieldIndex);
    }

    virtual WCHAR* WINAPI GetValueAsString(int FieldIndex, int* Length)
    {
        System::String^ str = _instance->GetValueAsString(FieldIndex);
        pin_ptr<const wchar_t> str1 = PtrToStringChars(str);
        *Length = str->Length;
        return (PWCHAR)str1;
    }

    virtual BOOL WINAPI NextRow()
    {
        return _instance->NextRow();
    }

    virtual BOOL WINAPI HasNextPage()
    {
        return _instance->HasNextPage();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (riid == IID_IAIMPMLDataProviderSelection)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
