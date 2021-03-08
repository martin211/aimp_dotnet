#pragma once
#include "SDK/BaseAimpService.h"

public ref class AimpServiceVersionInfo :
    public BaseAimpService<IAIMPServiceVersionInfo>,
    public Core::IAimpServiceVersionInfo {

public:
    explicit AimpServiceVersionInfo(ManagedAimpCore^ core);
    property String^ FormatInfo { virtual String^ get(); }
    property DateTime BuildDate { virtual DateTime get(); }
    property Core::BuildStateType BuildState { virtual Core::BuildStateType get(); }
    property int BuildNumber { virtual int get(); }
    property int VersionId { virtual int get(); }
protected:
    IAIMPServiceVersionInfo* GetAimpService() override;
};
