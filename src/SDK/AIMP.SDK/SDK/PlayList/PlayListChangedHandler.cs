using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Delegate PlayListChangedHandler
/// </summary>
/// <param name="sender">The sender.</param>
/// <param name="notifType">Type of the notif.</param>
public delegate void PlayListChangedHandler(IAimpPlaylist sender, PlaylistNotifyType notifType);