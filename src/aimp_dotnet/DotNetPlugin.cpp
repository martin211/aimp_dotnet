// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"

//#include <vld.h>

#include "DotNetPlugin.h"
//#include "vcclr.h"
#include "SDK/Options/OptionsDialogFrameExtension.h"

DotNetPlugin::DotNetPlugin()
{
    _optionsLoaded = false;
    System::String ^path = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
    AIMP::SDK::CustomAssemblyResolver::Initialize(path);
    _dotNetPlugin = AIMP::SDK::PluginInfoLoader::LoadPlugin(path);
}

// TODO: Add finalizer.
PWCHAR WINAPI DotNetPlugin::InfoGet(int index)
{
    switch (index)
    {
    case AIMP_PLUGIN_INFO_NAME:
    {
        if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
        {
            return L"AIMP DotNet proxy";
        }

        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->Name);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_AUTHOR:
    {
        if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
        {
            return L"Evgeniy Bogdan";
        }

        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->Author);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
    {
        if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
        {
            return L"AIMP DotNet proxy plugin";
        }

        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->Description);
        return (PWCHAR)str1;
    }
    case AIMP_PLUGIN_INFO_FULL_DESCRIPTION:
    {
        if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
        {
            return L"AIMP DotNet proxy plugin";
        }

        pin_ptr<const wchar_t> str1 = PtrToStringChars(_dotNetPlugin->FullDescription);
        return (PWCHAR)str1;
    }
    }

    return NULL;
}

DWORD WINAPI DotNetPlugin::InfoGetCategories()
{
    if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
    {
        return AIMP_PLUGIN_CATEGORY_ADDONS;
    }

    return (DWORD)_dotNetPlugin->PluginInformation->PluginInfo->AimpPluginType;
}

HRESULT WINAPI DotNetPlugin::Initialize(IAIMPCore* core)
{
    System::Diagnostics::Debug::WriteLine("BEGIN: Initialize DotNet plugin");

//#ifdef _DEBUG
//    _CrtSetBreakAlloc(230);
//#endif

    if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
    {
        return S_OK;
    }

    _managedExtension = gcnew ManagedFunctionality(core);

    _dotNetPlugin->PluginInformation->PluginLoadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
    _dotNetPlugin->PluginInformation->PluginUnloadEvent += gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);
    _dotNetPlugin->PluginInformation->Load();
    AIMP::SDK::IAimpExternalSettingsDialog^ externalSettingsDialog = dynamic_cast<AIMP::SDK::IAimpExternalSettingsDialog^>(_dotNetPlugin->PluginInformation->LoadedPlugin);

    if (externalSettingsDialog != nullptr && _dotNetPlugin->PluginInformation->PluginInfo->IsExternalSettingsDialog)
    {
        _externalSettingsDialog = new AimpExternalSettingsDialog(externalSettingsDialog);
    }

    System::Diagnostics::Debug::WriteLine("END: Initialize DotNet plugin");

    return S_OK;
}

HRESULT WINAPI DotNetPlugin::Finalize()
{
    if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
    {
        return S_OK;
    }

    _dotNetPlugin->PluginInformation->Unload();
    _dotNetPlugin->PluginInformation->PluginLoadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginLoadEventReaction);
    _dotNetPlugin->PluginInformation->PluginUnloadEvent -= gcnew AIMP::SDK::PluginLoadUnloadEvent(_managedExtension, &ManagedFunctionality::PluginUnloadEventReaction);

    delete _managedExtension;

    AIMP::SDK::CustomAssemblyResolver::Deinitialize();
    System::GC::Collect();

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

    return S_OK;
}

void WINAPI DotNetPlugin::SystemNotification(int NotifyID, IUnknown* Data)
{

}

HRESULT WINAPI DotNetPlugin::QueryInterface(REFIID riid, LPVOID* ppvObj)
{
    System::Diagnostics::Debug::WriteLine("DotNetPlugin: QueryInterface");

    if (System::Object::ReferenceEquals(_dotNetPlugin, nullptr))
    {
        return E_NOINTERFACE;
    }

    if (!ppvObj) {
        return E_POINTER;
    }

    if (riid == IID_IAIMPExternalSettingsDialog && _externalSettingsDialog != NULL)
    {
        return _externalSettingsDialog->QueryInterface(riid, ppvObj);
    }

    return E_NOINTERFACE;
}

ULONG WINAPI DotNetPlugin::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI DotNetPlugin::Release(void)
{
    return Base::Release();
}

void WINAPI DotNetPlugin::Show(HWND ParentWindow)
{
    System::IntPtr parent = System::IntPtr(ParentWindow);
    _dotNetPlugin->PluginInformation->ShowSettingDialog(parent);
}
