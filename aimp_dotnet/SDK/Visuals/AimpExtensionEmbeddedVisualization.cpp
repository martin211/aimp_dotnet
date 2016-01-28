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
    _aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject);
    strObject->SetData((PWCHAR)strDate, str->Length);
    *S = strObject;
    //strObject->Release();

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
    AIMP::SDK::Visuals::AimpVisualData ^data = gcnew AIMP::SDK::Visuals::AimpVisualData();
    data->Peaks = gcnew array<float>(2);
    data->Spectrum = gcnew array<array<byte>^>(3);
    data->WaveForm = gcnew array<array<byte>^>(2);

    data->Peaks[0] = Data->Peaks[0];
    data->Peaks[1] = Data->Peaks[1];

    for (int i = 0; i < 3; i++)
    {
        array<byte> ^arr = gcnew array<byte>(AIMP_VISUAL_SPECTRUM_MAX);
        for (int j = 0; j < AIMP_VISUAL_SPECTRUM_MAX; j++)
        {
            arr[j] = Data->Spectrum[i][j];
        }
        data->Spectrum[i] = arr;
    }

    for (int i = 0; i < 2; i++)
    {
        array<byte> ^arr = gcnew array<byte>(AIMP_VISUAL_WAVEFORM_MAX);
        for (int j = 0; j < AIMP_VISUAL_WAVEFORM_MAX; j++)
        {
            arr[j] = Data->WaveForm[i][j];
        }
        data->WaveForm[i] = arr;
    }

    _managedObject->Draw(System::IntPtr(DC), data);
}

void AimpExtensionEmbeddedVisualization::Resize(int NewWidth, int NewHeight)
{
    _managedObject->Resize(NewWidth, NewHeight);
}
