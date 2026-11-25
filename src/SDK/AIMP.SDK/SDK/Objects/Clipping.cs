namespace AIMP.SDK.Objects;

public class Clipping
{
    public Clipping(int offset, int size)
    {
        Offset = offset;
        Size = size;
    }

    public int Offset { get; }

    public int Size { get; }
}