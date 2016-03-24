using System;

namespace AIMP.SDK.PlayList
{
    public interface IAimpPlaylistQueueListener
    {
        event EventHandler ContentChanged;

        event EventHandler StateChanged;
    }
}