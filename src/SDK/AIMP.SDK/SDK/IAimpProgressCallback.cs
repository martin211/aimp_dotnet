namespace AIMP.SDK;

public interface IAimpProgressCallback
{
    AimpActionResult Process(double progress, bool canceled);
}