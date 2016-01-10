namespace AIMP.SDK.GUI.Controls
{
    using System;
    using System.Drawing;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIImageList
    {
        AimpActionResult Add(Image image);

        AimpActionResult Clear();

        AimpActionResult Delete(int index);

        AimpActionResult Draw(IntPtr dc, int x, int y, bool enabled);

        AimpActionResult LoadFromResource(IntPtr module, string resName, string resType);

        int GetCount();

        AimpActionResult GetSize(out SizeF size);

        AimpActionResult SetSize(SizeF size);
    }
}