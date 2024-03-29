﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.Actions.Objects
{
    /// <summary>
    /// This interface is simple event handler.
    /// </summary>
    public interface IAimpActionEvent
    {
        //todo: add Data parameter
        /// <summary>
        /// Occurs when action is executing.
        /// </summary>
        event EventHandler OnExecute;
    }
}
