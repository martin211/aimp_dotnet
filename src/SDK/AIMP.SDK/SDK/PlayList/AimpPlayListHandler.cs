using System;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Delegate AimpPlayListHandler
/// </summary>
/// <param name="sender">The sender.</param>
public delegate void AimpPlayListHandler(IAimpPlaylist sender);

/// <summary>
/// Delegate AimpPlayListHandler
/// </summary>
/// <typeparam name="TEventArgs">The type of the t event arguments.</typeparam>
/// <param name="sender">The sender.</param>
/// <param name="args">The <see cref="TEventArgs" /> instance containing the event data.</param>
public delegate void AimpPlayListHandler<in TEventArgs>(IAimpPlaylist sender, TEventArgs args) where TEventArgs : EventArgs;