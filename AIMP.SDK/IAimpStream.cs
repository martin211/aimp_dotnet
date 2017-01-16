namespace AIMP.SDK
{
    public interface IAimpStream
    {
        long GetSize();

        AimpActionResult SetSize(long value);

        long GetPosition();

        AimpActionResult Seek(long offset, System.IO.SeekOrigin mode);

        int Read(byte[] buffer, int count);

        AimpActionResult Write(byte[] buffer, int count, out int writen);
    }
}
