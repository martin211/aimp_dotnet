using System.Collections;

namespace AIMP.SDK.MusicLibrary.Presets
{
    public interface IAimpGroupingPresetStandard : IAimpGroupingPresets
    {
        ICollection Fields { get; }

        //AimpActionResult GetFilter(out IAimpDataFieldFilter filter);
    }
}