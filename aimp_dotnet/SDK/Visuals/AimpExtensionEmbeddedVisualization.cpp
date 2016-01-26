#include "..\..\Stdafx.h"
#include "AimpExtensionEmbeddedVisualization.h"



int AimpExtensionEmbeddedVisualization::GetFlags()
{
    return (int)_managedObject->GetFlags();
}

HRESULT AimpExtensionEmbeddedVisualization::GetMaxDisplaySize(int *Width, int *Height)
{
    int w = 0;
    int h = 0;
    INT w1 = *&w;
    INT h1 = *&h;

    System::Diagnostics::Debugger::Break();

    if (_managedObject->GetMaxDisplaySize(w1, h1) == AimpActionResult::Ok)
    {
        *Width = w1;
        *Height = h1;
        return S_OK;
    }

    return E_FAIL;
}

HRESULT AimpExtensionEmbeddedVisualization::GetName(IAIMPString **S)
{
    IAIMPString *strObject = NULL;
    System::String ^str;
    if (_managedObject->GetName(*&str) != AimpActionResult::Ok)
    {
        return E_FAIL;
    }

    pin_ptr<const WCHAR> strDate = PtrToStringChars(str);
    _aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject);
    strObject->SetData((PWCHAR)strDate, str->Length);
    *S = strObject;
    strObject->Release();

    return S_OK;
}

void AimpExtensionEmbeddedVisualization::Initialize(int Width, int Height)
{
    _managedObject->Initialize(Width, Height);
}

void AimpExtensionEmbeddedVisualization::Finalize()
{
    _managedObject->OnFinalize();
}

void AimpExtensionEmbeddedVisualization::Click(int X, int Y, int Button)
{
    _managedObject->Click(X, Y, (AIMP::SDK::Visuals::AimpVisualClickButtonType)Button);
}

void AimpExtensionEmbeddedVisualization::Draw(HDC DC, PAIMPVisualData Data)
{
    //_managedObject->Draw()
}

void AimpExtensionEmbeddedVisualization::Resize(int NewWidth, int NewHeight)
{
    _managedObject->Resize(NewWidth, NewHeight);
}
