namespace AIMP.SDK.Visuals
{
    public interface IAimpExtensionCustomVisualization
    {
        AimpVisualFlags GetFlags();

        void Draw(AimpVisualData data);
    }
}