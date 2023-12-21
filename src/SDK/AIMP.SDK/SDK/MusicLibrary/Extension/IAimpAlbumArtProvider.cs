﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Objects;

namespace AIMP.SDK.MusicLibrary.Extension;

public interface IAimpAlbumArtProvider
{
    AimpActionResult<IAimpImageContainer> Get(IAimpObjectList<string> fields, object[] values, IAimpPropertyList options);
}