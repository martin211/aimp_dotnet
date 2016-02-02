using System.Collections.Generic;

namespace AIMP.SDK.GUI.Controls
{
    public interface IAimpUIBaseComboBox : IAimpUIBaseButtonnedEdit
    {
        AimpActionResult Add(string value, string extraData);

        AimpActionResult AddRange(ICollection<string> values);

        AimpActionResult Clear();

        AimpActionResult Delete(int index);

        string this[int index] { get; }

        AimpActionResult SetItem(int index, string item);
    }
}