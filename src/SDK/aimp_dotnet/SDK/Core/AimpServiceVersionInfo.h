//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

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
