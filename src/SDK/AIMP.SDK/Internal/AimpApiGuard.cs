using AIMP.SDK;

namespace AIMP.Internal
{
    /// <summary>
    /// Guards SDK APIs that were introduced in a specific AIMP version.
    /// </summary>
    internal static class AimpApiGuard
    {
        /// <summary>
        /// Throws <see cref="AimpUnsupportedApiException"/> when the running
        /// AIMP is older than <paramref name="major"/>.<paramref name="minor"/>.
        /// When the version cannot be detected the check is skipped.
        /// </summary>
        public static void Require(int major, int minor, string apiName)
        {
            var version = AimpRuntime.Version;

            if (!version.IsKnown || version.IsAtLeast(major, minor))
            {
                return;
            }

            AimpLog.Write(
                $"Unsupported API '{apiName}': requires AIMP {major}.{minor.ToString("00")}, current {version}.");

            throw new AimpUnsupportedApiException(apiName, major, minor, version);
        }
    }
}