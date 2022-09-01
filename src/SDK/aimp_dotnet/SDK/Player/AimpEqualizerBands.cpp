//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpEqualizerBands.h"

AimpEqualizerBands::AimpEqualizerBands(IAIMPEqualizerBands* obj) : AimpObject<IAIMPEqualizerBands>(obj) {
}

int AimpEqualizerBands::GetBandCount() {
    return InternalAimpObject->GetBandCount();
}

DoubleActionResult^ AimpEqualizerBands::GetBandFrequency(int bandIndex) {
    double value = 0;
    const auto result = CheckResult(InternalAimpObject->GetBandFrequency(bandIndex, &value));

    return gcnew DoubleActionResult(result, value);
}

DoubleActionResult^ AimpEqualizerBands::GetBandGain(int bandIndex) {
    double value = 0;
    const auto result = CheckResult(InternalAimpObject->GetBandGain(bandIndex, &value));

    return gcnew DoubleActionResult(result, value);
}

AimpActionResult^ AimpEqualizerBands::SetBandGain(int index, double value) {
    const auto result = CheckResult(InternalAimpObject->SetBandGain(index, value));
    return ACTION_RESULT(result);
}
