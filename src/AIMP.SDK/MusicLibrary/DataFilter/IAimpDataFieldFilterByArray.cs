﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataFilter
{
    public interface IAimpDataFieldFilterByArray
    {
        /// <summary>
        /// Gets or sets the filter field.
        /// </summary>
        string Field { get; set; }

        AimpActionResult GetData(IList<object> values);

        AimpActionResult SetData(IList<object> values);
    }
}