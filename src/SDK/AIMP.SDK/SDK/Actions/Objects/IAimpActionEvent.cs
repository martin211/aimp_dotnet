// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;

<<<<<<<< HEAD:src/SDK/AIMP.SDK/SDK/Actions/IAimpActionEvent.cs
namespace AIMP.SDK.Actions
========
namespace AIMP.SDK.Actions.Objects
>>>>>>>> release/5.02.2365.1:src/SDK/AIMP.SDK/SDK/Actions/Objects/IAimpActionEvent.cs
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
