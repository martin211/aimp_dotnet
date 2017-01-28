/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpExtensionCustomVisualization.h"

AimpExtensionCustomVisualization::AimpExtensionCustomVisualization(IAIMPCore *aimpCore, gcroot<AIMP::SDK::Visuals::IAimpExtensionCustomVisualization^> instance)
{
    _managedObject = instance;
    _aimpCore = aimpCore;
}

int AimpExtensionCustomVisualization::GetFlags()
{
    return (int)_managedObject->GetFlags();
}

void AimpExtensionCustomVisualization::Draw(PAIMPVisualData Data)
{
    AIMP::SDK::Visuals::AimpVisualData ^data = AIMP::SDK::AimpConverter::PAIMPVisualDataToManaged(Data);
    _managedObject->Draw(data);
}

HRESULT WINAPI AimpExtensionCustomVisualization::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionCustomVisualization)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    ppvObject = NULL;
    return res;
}

ULONG WINAPI AimpExtensionCustomVisualization::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionCustomVisualization::Release(void)
{
    return Base::Release();
}
