//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionEmbeddedVisualization.h"
#include "SDK\AimpConverter.h"

int AimpExtensionEmbeddedVisualization::GetFlags() {
    return static_cast<int>(_managedObject->GetFlags());
}

HRESULT AimpExtensionEmbeddedVisualization::GetMaxDisplaySize(int* Width, int* Height) {
    const auto result = _managedObject->GetMaxDisplaySize();

    if (result->ResultType == ActionResultType::OK) {
        *Width = result->Item1;
        *Height = result->Item2;
        return S_OK;
    }

    return E_FAIL;
}

HRESULT AimpExtensionEmbeddedVisualization::GetName(IAIMPString** S) {
    IAIMPString* strObject = nullptr;
    const auto result = _managedObject->GetName();

    if (result->ResultType != ActionResultType::OK) {
        return E_FAIL;
    }

    const pin_ptr<const WCHAR> strDate = PtrToStringChars(result->Result);
    HRESULT r = _aimpCore->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&strObject));

    if (r == S_OK) {
        r = strObject->SetData(PWCHAR(strDate), result->Result->Length);
        *S = strObject;
    }

    return r;
}

HRESULT AimpExtensionEmbeddedVisualization::Initialize(int Width, int Height) {
    return HRESULT(_managedObject->Initialize(Width, Height)->ResultType);
}

void AimpExtensionEmbeddedVisualization::Finalize() {
    _managedObject->OnFinalize();
}

void AimpExtensionEmbeddedVisualization::Click(int X, int Y, int Button) {
    _managedObject->Click(X, Y, static_cast<Visuals::AimpVisualClickButtonType>(Button));
}

void AimpExtensionEmbeddedVisualization::Draw(HDC DC, PAIMPVisualData Data) {
    AIMP::SDK::Visuals::AimpVisualData^ data = AimpConverter::PAIMPVisualDataToManaged(Data);
    _managedObject->Draw(System::IntPtr(DC), data);
}

void AimpExtensionEmbeddedVisualization::Resize(int NewWidth, int NewHeight) {
    _managedObject->Resize(NewWidth, NewHeight);
}

HRESULT WINAPI AimpExtensionEmbeddedVisualization::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionEmbeddedVisualization) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG WINAPI AimpExtensionEmbeddedVisualization::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpExtensionEmbeddedVisualization::Release(void) {
    return Base::Release();
}
