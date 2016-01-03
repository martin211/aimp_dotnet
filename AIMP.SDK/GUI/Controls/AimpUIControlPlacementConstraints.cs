namespace AIMP.SDK.GUI.Controls
{
    // ReSharper disable once InconsistentNaming
    public struct AimpUIControlPlacementConstraints
    {
        public int MaxHeight { get; set; }

        public int MaxWidth { get; set; }

        public int MinHeight { get; set; }

        public int MinWidth { get; set; }

        public AimpUIControlPlacementConstraints(int maxHeight, int maxWidth, int minHeight, int minWidth)
        {
            MaxHeight = maxHeight;
            MaxWidth = maxWidth;
            MinHeight = minHeight;
            MinWidth = minWidth;
        }
    }
}