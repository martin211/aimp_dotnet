// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataProvider
    {
        AimpActionResult GetData(IList<string> fields, IAimpDataFilter filter, out object data);
    }
}