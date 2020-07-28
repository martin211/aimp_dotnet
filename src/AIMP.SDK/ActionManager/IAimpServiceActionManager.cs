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
using System.Collections.Generic;
using System.Windows.Input;

namespace AIMP.SDK.ActionManager
{
    /// <summary>
    /// The service provides an access to actions.
    /// </summary>
    public interface IAimpServiceActionManager : IAimpService
    {
        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="action">The action.</param>
        AimpActionResult<IAimpAction> GetById(string id);

        /// <summary>
        /// Makes the hotkey.
        /// </summary>
        /// <param name="modifiers">The key modifiers <see cref="ModifierKeys"/>.</param>
        /// <param name="key">The key.</param>
        int MakeHotkey(ModifierKeys modifiers, uint key);

        /// <summary>
        /// Registers the specified action.
        /// </summary>
        /// <param name="action">The action <see cref="IAimpAction"/>.</param>
        AimpActionResult Register(IAimpAction action);

        /// <summary>
        /// Registers the specified actions.
        /// </summary>
        /// <param name="actions">The collection of <see cref="IAimpAction"/>.</param>
        AimpActionResult Register(ICollection<IAimpAction> actions);

        /// <summary>
        /// Creates the Aimp action instance.
        /// </summary>
        [Obsolete("Use Core.CreateObject<IAimpAction>")]
        IAimpAction CreateAction();
    }
}