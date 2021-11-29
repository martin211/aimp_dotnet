using AIMP.SDK.Playback;
using AIMP.SDK.Playlist;

namespace AIMP.SDK.Player
{
    public interface IAimpServicePlayer2
    {
        /// <summary>
        /// Plays the specified item.
        /// </summary>
        /// <param name="item">Note that function doesn't check if file playback really started. It just put the file into queue of loading thread.</param>
        /// <param name="offset">Initial position in seconds. Set position to -1 to allow player to catch automatic bookmark for the track.</param>
        /// <param name="flags">Note that function doesn't check if file playback really started. It just put the file into queue of loading thread.</param>
        AimpActionResult Play(IAimpPlaybackQueueItem item, int offset, PlayFlags flags);

        /// <summary>
        /// Plays the specified play list item.
        /// </summary>
        /// <param name="item">Note that function doesn't check if file playback really started. It just put the file into queue of loading thread.</param>
        /// <param name="offset">Initial position in seconds. Set position to -1 to allow player to catch automatic bookmark for the track.</param>
        /// <param name="flags">Note that function doesn't check if file playback really started. It just put the file into queue of loading thread.</param>
        /// <returns></returns>
        AimpActionResult Play(IAimpPlaylistItem item, int offset, PlayFlags flags);

        /// <summary>
        /// Plays the specified file URI.
        /// </summary>
        /// <param name="fileUri">Can be file path to playlist.</param>
        /// <param name="offset">Initial position in seconds. Set position to -1 to allow player to catch automatic bookmark for the track.</param>
        /// <param name="flags"></param>
        /// <returns></returns>
        AimpActionResult Play(string fileUri, int offset, PlayFlags flags);
    }
}