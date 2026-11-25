namespace AIMP.SDK.Visuals;

/// <summary>
/// Extends <see cref="IAimpExtensionEmbeddedVisualization"/> with the AIMP 6.0
/// action-based input model.
/// </summary>
public interface IAimpExtensionEmbeddedVisualization2 : IAimpExtensionEmbeddedVisualization
{
    void Action(int x, int y, AimpVisualAction action);
}