using AIMP.SDK.GUI.Controls.Events;

namespace AIMP.SDK.GUI.Controls
{
    public enum SpinEditValueType
    {
        Int32 = 0,
        Double
    }

    public interface IAimpUISpinEdit : IAimpUIWinControl, IAimpUIChangeEvents
    {
        string DisplayMask { get; set; }

        SpinEditValueType ValueType { get; set; }

        object Increment { get; set; }

        object MaxValue { get; set; } 

        object MinValue { get; set; }

        object Value { get; set; }
    }
}