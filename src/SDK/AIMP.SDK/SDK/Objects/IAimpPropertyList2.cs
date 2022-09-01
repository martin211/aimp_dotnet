//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Objects;

public interface IAimpPropertyList
{
    /// <summary>
    /// Begins the update.
    /// </summary>
    void BeginUpdate();

    /// <summary>
    /// Ends the update.
    /// </summary>
    void EndUpdate();
}

public interface IAimpPropertyList2 : IAimpPropertyList
{

}