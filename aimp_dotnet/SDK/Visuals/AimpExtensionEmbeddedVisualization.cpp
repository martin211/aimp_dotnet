#include "..\..\Stdafx.h"
#include "AimpExtensionEmbeddedVisualization.h"
#include "..\..\SDK\AimpConverter.h"

int AimpExtensionEmbeddedVisualization::GetFlags()
{
    return (int)_managedObject->GetFlags();
}

HRESULT AimpExtensionEmbeddedVisualization::GetMaxDisplaySize(int *Width, int *Height)
{
    int w = 0;
    int h = 0;

    if (_managedObject->GetMaxDisplaySize(*&w, *&h) == AimpActionResult::Ok)
    {
        *Width = w;
        *Height = h;
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
    HRESULT r = _aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject);

    if (r == S_OK)
    {
        r = strObject->SetData((PWCHAR)strDate, str->Length);
        *S = strObject;
    }

    return r;
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
    AIMP::SDK::Visuals::AimpVisualData ^data = AIMP::SDK::AimpConverter::PAIMPVisualDataToManaged(Data);
    _managedObject->Draw(System::IntPtr(DC), data);
}

void AimpExtensionEmbeddedVisualization::Resize(int NewWidth, int NewHeight)
{
    _managedObject->Resize(NewWidth, NewHeight);
}
