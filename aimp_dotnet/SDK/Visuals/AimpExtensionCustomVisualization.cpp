#include "..\..\Stdafx.h"
#include "AimpExtensionCustomVisualization.h"
//#include "..\..\SDK\Converter.h"


int AimpExtensionCustomVisualization::GetFlags()
{
    return (int)_managedObject->GetFlags();
}

void AimpExtensionCustomVisualization::Draw(PAIMPVisualData Data)
{
    AIMP::SDK::Visuals::AimpVisualData ^data = AIMP::SDK::AimpExtension::PAIMPVisualDataToManaged(Data);
    _managedObject->Draw(data);
}
