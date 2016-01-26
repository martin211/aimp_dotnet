namespace AIMP.SDK.Visuals
{
    public interface IAimpExtensionCustomVisualization : IAimpExtension
    {
        AimpVisualFlags GetFlags();

        void Draw(AimpVisualData data);
    }
}