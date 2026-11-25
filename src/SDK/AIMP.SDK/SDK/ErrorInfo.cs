namespace AIMP.SDK;

public class ErrorInfo
{
    public ErrorInfo(int errorCode, string message, string details)
    {
        ErrorCode = errorCode;
        Message = message;
        Details = details;
    }

    public int ErrorCode { get; set; }

    public string Message { get; set; }

    public string Details { get; set; }
}