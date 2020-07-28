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
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceActionManager : IAimpService
    {
        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>AimpActionResult&lt;IAimpAction&gt;.</returns>
        AimpActionResult<IAimpAction> GetById(string id);

        /// <summary>
        /// Makes the hotkey.
        /// </summary>
        /// <param name="modifiers">The key modifiers <see cref="ModifierKeys" />.</param>
        /// <param name="key">The key.</param>
        /// <returns>System.Int32.</returns>
        int MakeHotkey(ModifierKeys modifiers, uint key);

        /// <summary>
        /// Registers the specified action.
        /// </summary>
        /// <param name="action">The action <see cref="IAimpAction" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Register(IAimpAction action);

        /// <summary>
        /// Registers the specified actions.
        /// </summary>
        /// <param name="actions">The collection of <see cref="IAimpAction" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Register(ICollection<IAimpAction> actions);

        /// <summary>
        /// Creates the Aimp action instance.
        /// </summary>
        /// <returns>IAimpAction.</returns>
        [Obsolete("Use Core.CreateObject<IAimpAction>")]
        IAimpAction CreateAction();
    }
}