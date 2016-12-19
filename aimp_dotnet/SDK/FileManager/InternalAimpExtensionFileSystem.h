#pragma once

class InternalAimpExtensionFileSystem : public IUnknownInterfaceImpl<IAIMPExtensionFileSystem>
{
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> _managed;
    IAIMPCore *_core;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileSystem> Base;

    InternalAimpExtensionFileSystem(gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> managed, IAIMPCore *core)
    {
        _managed = managed;
        _core = core;
    }

    virtual void WINAPI BeginUpdate()
    {
        System::Diagnostics::Debugger::Break();
    }

    virtual void WINAPI EndUpdate()
    {
        System::Diagnostics::Debugger::Break();
    }

    virtual HRESULT WINAPI Reset()
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    // Read
    virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double *Value)
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int *Value)
    {
        System::Diagnostics::Debugger::Break();
        if (PropertyID == AIMP_FILESYSTEM_PROPID_READONLY)
        {
            //*Value = _managed->ReadOnly ? 0 : 1;
            *Value = 0;
        }

        return S_OK;
    }

    virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64 *Value)
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void **Value)
    {
        //System::Diagnostics::Debugger::Launch();
        if (PropertyID == AIMP_FILESYSTEM_PROPID_SCHEME)
        {
            IAIMPString *strObject = NULL;
            System::String ^str = _managed->Schema;
            pin_ptr<const WCHAR> strDate = PtrToStringChars(str);
            _core->CreateObject(IID_IAIMPString, (void**)&strObject);
            strObject->SetData((PWCHAR)strDate, str->Length);
            *Value = strObject;
            //ManagedAimpCore->GetAimpCore()->CreateObject(IID_IAIMPString, (void**)&str);
            //*Value = AIMP::SDK::AimpExtension::GetAimpString(_managed->Schema);
        }

        return S_OK;
    }

    // Write
    virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value)
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value)
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value)
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown *Value)
    {
        System::Diagnostics::Debugger::Break();
        return E_NOTIMPL;
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPExtensionFileSystem)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }
};
