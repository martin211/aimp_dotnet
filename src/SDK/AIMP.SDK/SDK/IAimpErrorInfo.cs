namespace AIMP.SDK;

public interface IAimpErrorInfo : IAimpObject
{
    AimpActionResult<ErrorInfo> GetInfo();

    AimpActionResult<string> GetInfoFormatted();

    void SetInfo(int errorCode, string message, string details);
}