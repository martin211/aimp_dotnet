#pragma once
#include "Commands\InternalAimpFileSystemCommandFileInfo.h"
#include "Commands\InternalAimpFileSystemCommandOpenFileFolder.h"
#include "Commands\InternalAimpFileSystemCommandCopyToClipboard.h"
#include "Commands\InternalAimpFileSystemCommandDelete.h"
#include "Commands\InternalAimpFileSystemCommandDropSource.h"
#include "Commands\InternalAimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpExtensionFileSystem : public IUnknownInterfaceImpl<IAIMPExtensionFileSystem>
{
private:
    gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> _managed;
    IAIMPCore *_core;

    InternalAimpFileSystemCommandFileInfo *_commandFileInfo = NULL;
    InternalAimpFileSystemCommandOpenFileFolder *_commandOpenFileFolder = NULL;
    InternalAimpFileSystemCommandCopyToClipboard *_commandCopyToClipboard = NULL;
    InternalAimpFileSystemCommandDelete *_commandDelete = NULL;
    InternalAimpFileSystemCommandDropSource *_commandDropSource = NULL;
    InternalAimpFileSystemCommandStreaming *_commandStreaming = NULL;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileSystem> Base;

    InternalAimpExtensionFileSystem(gcroot<AIMP::SDK::FileManager::Extensions::IAimpExtensionFileSystem^> managed, IAIMPCore *core)
    {
        _managed = managed;
        _core = core;
        Object ^obj = managed;

        IAimpFileSystemCommandFileInfo ^fileInfoCommand = dynamic_cast<IAimpFileSystemCommandFileInfo^>(obj);
        IAimpFileSystemCommandOpenFileFolder ^openFileFolderCommand = dynamic_cast<IAimpFileSystemCommandOpenFileFolder^>(obj);
        IAimpFileSystemCommandCopyToClipboard ^copyToClipboardCommand = dynamic_cast<IAimpFileSystemCommandCopyToClipboard^>(obj);
        IAimpFileSystemCommandDelete ^deleteCommand = dynamic_cast<IAimpFileSystemCommandDelete^>(obj);
        IAimpFileSystemCommandDropSource ^dropSourceCommand = dynamic_cast<IAimpFileSystemCommandDropSource^>(obj);
        IAimpFileSystemCommandStreaming ^streamingCommand = dynamic_cast<IAimpFileSystemCommandStreaming^>(obj);

        if (fileInfoCommand != nullptr)
            _commandFileInfo = new InternalAimpFileSystemCommandFileInfo(fileInfoCommand);

        if (openFileFolderCommand != nullptr)
            _commandOpenFileFolder = new InternalAimpFileSystemCommandOpenFileFolder(openFileFolderCommand);

        if (copyToClipboardCommand != nullptr)
            _commandCopyToClipboard = new InternalAimpFileSystemCommandCopyToClipboard(copyToClipboardCommand);

        if (deleteCommand != nullptr)
            _commandDelete = new InternalAimpFileSystemCommandDelete(deleteCommand);

        if (dropSourceCommand != nullptr)
            _commandDropSource = new InternalAimpFileSystemCommandDropSource(dropSourceCommand);

        if (streamingCommand != nullptr)
            _commandStreaming = new InternalAimpFileSystemCommandStreaming(streamingCommand);
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

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs)
    {
        System::Diagnostics::Debug::WriteLine("GetFileAttrs");
        return S_OK;
    }

    virtual HRESULT WINAPI GetFileSize(IAIMPString* FileName, INT64* Size)
    {
        System::Diagnostics::Debug::WriteLine("GetFileSize");
        return S_OK;
    }

    virtual HRESULT WINAPI IsFileExists(IAIMPString* FileName)
    {
        System::Diagnostics::Debug::WriteLine("IsFileExists");
        return S_OK;
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        HRESULT res = Base::QueryInterface(riid, ppvObject);

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

        if (riid == IID_IAIMPFileSystemCommandFileInfo)
        {
            if (_commandFileInfo != NULL)
                return _commandFileInfo->QueryInterface(riid, ppvObject);
        }

        if (riid == IID_IAIMPFileSystemCommandOpenFileFolder)
        {
            if (_commandOpenFileFolder != NULL)
                return _commandOpenFileFolder->QueryInterface(riid, ppvObject);
        }

        if (riid == IID_IAIMPFileSystemCommandCopyToClipboard)
        {
            if (_commandCopyToClipboard != NULL)
                return _commandCopyToClipboard->QueryInterface(riid, ppvObject);
        }

        if (riid == IID_IAIMPFileSystemCommandDropSource)
        {
            if (_commandDropSource != NULL)
                return _commandDropSource->QueryInterface(riid, ppvObject);
        }

        if (riid == IID_IAIMPFileSystemCommandStreaming)
        {
            if (_commandStreaming != NULL)
                return _commandStreaming->QueryInterface(riid, ppvObject);
        }

        if (riid == IID_IAIMPFileSystemCommandDelete)
        {
            if (_commandDelete != NULL)
                return _commandDelete->QueryInterface(riid, ppvObject);
        }

        ppvObject = NULL;
        return res;
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
