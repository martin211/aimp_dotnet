#include "..\..\Stdafx.h"
#include "AimpExtensionCustomVisualization.h"



int AimpExtensionCustomVisualization::GetFlags()
{
    return (int)_managedObject->GetFlags();
}

void AimpExtensionCustomVisualization::Draw(PAIMPVisualData Data)
{
    AIMP::SDK::Visuals::AimpVisualData ^visualData = gcnew AIMP::SDK::Visuals::AimpVisualData();
    visualData->Peaks = gcnew array<float>(2);

    _managedObject->Draw(visualData);
}
