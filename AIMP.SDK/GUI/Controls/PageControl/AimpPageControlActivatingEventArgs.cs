namespace AIMP.SDK.GUI.Controls.PageControl
{
    public class AimpPageControlActivatingEventArgs : AimpPageControlEventArgs
    {
        public bool Canceled { get; set; }

        public AimpPageControlActivatingEventArgs(IAimpUITabSheet tabSheet) : base(tabSheet)
        {
        }
    }
}