using System;

namespace AIMP.SDK;

/// <summary>
/// Thrown when a plugin calls an SDK API that is not available in the
/// running AIMP version.
/// </summary>
public sealed class AimpUnsupportedApiException : NotSupportedException
{
    public AimpUnsupportedApiException(string apiName, int requiredMajor, int requiredMinor, AimpVersion currentVersion)
        : base(BuildMessage(apiName, requiredMajor, requiredMinor, currentVersion))
    {
        ApiName = apiName;
        RequiredVersion = new AimpVersion(
            requiredMajor,
            requiredMinor,
            0,
            0,
            "v" + requiredMajor + "." + requiredMinor.ToString("00"));
        CurrentVersion = currentVersion;
    }

    /// <summary>
    /// Gets the API that is not available.
    /// </summary>
    public string ApiName { get; }

    /// <summary>
    /// Gets the minimum AIMP version required by the API.
    /// </summary>
    public AimpVersion RequiredVersion { get; }

    /// <summary>
    /// Gets the detected AIMP version.
    /// </summary>
    public AimpVersion CurrentVersion { get; }

    private static string BuildMessage(string apiName, int major, int minor, AimpVersion current)
    {
        var required = $"AIMP {major}.{minor:00}";

        return current.IsKnown
            ? $"API '{apiName}' requires {required} or newer. Current AIMP version: {current}."
            : $"API '{apiName}' requires {required} or newer. The current AIMP version is unknown.";
    }
}