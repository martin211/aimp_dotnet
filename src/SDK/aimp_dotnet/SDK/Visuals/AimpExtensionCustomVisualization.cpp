//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionCustomVisualization.h"

AimpExtensionCustomVisualization::AimpExtensionCustomVisualization(IAIMPCore* aimpCore,
                                                                   gcroot<Visuals::IAimpExtensionCustomVisualization^>
                                                                   instance) {
    _managedObject = instance;
    _aimpCore = aimpCore;
}

int AimpExtensionCustomVisualization::GetFlags() {
    return (int)_managedObject->GetFlags();
}

void AimpExtensionCustomVisualization::Draw(PAIMPVisualData Data) {
    auto data = AimpConverter::PAIMPVisualDataToManaged(Data);
    _managedObject->Draw(data);
}

HRESULT WINAPI AimpExtensionCustomVisualization::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionCustomVisualization) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpExtensionCustomVisualization::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionCustomVisualization::Release(void) {
    return Base::Release();
}
