namespace AIMP.SDK.GUI.Controls
{
    using System.ComponentModel;
    using System.Drawing;

    public interface IAimpUIPopupMenu
    {
        AimpActionResult Add(string id, out IAimpUIMenuItem menuItem);

        AimpActionResult Delete(int index);

        AimpActionResult Get(int index, string id, out IAimpUIMenuItem menuItem);

        int GetCount();

        AimpActionResult Popup(PointF screenPoint);

        AimpActionResult Popup(RectangleF screenRectangle);
    }
}