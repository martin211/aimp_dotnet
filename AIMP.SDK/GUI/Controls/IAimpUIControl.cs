namespace AIMP.SDK.GUI.Controls
{
    public interface IAimpUIControl
    {
        string CustomData { get; set; }

        bool Enabled { get; set; }

        string Hint { get; set; }

        string Name { get; set; }

        IAimpUIWinControl Parent { get; set; }


    }
}