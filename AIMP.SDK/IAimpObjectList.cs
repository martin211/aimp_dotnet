namespace AIMP.SDK
{
    public interface IAimpObjectList<TObject>
    {
        AimpActionResult Add(TObject entry);

        AimpActionResult Clear();

        AimpActionResult Delete(int index);

        AimpActionResult Insert(int index, TObject item);

        int Count { get; }

        AimpActionResult GetObject(int index, out TObject item);

        AimpActionResult SetObject(int index, TObject item);
    }
}