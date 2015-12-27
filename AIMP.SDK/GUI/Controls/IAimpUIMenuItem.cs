namespace AIMP.SDK.GUI.Controls
{
    public interface IAimpUIMenuItem
    {
        AimpActionResult Add(string id, out IAimpUIMenuItem menuItem);

        AimpActionResult Delete(int index);

        AimpActionResult Get(int index, string id, out IAimpUIMenuItem menuItem);

        int GetCount();
    }
}