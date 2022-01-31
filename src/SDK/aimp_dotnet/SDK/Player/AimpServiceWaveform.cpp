#include "Stdafx.h"
#include "AimpServiceWaveform.h"

AimpServiceWaveform::AimpServiceWaveform(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceWaveform>(core) {
}

IAIMPServiceWaveform* AimpServiceWaveform::GetAimpService() {
    IAIMPServiceWaveform* service = nullptr;
    GetService(IID_IAIMPServiceWaveform, &service);
    return service;
}
