// ----------------------------------------------------
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
using System.Windows.Input;

namespace AIMP.SDK.ActionManager
{
    /// <summary>
    /// The service provides an access to actions.
    /// </summary>
    public interface IAimpServiceActionManager
    {
        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="action">The action.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        AimpActionResult GetById(string id, out IAimpAction action);

        /// <summary>
        /// Makes the hotkey.
        /// </summary>
        /// <param name="modifiers">The key modifiers <see cref="ModifierKeys"/>.</param>
        /// <param name="key">The key.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        int MakeHotkey(ModifierKeys modifiers, uint key);

        /// <summary>
        /// Registers the specified action.
        /// </summary>
        /// <param name="action">The action <see cref="IAimpAction"/>.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        AimpActionResult Register(IAimpAction action);

        /// <summary>
        /// Registers the specified actions.
        /// </summary>
        /// <param name="actions">The collection of <see cref="IAimpAction"/>.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        AimpActionResult Register(ICollection<IAimpAction> actions);

        /// <summary>
        /// Creates the Aimp action instance.
        /// </summary>
        IAimpAction CreateAction();
    }
}