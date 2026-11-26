namespace AIMP.SDK.Visuals;

/// <summary>
/// Actions reported by <see cref="IAimpExtensionEmbeddedVisualization2"/>.
/// </summary>
public enum AimpVisualAction
{
    Click = 0,
    ClickMiddle = 1,
    Move = 3,
    Leave = 4,
    ClickDouble = 5,
    WheelDown = 6,
    WheelUp = 7,
    Down = 8
}